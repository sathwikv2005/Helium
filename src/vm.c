#include "../include/vm.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
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
    vm.openUpvalues = NULL;
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
    vm.grayCount = 0;
    vm.grayCapacity = 0;
    vm.grayStack = NULL;
    vm.debugFlags = 0;
    vm.bytesAllocated = 0;
    vm.nextGC = 1024 * 1024;
    vm.currentGCMark = true;
    initTable(&vm.globals);
    initTable(&vm.strings);

    vm.initString = NULL;
    vm.pushString = NULL;
    vm.popString = NULL;
    vm.lengthString = NULL;
    vm.sortString = NULL;
    vm.initString = copyString("init", 4);
    vm.pushString = copyString("push", 4);
    vm.popString = copyString("pop", 3);
    vm.lengthString = copyString("length", 6);
    vm.sortString = copyString("sort", 4);

    mapNatives();
}

void freeVM() {
    vm.initString = NULL;
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

static bool sortDescending = false;

static int compareValues(const void* a, const void* b) {
    double da = AS_NUMBER(*(const Value*)a);
    double db = AS_NUMBER(*(const Value*)b);

    int result = (da > db) - (da < db);

    return sortDescending ? -result : result;
}

static bool arrayMethods(ObjArray* receiver, int argCount,
                         ArrayMethodType type) {
    switch (type) {
        case ARRAY_METHOD_PUSH:
            if (argCount != 1) {
                runtimeError("push() expects 1 argument.");
                return false;
            }

            writeValueArray(&receiver->array, peek(0));

            vm.stackTop -= argCount + 1;
            push(OBJ_VAL(receiver));
            return true;

        case ARRAY_METHOD_POP: {
            if (argCount > 1) {
                runtimeError("pop() expects 0 or 1 arguments.");
                return false;
            }
            int offset = 0;

            if (argCount != 0) {
                Value arg = vm.stackTop[-1];
                if (!IS_NUMBER(arg)) {
                    runtimeError("pop() expects a number.");
                    return false;
                }
                double index = AS_NUMBER(arg);

                if (index < 0 || index != (int)index) {
                    runtimeError(
                        "Array index must be a non-negative "
                        "integer");
                    return false;
                }

                offset = (int)index;
            }
            if (offset >= receiver->array.count) {
                runtimeError("Array index out of bounds.");
                return false;
            }
            receiver->array.count -= (1 + offset);

            vm.stackTop -= argCount + 1;

            push(OBJ_VAL(receiver));
            return true;
        }
        case ARRAY_METHOD_LENGTH: {
            if (argCount != 0) {
                runtimeError("lenght() expects no arguments.");
                return false;
            }
            vm.stackTop -= argCount + 1;
            push(NUMBER_VAL(receiver->array.count));
            return true;
        }
        case ARRAY_METHOD_SORT: {
            if (argCount > 1) {
                runtimeError("sort() expects 0 or 1 arguments.");
                return false;
            }
            sortDescending = false;
            ValueArray* array = &receiver->array;
            for (int i = 0; i < array->count; i++) {
                if (!IS_NUMBER(array->values[i])) {
                    runtimeError(
                        "Array.sort() only supports arrays of numbers.");
                    return false;
                }
            }
            if (argCount == 1) {
                Value arg = vm.stackTop[-1];

                if (!IS_BOOL(arg)) {
                    runtimeError("sort() expects a boolean.");
                    return false;
                }

                sortDescending = AS_BOOL(arg);
            }
            qsort(array->values, array->count, sizeof(Value), compareValues);
            vm.stackTop -= argCount + 1;
            push(OBJ_VAL(receiver));
            return true;
        }
    }
    return false;
}

static bool arrayMethodsFromName(ObjArray* receiver, int argCount,
                                 ObjString* method) {
    if (method == vm.pushString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_PUSH);
    }
    if (method == vm.popString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_POP);
    }
    if (method == vm.lengthString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_LENGTH);
    }
    if (method == vm.sortString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_SORT);
    }
    runtimeError("Undefined array method '%s'.", method->chars);
    return false;
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
            case OBJ_BOUND_METHOD: {
                ObjBoundMethod* bound = AS_BOUND_METHOD(callee);
                vm.stackTop[-argCount - 1] = bound->receiver;
                return call(bound->method, argCount);
            }
            case OBJ_CLASS: {
                ObjClass* klass = AS_CLASS(callee);
                vm.stackTop[-argCount - 1] = OBJ_VAL(newInstance(klass));
                if (klass->initializer != NULL) {
                    return call(klass->initializer, argCount);
                } else if (argCount != 0) {
                    runtimeError(
                        "Initializer %s() expects 0 arguments but got %d.",
                        klass->name->chars, argCount);
                    return false;
                }
                return true;
            }
            case OBJ_ARRAY_METHOD: {
                ObjArrayMethod* method = AS_ARRAY_METHOD(callee);
                return arrayMethods(method->receiver, argCount, method->type);
            }
            default:
                break;  // Non-callable object type.
        }
    } else if (IS_NULL(callee)) {
        runtimeError("Can not call a null value.");
        return false;
    }
    runtimeError("Can only call functions and classes.");
    return false;
}

