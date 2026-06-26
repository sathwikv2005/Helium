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

static void printChar(const char c) {
    putchar(c);
    vm.atLineStart = (c == '\n');
}

static Value printfNative(int argCount, Value* args) {
    if (argCount < 1) {
        runtimeError("printf() expects 1 or more arguments.");
        return NULL_VAL;
    }
    if (!IS_STRING(args[0])) {
        runtimeError("printf() expects a string.");
        return NULL_VAL;
    }
    ObjString* format = AS_STRING(args[0]);
    const char* chars = format->chars;

    int nextArg = 1;
    while (*chars) {
        if (*chars == '\\') {
            chars++;

            switch (*chars) {
                case '{':
                    printChar('{');
                    break;
                case '}':
                    printChar('}');
                    break;
                case 'n':
                    printChar('\n');
                    break;
                case 't':
                    printChar('\t');
                    break;
                case '\\':
                    printChar('\\');
                    break;
                case '\0':
                    runtimeError("Invalid escape sequence.");
                    return NULL_VAL;
                default:
                    printChar('\\');
                    printChar(*chars);
                    break;
            }

            chars++;
            continue;
        }

        if (*chars == '{') {
            const char* p = chars + 1;

            while (*p == ' ' || *p == '\t') p++;

            if (*p == '}') {
                if (nextArg >= argCount) {
                    runtimeError("Not enough arguments for format string.");
                    return NULL_VAL;
                }

                printValue(args[nextArg++]);
                chars = p + 1;
                vm.atLineStart = false;
                continue;
            }
        }

        printChar(*chars++);
    }

    if (nextArg != argCount) {
        runtimeError("Too many arguments for format string.");
        return NULL_VAL;
    }

    return NULL_VAL;
}

void registerSystemNatives() {
    defineNative("printf", printfNative);
    defineNative("time", timeNative);
    defineNative("clock", clockNative);
    defineNative("sleep", sleepNative);
}