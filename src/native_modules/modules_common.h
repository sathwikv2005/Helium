#ifndef helium_native_modules_common
#define helium_native_modules_common

#include <stdlib.h>

#include "../../include/compiler.h"
#include "../../include/memory.h"
#include "../../include/nativeModules.h"
#include "../../include/object.h"
#include "../../include/vm.h"

void defineNativeModule(ObjString* name, ObjModule* module);
void defineNativeFunction(ObjModule* module, const char* name, NativeFn fn);
void defineNativeValue(ObjModule* module, const char* name, Value value);
ObjModule* newNativeModule(ObjString* name);
void mathModule();

#endif