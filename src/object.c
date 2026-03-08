#include "../include/object.h"

#include <stdio.h>
#include <string.h>

#include "../include/memory.h"
#include "../include/value.h"
#include "../include/vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;
    object->next = vm.objects;
    vm.objects = object;
    return object;
}

static ObjString* allocateString(char* chars, int length) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    return string;
}

ObjString* takeString(char* chars, int length) {
    return allocateString(chars, length);
}

ObjString* copyString(const char* chars, int length) {
    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

ObjString* valueToString(Value value) {
    if (IS_STRING(value)) {
        return AS_STRING(value);
    }

    if (IS_BOOL(value)) {
        if (AS_BOOL(value)) {
            return copyString("true", 4);
        } else {
            return copyString("false", 5);
        }
    }

    if (IS_NUMBER(value)) {
        char buffer[32];
        int len = snprintf(buffer, sizeof(buffer), "%g", AS_NUMBER(value));
        return copyString(buffer, len);
    }

    return copyString("null", 4);
}