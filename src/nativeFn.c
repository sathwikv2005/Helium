#include "../include/nativeFn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/memory.h"
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

    Value value = args[0];
    char buffer[32];

    if (IS_BOOL(value)) {
        return OBJ_VAL(copyString(AS_BOOL(value) ? "true" : "false",
                                  AS_BOOL(value) ? 4 : 5));
    }

    if (IS_NULL(value)) {
        return OBJ_VAL(copyString("null", 4));
    }

    if (IS_NUMBER(value)) {
        int length =
            snprintf(buffer, sizeof(buffer), "%.15g", AS_NUMBER(value));
        return OBJ_VAL(copyString(buffer, length));
    }

    Obj* obj = AS_OBJ(value);

    switch (obj->type) {
        case OBJ_STRING:
            return value;

        case OBJ_FUNCTION:
        case OBJ_CLOSURE:
            return OBJ_VAL(copyString("<fn>", 4));

        case OBJ_NATIVE:
            return OBJ_VAL(copyString("<native fn>", 11));

        case OBJ_UPVALUE:
            return OBJ_VAL(copyString("<upvalue>", 9));

        case OBJ_VARIABLE:
            return OBJ_VAL(copyString("<variable>", 10));

        case OBJ_CLASS: {
            ObjClass* klass = (ObjClass*)obj;
            return OBJ_VAL(copyString(klass->name->chars, klass->name->length));
        }

        case OBJ_INSTANCE: {
            ObjInstance* instance = (ObjInstance*)obj;

            char buffer[256];
            int length = snprintf(buffer, sizeof(buffer), "%s instance",
                                  instance->klass->name->chars);

            return OBJ_VAL(copyString(buffer, length));
        }

        case OBJ_BOUND_METHOD:
            return OBJ_VAL(copyString("<bound method>", 14));
    }

    return NULL_VAL;
}

void mapNatives() {
    defineNative("time", timeNative);
    defineNative("clock", clockNative);
    defineNative("input", inputNative);
    defineNative("number", numberNative);
    defineNative("string", stringNative);
}