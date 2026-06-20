#include <stdlib.h>

#include "native_common.h"

static Value stringNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("string() expects 1 argument.");
        return NULL_VAL;
    }

    return valueToString(args[0]);
}

static Value numberNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("number() expects 1 argument.");
        return NULL_VAL;
    }

    if (!IS_STRING(args[0])) {
        runtimeError("number() expects a string.");
        return NULL_VAL;
    }

    ObjString* str = AS_STRING(args[0]);

    char* end;
    double value = strtod(str->chars, &end);

    if (end == str->chars) {
        runtimeError("Invalid number: '%s'.", str->chars);
        return NULL_VAL;
    }

    return NUMBER_VAL(value);
}

void registerTypeNatives() {
    defineNative("string", stringNative);
    defineNative("number", numberNative);
}