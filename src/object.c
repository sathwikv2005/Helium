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

void printArray(ObjArray* array) {
    printf("[ ");
    if (array->array.count == 0) {
        printf("]");
        return;
    }
    Value* values = array->array.values;
    int i;
    for (i = 0; i < array->array.count - 1; i++) {
        printValue(values[i]);
        printf(", ");
    }
    printValue(values[i]);
    printf(" ]");
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
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

Value valueToString(Value value) {
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
        case OBJ_HASHMAP:
            return OBJ_VAL(copyString("<map>", 5));
        case OBJ_ARRAY:
            return arrayToString(AS_ARRAY(value));
        case OBJ_ARRAY_METHOD:
            return OBJ_VAL(copyString("<array method>", 14));
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