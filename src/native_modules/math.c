#include <math.h>

#include "modules_common.h"

static Value sqrtNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("sqrt() expects a number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(sqrt(AS_NUMBER(args[0])));
}

static Value minNative(int argCount, Value* args) {
    if (argCount != 2 || !IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        runtimeError("min() expects 2 numbers.");
        return NULL_VAL;
    }
    double a = AS_NUMBER(args[0]);
    double b = AS_NUMBER(args[1]);
    return NUMBER_VAL(fmin(a, b));
}

static Value maxNative(int argCount, Value* args) {
    if (argCount != 2 || !IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        runtimeError("max() expects 2 numbers.");
        return NULL_VAL;
    }
    double a = AS_NUMBER(args[0]);
    double b = AS_NUMBER(args[1]);
    return NUMBER_VAL(fmax(a, b));
}

static Value absNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("abs() expects 1 number.");
        return NULL_VAL;
    }
    return NUMBER_VAL(fabs(AS_NUMBER(args[0])));
}

static Value randomNative(int argCount, Value* args) {
    if (argCount != 0) {
        runtimeError("random() expects 0 arguments.");
        return NULL_VAL;
    }

    return NUMBER_VAL((double)rand() / ((double)RAND_MAX + 1.0));
}

static Value randomIntNative(int argCount, Value* args) {
    if (argCount != 2 || !IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        runtimeError("randomInt() expects 2 numbers.");
        return NULL_VAL;
    }

    int min = (int)AS_NUMBER(args[0]);
    int max = (int)AS_NUMBER(args[1]);

    if (min > max) {
        runtimeError("randomInt(): min must be <= max.");
        return NULL_VAL;
    }

    return NUMBER_VAL(min + rand() % (max - min + 1));
}

static Value powNative(int argCount, Value* args) {
    if (argCount != 2 || !IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        runtimeError("pow() expects 2 numbers.");
        return NULL_VAL;
    }

    double base = AS_NUMBER(args[0]);
    double exponent = AS_NUMBER(args[1]);

    return NUMBER_VAL(pow(base, exponent));
}

static Value signNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("sign() expects 1 number.");
        return NULL_VAL;
    }

    double x = AS_NUMBER(args[0]);

    if (x > 0) return NUMBER_VAL(1);
    if (x < 0) return NUMBER_VAL(-1);

    return NUMBER_VAL(0);
}

static Value clampNative(int argCount, Value* args) {
    if (argCount != 3 || !IS_NUMBER(args[0]) || !IS_NUMBER(args[1]) ||
        !IS_NUMBER(args[2])) {
        runtimeError("clamp() expects 3 numbers.");
        return NULL_VAL;
    }

    double value = AS_NUMBER(args[0]);
    double min = AS_NUMBER(args[1]);
    double max = AS_NUMBER(args[2]);

    if (min > max) {
        runtimeError("clamp(): min must be <= max.");
        return NULL_VAL;
    }

    if (value < min) value = min;
    if (value > max) value = max;

    return NUMBER_VAL(value);
}

static Value floorNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("floor() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(floor(AS_NUMBER(args[0])));
}

static Value ceilNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("ceil() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(ceil(AS_NUMBER(args[0])));
}

static Value roundNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("round() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(round(AS_NUMBER(args[0])));
}

static Value truncNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("trunc() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(trunc(AS_NUMBER(args[0])));
}

static Value cbrtNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("cbrt() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(cbrt(AS_NUMBER(args[0])));
}

static Value expNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("exp() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(exp(AS_NUMBER(args[0])));
}

static Value degreesNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("degrees() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(AS_NUMBER(args[0]) * 180.0 / HELIUM_PI);
}

static Value radiansNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("radians() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(AS_NUMBER(args[0]) * HELIUM_PI / 180.0);
}

static Value logNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("log() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(log(AS_NUMBER(args[0])));
}

static Value log10Native(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("log10() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(log10(AS_NUMBER(args[0])));
}

static Value log2Native(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("log2() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(log2(AS_NUMBER(args[0])));
}

static Value isNaNNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("isNaN() expects 1 number.");
        return NULL_VAL;
    }

    return BOOL_VAL(isnan(AS_NUMBER(args[0])));
}

static Value sinNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("sin() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(sin(AS_NUMBER(args[0])));
}

static Value cosNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("cos() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(cos(AS_NUMBER(args[0])));
}

static Value tanNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("tan() expects 1 number.");
        return NULL_VAL;
    }

    return NUMBER_VAL(tan(AS_NUMBER(args[0])));
}

void mathModule() {
    ObjModule* module = newNativeModule(vm.specialStrings[SPECIAL_STD_MATH]);

    defineNativeFunction(module, "sqrt", sqrtNative);
    defineNativeFunction(module, "min", minNative);
    defineNativeFunction(module, "max", maxNative);
    defineNativeFunction(module, "abs", absNative);
    defineNativeFunction(module, "random", randomNative);
    defineNativeFunction(module, "randomInt", randomIntNative);
    defineNativeFunction(module, "pow", powNative);
    defineNativeFunction(module, "clamp", clampNative);
    defineNativeFunction(module, "sign", signNative);

    defineNativeFunction(module, "floor", floorNative);
    defineNativeFunction(module, "ceil", ceilNative);
    defineNativeFunction(module, "round", roundNative);
    defineNativeFunction(module, "trunc", truncNative);

    defineNativeFunction(module, "cbrt", cbrtNative);
    defineNativeFunction(module, "exp", expNative);

    defineNativeFunction(module, "degrees", degreesNative);
    defineNativeFunction(module, "radians", radiansNative);

    defineNativeFunction(module, "log", logNative);
    defineNativeFunction(module, "log10", log10Native);
    defineNativeFunction(module, "log2", log2Native);

    defineNativeFunction(module, "isNaN", isNaNNative);

    defineNativeFunction(module, "sin", sinNative);
    defineNativeFunction(module, "cos", cosNative);
    defineNativeFunction(module, "tan", tanNative);

    defineNativeValue(module, "TAU", NUMBER_VAL(6.28318530717958647692));

    defineNativeValue(module, "PI", NUMBER_VAL(HELIUM_PI));
    defineNativeValue(module, "E", NUMBER_VAL(2.718281828459045));

    defineNativeModule(vm.specialStrings[SPECIAL_STD_MATH], module);
}
