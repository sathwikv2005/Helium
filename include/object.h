#ifndef helium_object_h
#define helium_object_h

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

#define OBJ_TYPE(value) AS_OBJ(value)->type
#define IS_VARIABLE(value) isObjType(value, OBJ_VARIABLE)
#define IS_STRING(value) isObjType(value, OBJ_STRING)
#define IS_CLOSURE(value) isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_NATIVE(value) isObjType(value, OBJ_NATIVE)
#define IS_CLASS(value) isObjType(value, OBJ_CLASS)
#define IS_INSTANCE(value) isObjType(value, OBJ_INSTANCE)
#define IS_BOUND_METHOD(value) isObjType(value, OBJ_BOUND_METHOD)
#define IS_HASHMAP(value) isObjType(value, OBJ_HASHMAP)
#define IS_ARRAY(value) isObjType(value, OBJ_ARRAY)
#define IS_ARRAY_METHOD(value) isObjType(value, OBJ_ARRAY_METHOD)

#define AS_ARRAY_METHOD(value) ((ObjArrayMethod*)AS_OBJ(value))
#define AS_ARRAY(value) ((ObjArray*)AS_OBJ(value))
#define AS_HASHMAP(value) ((ObjHashMap*)AS_OBJ(value))
#define AS_BOUND_METHOD(value) ((ObjBoundMethod*)AS_OBJ(value))
#define AS_INSTANCE(value) ((ObjInstance*)AS_OBJ(value))
#define AS_CLASS(value) ((ObjClass*)AS_OBJ(value))
#define AS_CLOSURE(value) ((ObjClosure*)AS_OBJ(value))
#define AS_FUNCTION(value) ((ObjFunction*)AS_OBJ(value))
#define AS_NATIVE(value) (((ObjNative*)AS_OBJ(value))->function)
#define AS_VARIABLE(value) ((ObjVariable*)AS_OBJ(value))
#define AS_STRING(value) ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ(value))->chars)

typedef enum {
    OBJ_STRING,
    OBJ_UPVALUE,
    OBJ_VARIABLE,
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_CLOSURE,
    OBJ_CLASS,
    OBJ_INSTANCE,
    OBJ_BOUND_METHOD,
    OBJ_HASHMAP,
    OBJ_ARRAY,
    OBJ_ARRAY_METHOD,
} ObjType;

struct Obj {
    ObjType type;
    bool isMarked;
    Obj* next;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

typedef struct ObjUpvalue {
    Obj obj;
    Value* location;
    Value closed;
    struct ObjUpvalue* next;
} ObjUpvalue;

typedef struct {
    Obj obj;
    Value value;
    bool isConst;
} ObjVariable;

typedef struct {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString* name;
} ObjFunction;
typedef struct {
    Obj obj;
    ObjFunction* function;
    ObjUpvalue** upvalues;
    int upvalueCount;
} ObjClosure;

typedef struct {
    Obj obj;
    ObjString* name;
    Table methods;
    ObjClosure* initializer;
} ObjClass;

typedef struct {
    Obj obj;
    ObjClass* klass;
    Table fields;
} ObjInstance;

typedef struct {
    Obj obj;
    Value receiver;
    ObjClosure* method;
} ObjBoundMethod;

typedef struct {
    Obj obj;
    Table map;
} ObjHashMap;

typedef struct {
    Obj obj;
    ValueArray array;
} ObjArray;

typedef enum {
    ARRAY_METHOD_PUSH,
    ARRAY_METHOD_POP,
    ARRAY_METHOD_SORT,
    ARRAY_METHOD_LENGTH,
} ArrayMethodType;

typedef struct {
    Obj obj;
    ObjArray* receiver;
    ArrayMethodType type;
} ObjArrayMethod;

typedef Value (*NativeFn)(int argCount, Value* args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

ObjVariable* newVariable(Value value, bool isConst);
ObjBoundMethod* newBoundMethod(Value receiver, ObjClosure* method);
ObjClass* newClass(ObjString* name);
ObjClosure* newClosure(ObjFunction* function);
ObjFunction* newFunction();
ObjInstance* newInstance(ObjClass* klass);
ObjNative* newNative(NativeFn function);
ObjHashMap* newHashMap();
ObjArray* newArray(int capacity);
ObjArrayMethod* newArrayMethod(ObjArray* array, ArrayMethodType type);

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
ObjUpvalue* newUpvalue(Value* slot);
void printObject(Value value);
Value valueToString(Value value);

void printArray(ObjArray* array);

ObjString* objType(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif