#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <time.h>

#include "native_common.h"

static Value timeNative(int argCount, Value* args) {
    if (argCount != 0) {
        runtimeError("time() expects no arguments.");
        return NULL_VAL;
    }
    return NUMBER_VAL((double)time(NULL));
}

static Value clockNative(int argCount, Value* args) {
    if (argCount != 0) {
        runtimeError("clock() expects no arguments.");
        return NULL_VAL;
    }
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

static Value sleepNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("sleep() expects 1 argument.");
        return NULL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("sleep() expects a number.");
        return NULL_VAL;
    }
    double ms = AS_NUMBER(args[0]);

    if (ms < 0) {
        runtimeError("sleep() duration cannot be negative.");
        return NULL_VAL;
    }

#ifdef _WIN32
    Sleep((DWORD)ms);
#else
    struct timespec ts;
    ts.tv_sec = (time_t)(ms / 1000);
    ts.tv_nsec = (long)((ms - ts.tv_sec * 1000) * 1000000.0);
    nanosleep(&ts, NULL);
#endif

    return NULL_VAL;
}

void registerSystemNatives() {
    defineNative("time", timeNative);
    defineNative("clock", clockNative);
    defineNative("sleep", sleepNative);
}