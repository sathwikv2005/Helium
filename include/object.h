#ifndef helium_object_h
#define helium_object_h

#include "chunk.h"
#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) AS_OBJ(value)->type
#define IS_VARIABLE(value) isObjType(value, OBJ_VARIABLE)
#define IS_STRING(value) isObjType(value, OBJ_STRING)
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)

#define AS_FUNCTION(value) ((ObjFunction*)AS_OBJ(value))
#define AS_VARIABLE(value) ((ObjVariable*)AS_OBJ(value))
#define AS_STRING(value) ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ(value))->chars)

typedef enum { OBJ_STRING, OBJ_VARIABLE, OBJ_FUNCTION } ObjType;

struct Obj {
    ObjType type;
    Obj* next;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

typedef struct {
    Obj obj;
    Value value;
    bool isConst;
} ObjVariable;

typedef struct {
    Obj obj;
    int arity;
    Chunk chunk;
    ObjString* name;
} ObjFunction;

ObjVariable* newVariable(Value value, bool isConst);

ObjFunction* newFunction();

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);
ObjString* valueToString(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif