#include "../include/object.h"

#include <stdio.h>
#include <string.h>

#include "../include/memory.h"
#include "../include/table.h"
#include "../include/value.h"
#include "../include/vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;
    object->isMarked = !vm.currentGCMark;
    object->next = vm.objects;
    vm.objects = object;

#ifdef HELIUM_DEBUG
    if (GET_DEBUG_LOG_GC())
        printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif

    return object;
}

static ObjString* allocateString(char* chars, int length, uint32_t hash) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    string->hash = hash;

    push(OBJ_VAL(string));

    tableSet(&vm.strings, string, NULL_VAL);

    pop();

    return string;
}

static uint32_t hashString(const char* key, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString* takeString(char* chars, int length) {
    uint32_t hash = hashString(chars, length);

    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);

    if (interned != NULL) {
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }

    return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
    uint32_t hash = hashString(chars, length);

    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) return interned;

    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

static void printFunction(ObjFunction* function) {
    if (function->name == NULL) {
        printf("<script>");
        return;
    }
    printf("<fn %s>", function->name->chars);
}

void printString(char* str, bool withQuotes) {
    if (withQuotes) {
        printf("\"%s\"", str);
    } else {
        printf("%s", str);
    }
    return;
}

void printArrayValue(Value value) {
    if (IS_STRING(value)) {
        printString(AS_CSTRING(value), true);
        return;
    }

    printValue(value);
}

void printArray(ObjArray* array) {
    printf("[ ");
    if (array->array.count == 0) {
        printf("]");
        return;
    }
    Value* values = array->array.values;
    int i;
    for (i = 0; i < array->array.count - 1; i++) {
        printArrayValue(values[i]);
        printf(", ");
    }
    printArrayValue(values[i]);
    printf(" ]");
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printString(AS_CSTRING(value), false);
            break;
        case OBJ_UPVALUE:
            printf("upvalue");
            break;
        case OBJ_BOUND_METHOD:
            printFunction(AS_BOUND_METHOD(value)->method->function);
            break;
        case OBJ_CLASS:
            printf("<CLASS %s>", AS_CLASS(value)->name->chars);
            break;
        case OBJ_INSTANCE:
            printf("<%s>", AS_INSTANCE(value)->klass->name->chars);
            break;
        case OBJ_CLOSURE:
            printFunction((AS_CLOSURE(value)->function));
            break;
        case OBJ_FUNCTION:
            printFunction(AS_FUNCTION(value));
            break;
        case OBJ_NATIVE:
            printf("<native fn>");
            break;
        case OBJ_HASHMAP:
            printf("<map>");
            break;
        case OBJ_ARRAY:
            printArray(AS_ARRAY(value));
            break;
        case OBJ_ARRAY_METHOD:
            printf("<array method>");
            break;
        case OBJ_VARIABLE:
            printf("Variable");
            break;
    }
}

ObjString* objType(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            return copyString("string", 6);

        case OBJ_UPVALUE:
            return copyString("upvalue", 7);

        case OBJ_BOUND_METHOD:
            return copyString("function", 8);

        case OBJ_CLASS:
            return copyString("class", 5);

        case OBJ_INSTANCE:
            return copyString("instance", 8);

        case OBJ_CLOSURE:
            return copyString("function", 8);

        case OBJ_FUNCTION:
            return copyString("function", 8);

        case OBJ_NATIVE:
            return copyString("native", 6);

        case OBJ_HASHMAP:
            return copyString("map", 3);

        case OBJ_ARRAY:
            return copyString("array", 5);

        case OBJ_ARRAY_METHOD:
            return copyString("array_method", 12);

        case OBJ_VARIABLE:
            return copyString("variable", 8);
    }

    return copyString("unknown type", 12);
}

static Value arrayToString(ObjArray* array) {
    if (array->array.count == 0) {
        return OBJ_VAL(copyString("[]", 2));
    }

    int capacity = 64;
    int length = 0;
    char* chars = ALLOCATE(char, capacity);

    chars[length++] = '[';

    for (int i = 0; i < array->array.count; i++) {
        Value value = array->array.values[i];

        ObjString* string = AS_STRING(valueToString(value));

        int strLength = string->length;

        while (length + strLength + 3 >= capacity) {
            int oldCapacity = capacity;
            capacity *= 2;
            chars = GROW_ARRAY(char, chars, oldCapacity, capacity);
        }

        memcpy(chars + length, string->chars, strLength);
        length += strLength;

        if (i != array->array.count - 1) {
            chars[length++] = ',';
            chars[length++] = ' ';
        }
    }

    chars[length++] = ']';
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    return OBJ_VAL(result);
}

static Value stringValue(const char* chars) {
    return OBJ_VAL(copyString(chars, (int)strlen(chars)));
}

static Value functionToString(ObjFunction* function) {
    if (function->name == NULL) {
        return stringValue("<script>");
    }

    char buffer[256];
    int length =
        snprintf(buffer, sizeof(buffer), "<fn %s>", function->name->chars);

    return OBJ_VAL(copyString(buffer, length));
}

