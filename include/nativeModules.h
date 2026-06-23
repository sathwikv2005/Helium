#ifndef helium_nativeModules_h
#define helium_nativeModules_h

bool invokeModuleMethod(ObjModule* module, int argCount, ObjString* name);
ObjModule* loadModule(ObjString* path);
void mapModules();

#endif