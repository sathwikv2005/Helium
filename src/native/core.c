#include <stdio.h>

#include "native_common.h"

static Value inputNative(int argCount, Value* args) {
    if (argCount > 1) {
        runtimeError("input() expects 0 or 1 arguments.");
        return NULL_VAL;
    }
    if (argCount > 0) {
        printValue(args[0]);
    }

    int capacity = 64;
    int length = 0;
    char* buffer = ALLOCATE(char, capacity);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            int oldCapacity = capacity;
            capacity = GROW_CAPACITY(capacity);
            buffer = GROW_ARRAY(char, buffer, oldCapacity, capacity);
        }

        buffer[length++] = (char)c;
    }

    buffer[length] = '\0';

    Value result = OBJ_VAL(copyString(buffer, length));

    FREE_ARRAY(char, buffer, capacity);

    return result;
}

static Value lenNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("len() expects 1 argument.");
        return NULL_VAL;
    }

    if (!IS_OBJ(args[0])) {
        runtimeError("Object has no length.");
        return NULL_VAL;
    }

    switch (OBJ_TYPE(args[0])) {
        case OBJ_STRING:
            return NUMBER_VAL(AS_STRING(args[0])->length);

        case OBJ_HASHMAP:
            return NUMBER_VAL(AS_HASHMAP(args[0])->map.size);

        case OBJ_ARRAY:
            return NUMBER_VAL(AS_ARRAY(args[0])->array.count);

        default:
            runtimeError("Object has no length.");
            return NULL_VAL;
    }
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

void registerCoreNatives() {
    defineNative("printf", printfNative);
    defineNative("input", inputNative);
    defineNative("len", lenNative);
}