static Value classToString(ObjClass* klass) {
    char buffer[256];
    int length =
        snprintf(buffer, sizeof(buffer), "<CLASS %s>", klass->name->chars);

    return OBJ_VAL(copyString(buffer, length));
}

static Value instanceToString(ObjInstance* instance) {
    char buffer[256];
    int length =
        snprintf(buffer, sizeof(buffer), "<%s>", instance->klass->name->chars);

    return OBJ_VAL(copyString(buffer, length));
}

Value valueToString(Value value) {
    char buffer[32];

    if (IS_BOOL(value)) {
        return stringValue(AS_BOOL(value) ? "true" : "false");
    }

    if (IS_NULL(value)) {
        return stringValue("null");
    }

    if (IS_NUMBER(value)) {
        int length =
            snprintf(buffer, sizeof(buffer), "%.15g", AS_NUMBER(value));
        return OBJ_VAL(copyString(buffer, length));
    }

    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            return value;

        case OBJ_UPVALUE:
            return stringValue("upvalue");

        case OBJ_BOUND_METHOD:
            return functionToString(AS_BOUND_METHOD(value)->method->function);

        case OBJ_CLASS:
            return classToString(AS_CLASS(value));

        case OBJ_INSTANCE:
            return instanceToString(AS_INSTANCE(value));

        case OBJ_CLOSURE:
            return functionToString(AS_CLOSURE(value)->function);

        case OBJ_FUNCTION:
            return functionToString(AS_FUNCTION(value));

        case OBJ_NATIVE:
            return stringValue("<native fn>");

        case OBJ_HASHMAP:
            return stringValue("<map>");

        case OBJ_ARRAY:
            return arrayToString(AS_ARRAY(value));

        case OBJ_ARRAY_METHOD:
            return stringValue("<array method>");

        case OBJ_VARIABLE:
            return stringValue("Variable");
    }

    return NULL_VAL;
}

ObjVariable* newVariable(Value value, bool isConst) {
    ObjVariable* var = ALLOCATE_OBJ(ObjVariable, OBJ_VARIABLE);
    var->value = value;
    var->isConst = isConst;
    return var;
}

ObjBoundMethod* newBoundMethod(Value reciever, ObjClosure* method) {
    ObjBoundMethod* boundMethod =
        ALLOCATE_OBJ(ObjBoundMethod, OBJ_BOUND_METHOD);
    boundMethod->receiver = reciever;
    boundMethod->method = method;
    return boundMethod;
}

ObjClass* newClass(ObjString* name) {
    ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
    klass->name = name;
    initTable(&klass->methods);
    klass->initializer = NULL;
    return klass;
}

ObjInstance* newInstance(ObjClass* klass) {
    ObjInstance* instance = ALLOCATE_OBJ(ObjInstance, OBJ_INSTANCE);
    instance->klass = klass;
    initTable(&instance->fields);
    return instance;
}

ObjClosure* newClosure(ObjFunction* function) {
    ObjUpvalue** upvalues = ALLOCATE(ObjUpvalue*, function->upvalueCount);
    for (int i = 0; i < function->upvalueCount; i++) {
        upvalues[i] = NULL;
    }
    ObjClosure* closure = ALLOCATE_OBJ(ObjClosure, OBJ_CLOSURE);

    closure->function = function;
    closure->upvalues = upvalues;
    closure->upvalueCount = function->upvalueCount;
    return closure;
}

ObjFunction* newFunction() {
    ObjFunction* function = ALLOCATE_OBJ(ObjFunction, OBJ_FUNCTION);
    function->arity = 0;
    function->upvalueCount = 0;
    function->name = NULL;
    initChunk(&function->chunk);
    return function;
}

ObjNative* newNative(NativeFn function) {
    ObjNative* native = ALLOCATE_OBJ(ObjNative, OBJ_NATIVE);
    native->function = function;
    return native;
}

ObjUpvalue* newUpvalue(Value* slot) {
    ObjUpvalue* upvalue = ALLOCATE_OBJ(ObjUpvalue, OBJ_UPVALUE);
    upvalue->location = slot;
    upvalue->next = NULL;
    upvalue->closed = NULL_VAL;
    return upvalue;
}

ObjHashMap* newHashMap() {
    ObjHashMap* hashMap = ALLOCATE_OBJ(ObjHashMap, OBJ_HASHMAP);
    initTable(&hashMap->map);
    return hashMap;
}

ObjArray* newArray(int capacity) {
    ObjArray* array = ALLOCATE_OBJ(ObjArray, OBJ_ARRAY);
    initValueArrayWithCapacity(&array->array, capacity);
    return array;
}

ObjArrayMethod* newArrayMethod(ObjArray* array, ArrayMethodType type) {
    ObjArrayMethod* arrayMethod =
        ALLOCATE_OBJ(ObjArrayMethod, OBJ_ARRAY_METHOD);
    arrayMethod->type = type;
    arrayMethod->receiver = array;
    return arrayMethod;
}