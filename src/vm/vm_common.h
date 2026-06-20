#ifndef helium_vm_common
#define helium_vm_common

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/common.h"
#include "../../include/compiler.h"
#include "../../include/debug.h"
#include "../../include/memory.h"
#include "../../include/nativeFn.h"
#include "../../include/object.h"
#include "../../include/vm.h"

// util
Value peek(int distance);
bool isFalsey(Value value);
void concatenate();
void resetStack();

// call
bool callValue(Value callee, int argCount);
bool invoke(ObjString* name, int argCount);
bool invokeFromClass(ObjClass* klass, ObjString* name, int argCount);
bool bindMethod(ObjClass* klass, ObjString* name);

// closure
ObjUpvalue* captureUpvalue(Value* local);
void closeUpvalues(Value* last);

// methods
void removeArgs(int argCount);
void defineMethod(ObjString* name);

// array methods
bool arrayMethods(ObjArray* receiver, int argCount, ArrayMethodType type);
bool arrayMethodsFromName(ObjArray* receiver, int argCount, ObjString* method);

// string methods
bool stringMethodsFromName(ObjString* receiver, int argCount,
                           ObjString* method);

#endif