static bool invokeFromClass(ObjClass* klass, ObjString* name, int argCount) {
    Value method;
    if (name == vm.initString) {
        if (klass->initializer == NULL) {
            if (argCount != 0) {
                runtimeError(
                    "Superclass has no initializer accepting %d arguments.",
                    argCount);
                return false;
            }
            return true;  // do nothing
        }
        return call(klass->initializer, argCount);
    } else if (!tableGet(&klass->methods, name, &method)) {
        runtimeError("Undefined property '%s'.", name->chars);
        return false;
    }
    return call(AS_CLOSURE(method), argCount);
}

static bool invoke(ObjString* name, int argCount) {
    Value receiver = peek(argCount);

    if (!IS_INSTANCE(receiver)) {
        runtimeError("Only instances have methods.");
        return false;
    }

    ObjInstance* instance = AS_INSTANCE(receiver);

    Value value;
    if (tableGet(&instance->fields, name, &value)) {
        vm.stackTop[-argCount - 1] = value;
        return callValue(value, argCount);
    }

    return invokeFromClass(instance->klass, name, argCount);
}

static bool bindMethod(ObjClass* klass, ObjString* name) {
    Value method;
    if (!tableGet(&klass->methods, name, &method)) {
        return false;
    }
    ObjBoundMethod* bound = newBoundMethod(peek(0), AS_CLOSURE(method));
    pop();
    push(OBJ_VAL(bound));
    return true;
}

static ObjUpvalue* captureUpvalue(Value* local) {
    ObjUpvalue* prevUpvalue = NULL;
    ObjUpvalue* upvalue = vm.openUpvalues;
    while (upvalue != NULL && upvalue->location > local) {
        prevUpvalue = upvalue;
        upvalue = upvalue->next;
    }

    if (upvalue != NULL && upvalue->location == local) {
        return upvalue;
    }

    ObjUpvalue* createdUpvalue = newUpvalue(local);
    createdUpvalue->next = upvalue;

    if (prevUpvalue == NULL) {
        vm.openUpvalues = createdUpvalue;
    } else {
        prevUpvalue->next = createdUpvalue;
    }
    return createdUpvalue;
}

static void closeUpvalues(Value* last) {
    while (vm.openUpvalues != NULL && vm.openUpvalues->location >= last) {
        ObjUpvalue* upvalue = vm.openUpvalues;
        upvalue->closed = *upvalue->location;
        upvalue->location = &upvalue->closed;
        vm.openUpvalues = upvalue->next;
    }
}

static void defineMethod(ObjString* name) {
    Value method = peek(0);
    ObjClass* klass = AS_CLASS(peek(1));
    if (name == vm.initString) {
        klass->initializer = AS_CLOSURE(method);
    } else {
        tableSet(&klass->methods, name, method);
    }
    pop();
}

