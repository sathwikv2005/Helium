#include "vm_common.h"

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

Value peek(int distance) { return vm.stackTop[-1 - distance]; }

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

bool isFalsey(Value value) {
    return IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

void concatenate() {
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

void resetStack() {
    vm.stackTop = vm.stack;
    vm.openUpvalues = NULL;
    vm.frameCount = 0;
}