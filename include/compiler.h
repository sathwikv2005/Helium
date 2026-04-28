#ifndef helium_compiler_h
#define helium_compiler_h

#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);

#endif