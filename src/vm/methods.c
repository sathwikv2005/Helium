#include "vm_common.h"

void removeArgs(int argCount) { vm.stackTop -= argCount + 1; }

void defineMethod(ObjString* name) {
    Value method = peek(0);
    ObjClass* klass = AS_CLASS(peek(1));
    if (name == vm.specialStrings[SPECIAL_INIT]) {
        klass->initializer = AS_CLOSURE(method);
    } else {
        tableSet(&klass->methods, name, method);
    }
    pop();
}