static bool isFalsey(Value value) {
    return IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

static void concatenate() {
    ObjString* b = AS_STRING(valueToString(peek(0)));
    ObjString* a = AS_STRING(valueToString(peek(1)));

    int length = a->length + b->length;
    char* chars = ALLOCATE(char, length + 1);
    memcpy(chars, a->chars, a->length);
    memcpy(chars + a->length, b->chars, b->length);
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    pop();
    pop();
    push(OBJ_VAL(result));
}

static InterpretResult run() {
    CallFrame* frame = &vm.frames[vm.frameCount - 1];
    register uint8_t* ip = frame->ip;
#define RUNTIME_ERROR(...)         \
    do {                           \
        frame->ip = ip;            \
        runtimeError(__VA_ARGS__); \
    } while (false)
#define READ_BYTE() (*ip++)
#define READ_CONSTANT() \
    (frame->closure->function->chunk.constants.values[READ_BYTE()])
#define READ_SHORT() (ip += 2, (uint16_t)((ip[-2] << 8) | ip[-1]))
#define READ_STRING() AS_STRING(READ_CONSTANT())
#define BINARY_OP(valueType, op)                          \
    do {                                                  \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            RUNTIME_ERROR("Operands must be numbers.");   \
        }                                                 \
        double b = AS_NUMBER(pop());                      \
        double a = AS_NUMBER(pop());                      \
        push(valueType(a op b));                          \
    } while (false)

    while (true) {
#ifdef HELIUM_DEBUG
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
#endif

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
                    RUNTIME_ERROR("Undefined variable '%s'.", name->chars);
                }

                if (!IS_VARIABLE(value)) {
                    RUNTIME_ERROR("Internal error: expected variable.",
                                  name->chars);
                }
                ObjVariable* var = AS_VARIABLE(value);

                if (var->isConst) {
                    RUNTIME_ERROR("Cannot assign to const variable '%s'.",
                                  name->chars);
                }

                var->value = peek(0);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;
                if (!tableGet(&vm.globals, name, &value)) {
                    RUNTIME_ERROR("Undefined variable '%s'.", name->chars);
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
                Value value = peek(0);

                push(OBJ_VAL(name));

                ObjVariable* variable = newVariable(value, false);
                push(OBJ_VAL(variable));

                tableSet(&vm.globals, name, OBJ_VAL(variable));

                pop();  // variable
                pop();  // name
                pop();  // original value

                break;
            }

            case OP_DEFINE_GLOBAL_CONST: {
                ObjString* name = READ_STRING();
                Value value = peek(0);

                push(OBJ_VAL(name));

                ObjVariable* variable = newVariable(value, true);
                push(OBJ_VAL(variable));

                tableSet(&vm.globals, name, OBJ_VAL(variable));

                pop();  // variable
                pop();  // name
                pop();  // original value

                break;
            }
            case OP_GET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                push(*frame->closure->upvalues[slot]->location);
                break;
            }
            case OP_SET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                *frame->closure->upvalues[slot]->location = peek(0);
                break;
            }

            case OP_CREATE_MAP: {
                ObjHashMap* hashMap = newHashMap();
                push(OBJ_VAL(hashMap));
                break;
            }
            case OP_CREATE_ARRAY: {
                uint8_t capacity = READ_BYTE();
                ObjArray* array = newArray((int)capacity);
                push(OBJ_VAL(array));
                break;
            }

            case OP_GET_PROPERTY: {
                if (!IS_OBJ(peek(0))) {
                    RUNTIME_ERROR("Only instances and maps have fields.");
                }
                Obj* target = AS_OBJ(peek(0));
                ObjString* name = READ_STRING();
                Value value;
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        ObjInstance* instance = (ObjInstance*)target;
                        if (tableGet(&instance->fields, name, &value)) {
                            pop();
                            push(value);
                        } else if (!bindMethod(instance->klass, name)) {
                            pop();
                            push(NULL_VAL);  // return null as default
                        }
                        break;
                    }
                    case OBJ_HASHMAP: {
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        if (tableGet(&hashMap->map, name, &value)) {
                            pop();
                            push(value);
                        } else {
                            pop();
                            push(NULL_VAL);  // return null as default
                        }
                        break;
                    }
                    case OBJ_ARRAY: {
                        ObjArray* array = (ObjArray*)target;
                        if (name == vm.pushString) {
                            pop();  // remove array
                            push(OBJ_VAL(
                                newArrayMethod(array, ARRAY_METHOD_PUSH)));
                        } else if (name == vm.popString) {
                            pop();
                            push(OBJ_VAL(
                                newArrayMethod(array, ARRAY_METHOD_POP)));
                        } else {
                            RUNTIME_ERROR("Unknown array method %s",
                                          name->chars);
                        }
                        break;
                    }
                    default: {
                        RUNTIME_ERROR("Only instances and maps have fields.");
                        break;
                    }
                }

                break;
            }
            case OP_SET_PROPERTY: {
                if (!IS_OBJ(peek(1))) {
                    RUNTIME_ERROR("Only instances and maps have fields.");
                }
                Obj* target = AS_OBJ(peek(1));
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        ObjInstance* instance = (ObjInstance*)target;
                        tableSet(&instance->fields, READ_STRING(), peek(0));
                        break;
                    }
                    case OBJ_HASHMAP: {
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        tableSet(&hashMap->map, READ_STRING(), peek(0));
                        break;
                    }
                    default: {
                        RUNTIME_ERROR("Only instances and maps have fields.");
                        break;
                    }
                }
                Value value = pop();
                pop();
                push(value);
                break;
            }
            case OP_INVOKE: {
                ObjString* method = READ_STRING();
                int argCount = READ_BYTE();
                Value receiver = peek(argCount);

                if (IS_ARRAY(receiver)) {
                    if (!arrayMethodsFromName(AS_ARRAY(receiver), argCount,
                                              method)) {
                        RUNTIME_ERROR("Undefined array method '%s'.",
                                      method->chars);
                    }
                    break;
                }
                frame->ip = ip;
                if (!invoke(method, argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            case OP_GET_INDEX: {
                Value key = pop();

                if (!IS_OBJ(peek(0))) {
                    RUNTIME_ERROR(
                        "Only instances, maps and arrays support indexing.");
                }
                Value value;
                Obj* target = AS_OBJ(peek(0));
                bool get = false;
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjInstance* instance = (ObjInstance*)target;
                        get =
                            tableGet(&instance->fields, AS_STRING(key), &value);
                        break;
                    }
                    case OBJ_HASHMAP: {
                        if (IS_NUMBER(key)) {
                            key = OBJ_VAL(valueToString(key));
                        }
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        get = tableGet(&hashMap->map, AS_STRING(key), &value);
                        break;
                    }
                    case OBJ_ARRAY: {
                        if (!IS_NUMBER(key)) {
                            RUNTIME_ERROR("Index must be a number");
                        }
                        double index = AS_NUMBER(key);

                        if (index < 0 || index != (int)index) {
                            RUNTIME_ERROR(
                                "Array index must be a non-negative integer");
                        }

                        int i = (int)index;
                        ObjArray* array = (ObjArray*)target;

                        if (i >= array->array.count) {
                            RUNTIME_ERROR("Array index out of bounds");
                        }
                        value = array->array.values[i];
                        get = true;
                        break;
                    }
                    default: {
                        RUNTIME_ERROR(
                            "Only instances, maps and arrays support "
                            "indexing.");
                        break;
                    }
                }

                if (get) {
                    pop();
                    push(value);
                } else {
                    pop();
                    push(NULL_VAL);
                }

                break;
            }

            case OP_SET_INDEX: {
                Value value = peek(0);
                Value key = peek(1);

                if (!IS_OBJ(peek(2))) {
                    RUNTIME_ERROR(
                        "Only instances, maps and arrays support indexing.");
                }
                Obj* target = AS_OBJ(peek(2));
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjInstance* instance = (ObjInstance*)target;
                        tableSet(&instance->fields, AS_STRING(key), value);
                        break;
                    }
                    case OBJ_HASHMAP: {
                        if (IS_NUMBER(key)) {
                            key = OBJ_VAL(valueToString(key));
                        }
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        tableSet(&hashMap->map, AS_STRING(key), value);
                        break;
                    }
                    case OBJ_ARRAY: {
                        if (!IS_NUMBER(key)) {
                            RUNTIME_ERROR("Index must be a number");
                        }
                        double index = AS_NUMBER(key);

                        if (index < 0 || index != (int)index) {
                            RUNTIME_ERROR(
                                "Array index must be a non-negative integer");
                        }

                        int i = (int)index;
                        ObjArray* array = (ObjArray*)target;

                        if (i >= array->array.count) {
                            RUNTIME_ERROR("Array index out of bounds");
                        }
                        array->array.values[i] = value;
                        break;
                    }
                    default: {
                        RUNTIME_ERROR(
                            "Only instances, maps and arrays support "
                            "indexing.");
                        break;
                    }
                }

                pop();  // value
                pop();  // key
                pop();  // instance

                push(value);

                break;
            }
            case OP_PUSH: {
                Value value = peek(0);
                if (!IS_ARRAY(peek(1))) {
                    RUNTIME_ERROR("Only arrays support push.");
                }
                ObjArray* array = AS_ARRAY(peek(1));

                writeValueArray(&array->array, value);
                pop();  // value
                break;
            }
            case OP_INHERIT: {
                Value superclass = peek(1);
                if (!IS_CLASS(superclass)) {
                    RUNTIME_ERROR("Superclass must be a class.");
                }
                ObjClass* subclass = AS_CLASS(peek(0));
                tableAddAll(&AS_CLASS(superclass)->methods, &subclass->methods);
                subclass->initializer = AS_CLASS(superclass)->initializer;
                pop();  // subclass
                break;
            }
            case OP_GET_SUPER: {
                ObjString* name = READ_STRING();
                ObjClass* superclass = AS_CLASS(pop());

                if (!bindMethod(superclass, name)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUPER_INVOKE: {
                ObjString* method = READ_STRING();
                int argCount = READ_BYTE();
                ObjClass* superclass = AS_CLASS(pop());
                if (!invokeFromClass(superclass, method, argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame->ip = ip;
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
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
                    RUNTIME_ERROR("Operands must be numbers or strings.");
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
                if (IS_NUMBER(peek(0)) && AS_NUMBER(peek(0)) == 0) {
                    RUNTIME_ERROR("Division by zero.");
                }
                BINARY_OP(NUMBER_VAL, /);
                break;
            case OP_MODULO: {
                if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) {
                    RUNTIME_ERROR("Operands must be numbers.");
                }
                if (AS_NUMBER(peek(0)) == 0) {
                    RUNTIME_ERROR("Modulo by zero.");
                }

                double b = AS_NUMBER(pop());
                double a = AS_NUMBER(pop());

                push(NUMBER_VAL(fmod(a, b)));
                break;
            }
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE: {
                if (!IS_NUMBER(peek(0))) {
                    RUNTIME_ERROR("Operand must be a number.");
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

                for (int i = 0; i < closure->upvalueCount; i++) {
                    uint8_t isLocal = READ_BYTE();
                    uint8_t index = READ_BYTE();
                    if (isLocal) {
                        closure->upvalues[i] =
                            captureUpvalue(frame->slots + index);
                    } else {
                        closure->upvalues[i] = frame->closure->upvalues[index];
                    }
                }

                break;
            }
            case OP_CLOSE_UPVALUE:
                closeUpvalues(vm.stackTop - 1);
                pop();
                break;
            case OP_RETURN: {
                Value result = pop();
                closeUpvalues(frame->slots);
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
            case OP_CLASS: {
                push(OBJ_VAL(newClass(READ_STRING())));
                break;
            }
            case OP_METHOD:
                defineMethod(READ_STRING());
                break;
            case OP_DUP:
                push(peek(0));
                break;
            case OP_DUP2:
                push(peek(1));
                push(peek(1));
                break;
            case OP_SWAP:
                swap(READ_BYTE());
                break;
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

void swap(uint8_t offset) {
    if ((size_t)(vm.stackTop - vm.stack) < (size_t)offset + 2) {
        runtimeError("Stack underflow error.");
        return;
    }

    Value temp = vm.stackTop[-1 - offset];
    vm.stackTop[-1 - offset] = vm.stackTop[-2 - offset];
    vm.stackTop[-2 - offset] = temp;
}

Value pop() {
    if (vm.stackTop == vm.stack) {
        runtimeError("Stack underflow error.");
    }
    return *--vm.stackTop;
}
