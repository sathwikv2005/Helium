#include "modules_common.h"

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
    Value value;

    if (tableGet(&vm.builtins, path, &value)) {
        return AS_MODULE(value);
    }

    char* source = readFile(path->chars);

    if (source == NULL) {
        runtimeError("Could not find module '%s'.", path->chars);
        return NULL;
    }

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

void defineNativeModule(ObjString* name, ObjModule* module) {
    push(OBJ_VAL(module));
    push(OBJ_VAL(name));
    tableSet(&vm.builtins, name, OBJ_VAL(module));
    pop();
    pop();
}

ObjModule* newNativeModule(ObjString* name) {
    ObjModule* module = newModule(name);
    return module;
}

void defineNativeValue(ObjModule* module, const char* name, Value value) {
    ObjVariable* var = newVariable(value, true);

    var->isExported = true;

    ObjString* key = copyString(name, (int)strlen(name));

    push(OBJ_VAL(key));
    push(OBJ_VAL(var));

    tableSet(&module->globals, key, OBJ_VAL(var));

    pop();
    pop();
}

void defineNativeFunction(ObjModule* module, const char* name, NativeFn fn) {
    ObjString* fnName = copyString(name, (int)strlen(name));

    ObjNative* native = newNative(fn);

    defineNativeValue(module, name, OBJ_VAL(native));
}

void mapModules() { mathModule(); }