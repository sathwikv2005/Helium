#include "../include/vm.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../include/common.h"
#include "../include/compiler.h"
#include "../include/debug.h"
#include "../include/memory.h"
#include "../include/nativeFn.h"
#include "../include/object.h"
#include "../include/vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
    vm.frameCount = 0;
}

void runtimeError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    for (int i = vm.frameCount - 1; i >= 0; i--) {
        CallFrame* frame = &vm.frames[i];
        ObjFunction* function = frame->closure->function;
        size_t instruction = frame->ip - function->chunk.code - 1;
        fprintf(stderr, "[line %d] in ",
                getLine(&frame->closure->function->chunk, instruction));
        if (function->name == NULL) {
            fprintf(stderr, "script\n");
        } else {
            fprintf(stderr, "%s()\n", function->name->chars);
        }
    }

    resetStack();
    longjmp(vm.errorJmp, 1);
}

void initVM() {
    resetStack();
    vm.objects = NULL;
    vm.debugFlags = 0;
    initTable(&vm.globals);
    initTable(&vm.strings);

    mapNatives();
}

void freeVM() {
    freeObjects();
    freeTable(&vm.strings);
    freeTable(&vm.globals);
}

static Value peek(int distance) { return vm.stackTop[-1 - distance]; }

static bool call(ObjClosure* closure, int argCount) {
    if (argCount != closure->function->arity) {
        runtimeError("Expected %d arguments but got %d.",
                     closure->function->arity, argCount);
        return false;
    }
    if (vm.frameCount == FRAMES_MAX) {
        runtimeError("Stack overflow.");
        return false;
    }
    CallFrame* frame = &vm.frames[vm.frameCount++];
    frame->closure = closure;
    frame->ip = closure->function->chunk.code;
    frame->slots = vm.stackTop - argCount - 1;
    return true;
}

static bool callValue(Value callee, int argCount) {
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_CLOSURE:
                return call(AS_CLOSURE(callee), argCount);
            case OBJ_NATIVE: {
                NativeFn native = AS_NATIVE(callee);
                Value result = native(argCount, vm.stackTop - argCount);
                vm.stackTop -= argCount + 1;
                push(result);
                return true;
            }
            default:
                break;  // Non-callable object type.
        }
    }
    runtimeError("Can only call functions and classes.");
    return false;
}

