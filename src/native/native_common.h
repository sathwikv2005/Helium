#ifndef helium_native_common
#define helium_native_common

#include "../../include/memory.h"
#include "../../include/nativeFn.h"
#include "../../include/object.h"
#include "../../include/vm.h"

// nativeFn
void defineNative(const char* name, NativeFn function);

// runtime
void registerRuntimeNatives();

// core
void registerCoreNatives();

// system
void registerSystemNatives();

// type
void registerTypeNatives();

#endif