#include <math.h>
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

static Value intNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("int() expects 1 argument.");
        return NULL_VAL;
    }
    if (IS_NUMBER(args[0])) {
        return NUMBER_VAL(trunc(AS_NUMBER(args[0])));
    }
    if (IS_STRING(args[0])) {
        ObjString* str = AS_STRING(args[0]);

        char* end;
        double value = strtod(str->chars, &end);

        if (end == str->chars) {
            runtimeError("Invalid number: '%s'.", str->chars);
            return NULL_VAL;
        }

        return NUMBER_VAL(trunc(value));
    }

    runtimeError("int() expects a number or a string");
    return NULL_VAL;
}

void registerTypeNatives() {
    defineNative("string", stringNative);
    defineNative("int", intNative);
    defineNative("number", numberNative);
}