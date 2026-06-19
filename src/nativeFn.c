#include "../include/nativeFn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/memory.h"
#include "../include/object.h"
#include "../include/vm.h"

static void defineNative(const char* name, NativeFn function) {
    push(OBJ_VAL(copyString(name, (int)strlen(name))));
    push(OBJ_VAL(newNative(function)));
    tableSet(&vm.globals, AS_STRING(vm.stack[0]), vm.stack[1]);
    pop();
    pop();
}

static Value timeNative(int argCount, Value* args) {
    return NUMBER_VAL((double)time(NULL));
}

static Value clockNative(int argCount, Value* args) {
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

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

static Value stringNative(int argCount, Value* args) {
    if (argCount != 1) {
        runtimeError("string() expects 1 argument.");
        return NULL_VAL;
    }

    return valueToString(args[0]);
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

void mapNatives() {
    defineNative("time", timeNative);
    defineNative("clock", clockNative);
    defineNative("input", inputNative);
    defineNative("number", numberNative);
    defineNative("string", stringNative);
    defineNative("len", lenNative);
}