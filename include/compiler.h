#ifndef helium_compiler_h
#define helium_compiler_h

#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);
ObjFunction* compileModule(const char* source, ObjModule* module);
void markCompilerRoots();

#endif