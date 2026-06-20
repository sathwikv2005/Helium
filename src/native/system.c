#include <time.h>

#include "native_common.h"

static Value timeNative(int argCount, Value* args) {
    if (argCount != 0) {
        runtimeError("time() expects no arguments");
        return NULL_VAL;
    }
    return NUMBER_VAL((double)time(NULL));
}

static Value clockNative(int argCount, Value* args) {
    if (argCount != 0) {
        runtimeError("clock() expects no arguments");
        return NULL_VAL;
    }
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

void registerSystemNatives() {
    defineNative("time", timeNative);
    defineNative("clock", clockNative);
}