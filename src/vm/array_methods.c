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

            removeArgs(argCount);
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

            removeArgs(argCount);

            push(OBJ_VAL(receiver));
            return true;
        }
        case ARRAY_METHOD_LENGTH: {
            if (argCount != 0) {
                runtimeError("lenght() expects no arguments.");
                return false;
            }
            removeArgs(argCount);
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
            removeArgs(argCount);
            push(OBJ_VAL(receiver));
            return true;
        }
    }
    return false;
}

static bool isEmptyMethod(ObjArray* receiver, int argCount) {
    if (argCount != 0) {
        runtimeError("isEmpty() expects no arguments.");
        return false;
    }
    removeArgs(argCount);
    push(BOOL_VAL(receiver->array.count == 0));
    return true;
}

bool arrayMethodsFromName(ObjArray* receiver, int argCount, ObjString* method) {
    if (method == vm.specialStrings[SPECIAL_PUSH]) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_PUSH);
    }
    if (method == vm.specialStrings[SPECIAL_POP]) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_POP);
    }
    if (method == vm.specialStrings[SPECIAL_LENGTH]) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_LENGTH);
    }
    if (method == vm.specialStrings[SPECIAL_SORT]) {
        return arrayMethods(receiver, argCount, ARRAY_METHOD_SORT);
    }
    if (method == vm.specialStrings[SPECIAL_ISEMPTY]) {
        return isEmptyMethod(receiver, argCount);
    }
    runtimeError("Undefined array method '%s'.", method->chars);
    return false;
}
