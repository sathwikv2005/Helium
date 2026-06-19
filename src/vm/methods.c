#include "vm_common.h"

static bool sortDescending = false;

static int compareValues(const void* a, const void* b) {
    double da = AS_NUMBER(*(const Value*)a);
    double db = AS_NUMBER(*(const Value*)b);

    int result = (da > db) - (da < db);

    return sortDescending ? -result : result;
}

bool arrayMethods(ObjArray* receiver, int argCount, ArrayMethodType type) {
    switch (type) {
        case ARRAY_METHOD_PUSH:
            if (argCount != 1) {
                runtimeError("push() expects 1 argument.");
                return false;
            }

            writeValueArray(&receiver->array, peek(0));

            vm.stackTop -= argCount + 1;
            push(OBJ_VAL(receiver));
            return true;

        case ARRAY_METHOD_POP: {
            if (argCount > 1) {
                runtimeError("pop() expects 0 or 1 arguments.");
                return false;
            }
            int offset = 0;

            if (argCount != 0) {
                Value arg = vm.stackTop[-1];
                if (!IS_NUMBER(arg)) {
                    runtimeError("pop() expects a number.");
                    return false;
                }
                double index = AS_NUMBER(arg);

                if (index < 0 || index != (int)index) {
                    runtimeError(
                        "Array index must be a non-negative "
                        "integer");
                    return false;
                }

                offset = (int)index;
            }
            if (offset >= receiver->array.count) {
                runtimeError("Array index out of bounds.");
                return false;
            }
            receiver->array.count -= (1 + offset);

            vm.stackTop -= argCount + 1;

            push(OBJ_VAL(receiver));
            return true;
        }
        case ARRAY_METHOD_LENGTH: {
            if (argCount != 0) {
                runtimeError("lenght() expects no arguments.");
                return false;
            }
            vm.stackTop -= argCount + 1;
            push(NUMBER_VAL(receiver->array.count));
            return true;
        }
        case ARRAY_METHOD_SORT: {
            if (argCount > 1) {
                runtimeError("sort() expects 0 or 1 arguments.");
                return false;
            }
            sortDescending = false;
            ValueArray* array = &receiver->array;
            for (int i = 0; i < array->count; i++) {
                if (!IS_NUMBER(array->values[i])) {
                    runtimeError(
                        "Array.sort() only supports arrays of numbers.");
                    return false;
                }
            }
            if (argCount == 1) {
                Value arg = vm.stackTop[-1];

                if (!IS_BOOL(arg)) {
                    runtimeError("sort() expects a boolean.");
                    return false;
                }

                sortDescending = AS_BOOL(arg);
            }
            qsort(array->values, array->count, sizeof(Value), compareValues);
            vm.stackTop -= argCount + 1;
            push(OBJ_VAL(receiver));
            return true;
        }
    }
    return false;
}

bool arrayMethodsFromName(ObjArray* receiver, int argCount, ObjString* method) {
    if (method == vm.pushString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_PUSH);
    }
    if (method == vm.popString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_POP);
    }
    if (method == vm.lengthString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_LENGTH);
    }
    if (method == vm.sortString) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_SORT);
    }
    runtimeError("Undefined array method '%s'.", method->chars);
    return false;
}

void defineMethod(ObjString* name) {
    Value method = peek(0);
    ObjClass* klass = AS_CLASS(peek(1));
    if (name == vm.initString) {
        klass->initializer = AS_CLOSURE(method);
    } else {
        tableSet(&klass->methods, name, method);
    }
    pop();
}