static bool isFalsey(Value value) {
    return IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

static void concatenate() {
    ObjString* b = valueToString(pop());
    ObjString* a = valueToString(pop());

    int length = a->length + b->length;
    char* chars = ALLOCATE(char, length + 1);
    memcpy(chars, a->chars, a->length);
    memcpy(chars + a->length, b->chars, b->length);
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    push(OBJ_VAL(result));
}

static InterpretResult run() {
    CallFrame* frame = &vm.frames[vm.frameCount - 1];
    register uint8_t* ip = frame->ip;
#define READ_BYTE() (*ip++)
#define READ_CONSTANT() \
    (frame->closure->function->chunk.constants.values[READ_BYTE()])
#define READ_SHORT() (ip += 2, (uint16_t)((ip[-2] << 8) | ip[-1]))
#define READ_STRING() AS_STRING(READ_CONSTANT())
#define BINARY_OP(valueType, op)                          \
    do {                                                  \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            frame->ip = ip;                               \
            runtimeError("Operands must be numbers.");    \
            return INTERPRET_RUNTIME_ERROR;               \
        }                                                 \
        double b = AS_NUMBER(pop());                      \
        double a = AS_NUMBER(pop());                      \
        push(valueType(a op b));                          \
    } while (false)

    while (true) {
        if (GET_DEBUG_TRACE()) {
            printf("Stack=>\t");
            printf("[ ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printValue(*slot);
                printf(", ");
            }
            printf("]");
            printf("\n");
            disassembleInstruction(
                &frame->closure->function->chunk,
                (int)(ip - frame->closure->function->chunk.code));
            // printf("==+++++++++==\n");
        }

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_FALSE:
                push(BOOL_VAL(false));
                break;
            case OP_TRUE:
                push(BOOL_VAL(true));
                break;
            case OP_NULL:
                push(NULL_VAL);
                break;
            case OP_POP:
                pop();
                break;
            case OP_GET_LOCAL: {
                uint8_t slot = READ_BYTE();
                push(frame->slots[slot]);
                break;
            }
            case OP_SET_LOCAL: {
                uint8_t slot = READ_BYTE();
                frame->slots[slot] = peek(0);
                break;
            }
            case OP_SET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;

                if (!tableGet(&vm.globals, name, &value)) {
                    frame->ip = ip;
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }

                if (!IS_VARIABLE(value)) {
                    frame->ip = ip;
                    runtimeError("Internal error: expected variable.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                ObjVariable* var = AS_VARIABLE(value);

                if (var->isConst) {
                    frame->ip = ip;
                    runtimeError("Cannot assign to const variable '%s'.",
                                 name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }

                var->value = peek(0);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;
                if (!tableGet(&vm.globals, name, &value)) {
                    frame->ip = ip;
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                if (IS_VARIABLE(value)) {
                    ObjVariable* var = AS_VARIABLE(value);
                    push(var->value);
                    break;
                } else
                    push(value);
                break;
            }
            case OP_DEFINE_GLOBAL: {
                ObjString* name = READ_STRING();
                tableSet(&vm.globals, name,
                         OBJ_VAL(newVariable(peek(0), false)));
                pop();
                break;
            }
            case OP_DEFINE_GLOBAL_CONST: {
                ObjString* name = READ_STRING();
                tableSet(&vm.globals, name,
                         OBJ_VAL(newVariable(peek(0), true)));
                pop();
                break;
            }
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_GREATER:
                BINARY_OP(BOOL_VAL, >);
                break;
            case OP_LESS:
                BINARY_OP(BOOL_VAL, <);
                break;
            case OP_ADD: {
                if (IS_STRING(peek(0)) || IS_STRING(peek(1))) {
                    concatenate();
                } else if (IS_NUMBER(peek(0)) && IS_NUMBER(peek(1))) {
                    double b = AS_NUMBER(pop());
                    double a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a + b));
                } else {
                    frame->ip = ip;
                    runtimeError("Operands must be numbers or strings.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUBTRACT:
                BINARY_OP(NUMBER_VAL, -);
                break;
            case OP_MULTIPLY:
                BINARY_OP(NUMBER_VAL, *);
                break;
            case OP_DIVIDE:
                BINARY_OP(NUMBER_VAL, /);
                break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE: {
                if (!IS_NUMBER(peek(0))) {
                    frame->ip = ip;
                    runtimeError("Operand must be a number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            }
            case OP_PRINT: {
                printValue(pop());
                printf("\n");
                break;
            }
            case OP_JUMP: {
                uint16_t offset = READ_SHORT();
                ip += offset;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t offset = READ_SHORT();
                if (isFalsey(peek(0))) ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = READ_SHORT();
                ip -= offset;
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();
                frame->ip = ip;
                if (!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            case OP_CLOSURE: {
                ObjFunction* function = AS_FUNCTION(READ_CONSTANT());
                ObjClosure* closure = newClosure(function);
                push(OBJ_VAL(closure));
                break;
            }
            case OP_RETURN: {
                Value result = pop();
                vm.frameCount--;
                if (vm.frameCount == 0) {
                    pop();
                    frame->ip = ip;
                    return INTERPRET_OK;
                }

                vm.stackTop = frame->slots;
                push(result);
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            default:
                break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_SHORT
#undef READ_STRING
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    ObjFunction* function = compile(source);

    if (function == NULL) {
        return INTERPRET_COMPILE_ERROR;
    }

    push(OBJ_VAL(function));
    ObjClosure* closure = newClosure(function);
    pop();
    push(OBJ_VAL(closure));
    callValue(OBJ_VAL(closure), 0);

    if (setjmp(vm.errorJmp) != 0) {
        return INTERPRET_RUNTIME_ERROR;
    }

    return run();
}

void push(Value value) {
    if (vm.stackTop == vm.stack + STACK_MAX) {
        runtimeError("Stack overflow error.");
    }
    *vm.stackTop++ = value;
}

Value pop() {
    if (vm.stackTop == vm.stack) {
        runtimeError("Stack underflow error.");
    }
    return *--vm.stackTop;
}
