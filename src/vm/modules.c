#include "vm_common.h"

bool invokeModuleMethod(ObjModule* module, int argCount, ObjString* name) {
    Value value;

    if (!tableGet(&module->globals, name, &value)) return false;

    if (!IS_VARIABLE(value)) {
        runtimeError("Can only invoke exported globals.");
        return false;
    }

    ObjVariable* var = AS_VARIABLE(value);

    if (!var->isExported) {
        runtimeError("%s is not exported.", name->chars);
        return false;
    }

    value = var->value;

    if (IS_CLOSURE(value)) {
        AS_CLOSURE(value)->module = module;
    }

    vm.stackTop[-argCount - 1] = value;

    return callValue(value, argCount);
}

ObjModule* loadModule(ObjString* path) {
    char* source = readFile(path->chars);

    ObjModule* module = newModule(path);

    ObjFunction* function = compileModule(source, module);
    if (function == NULL) {
        free(source);
        return NULL;
    }

    ObjClosure* closure = newClosure(function);
    closure->module = module;

    push(OBJ_VAL(closure));
    callValue(OBJ_VAL(closure), 0);

    free(source);

    return module;
}