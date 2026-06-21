#include <string.h>

#include "vm_common.h"

static bool getIntegerArg(Value value, const char* name, int* out) {
    if (!IS_NUMBER(value)) {
        runtimeError("%s must be a number.", name);
        return false;
    }

    double number = AS_NUMBER(value);

    if ((int)number != number) {
        runtimeError("%s must be an integer.", name);
        return false;
    }

    *out = (int)number;
    return true;
}

static bool substrMethod(ObjString* receiver, int argCount) {
    if (argCount < 1 || argCount > 2) {
        runtimeError("substr() expects 1 or 2 arguments.");
        return false;
    }

    int start;
    if (!getIntegerArg(vm.stackTop[-argCount], "substr() start index",
                       &start)) {
        return false;
    }

    int length = receiver->length - start;

    if (argCount == 2) {
        if (!getIntegerArg(vm.stackTop[-1], "substr() length", &length)) {
            return false;
        }
    }

    if (start < 0) {
        runtimeError("substr() start index cannot be negative.");
        return false;
    }

    if (length < 0) {
        runtimeError("substr() length cannot be negative.");
        return false;
    }

    if (start > receiver->length) {
        runtimeError("substr() start index out of bounds.");
        return false;
    }

    if (length > receiver->length - start) {
        runtimeError("substr() range out of bounds.");
        return false;
    }

    ObjString* result = copyString(receiver->chars + start, length);

    removeArgs(argCount);
    push(OBJ_VAL(result));

    return true;
}
static bool toUpperMethod(ObjString* receiver, int argCount) {
    if (argCount != 0) {
        runtimeError("toUpper() expects no arguments.");
        return false;
    }

    int length = receiver->length;
    char* chars = ALLOCATE(char, length + 1);

    for (int i = 0; i < length; i++) {
        char c = receiver->chars[i];

        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        }

        chars[i] = c;
    }

    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    push(OBJ_VAL(result));
    return true;
}

static bool toLowerMethod(ObjString* receiver, int argCount) {
    if (argCount != 0) {
        runtimeError("toLower() expects no arguments.");
        return false;
    }

    int length = receiver->length;
    char* chars = ALLOCATE(char, length + 1);

    for (int i = 0; i < length; i++) {
        char c = receiver->chars[i];

        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }

        chars[i] = c;
    }

    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    push(OBJ_VAL(result));
    return true;
}

static bool isEmptyMethod(ObjString* receiver, int argCount) {
    if (argCount != 0) {
        runtimeError("isEmpty() expects no arguments.");
        return false;
    }
    removeArgs(argCount);
    push(BOOL_VAL(receiver->length == 0));
    return true;
}

// prevents the C compiler from inlining this function into the VM's dispatch
// loop.
//  With GCC -O3 -flto, inlining causes a significant performance impact in
//  interpreter's runtime errors even when this function never executes.
HELIUM_NOINLINE
bool stringMethodsFromName(ObjString* receiver, int argCount,
                           ObjString* method) {
    if (method == vm.specialStrings[SPECIAL_SUBSTR]) {
        return substrMethod(receiver, argCount);
    }
    if (method == vm.specialStrings[SPECIAL_TOLOWER]) {
        return toLowerMethod(receiver, argCount);
    }
    if (method == vm.specialStrings[SPECIAL_TOUPPER]) {
        return toUpperMethod(receiver, argCount);
    }
    if (method == vm.specialStrings[SPECIAL_ISEMPTY]) {
        return isEmptyMethod(receiver, argCount);
    }

    return false;
}