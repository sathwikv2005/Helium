#include "native_common.h"

static Value throwErrorNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("runtimeError() expects 1 argument.");
        return NULL_VAL;
    }
    Value str = valueToString(args[0]);
    runtimeError(AS_CSTRING(args[0]));
    return NULL_VAL;
}

static Value assertNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("assert() expects 1 argument.");
        return NULL_VAL;
    }
    if (isFalsey(args[0])) {
        runtimeError("Assertion failed: expected a truthy value, got %s",
                     AS_CSTRING(valueToString(args[0])));
        return FALSE_VAL;
    }
    return TRUE_VAL;
}

static Value exitNative(int argCount, Value* args) {
    if (argCount > 0) {
        if (!IS_NUMBER(args[0])) {
            runtimeError("exit() expects a number.");
        }

        vm.exitCode = (int)AS_NUMBER(args[0]);
    } else {
        vm.exitCode = 0;
    }
    longjmp(vm.vmJump, JUMP_EXIT);

    return NULL_VAL;
}

void registerRuntimeNatives() {
    defineNative("throwError", throwErrorNative);
    defineNative("assert", assertNative);
    defineNative("exit", exitNative);
}