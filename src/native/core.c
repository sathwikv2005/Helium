#include <stdio.h>

#include "native_common.h"

static Value inputNative(int argCount, Value* args) {
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

void registerCoreNatives() {
    defineNative("input", inputNative);
    defineNative("len", lenNative);
}