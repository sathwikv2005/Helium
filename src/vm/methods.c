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

void initSpecialStrings() {
    for (int i = 0; i < SPECIAL_COUNT; i++) {
        vm.specialStrings[i] = NULL;
    }

    vm.specialStrings[SPECIAL_INIT] = copyString("init", 4);
    vm.specialStrings[SPECIAL_PUSH] = copyString("push", 4);
    vm.specialStrings[SPECIAL_POP] = copyString("pop", 3);
    vm.specialStrings[SPECIAL_LENGTH] = copyString("length", 6);
    vm.specialStrings[SPECIAL_SORT] = copyString("sort", 4);
    vm.specialStrings[SPECIAL_SUBSTR] = copyString("substr", 6);
    vm.specialStrings[SPECIAL_TOLOWER] = copyString("toLower", 7);
    vm.specialStrings[SPECIAL_TOUPPER] = copyString("toUpper", 7);
    vm.specialStrings[SPECIAL_ISEMPTY] = copyString("isEmpty", 7);
}