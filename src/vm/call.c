#include "vm_common.h"

static bool call(ObjClosure* closure, int argCount) {
    if (argCount != closure->function->arity) {
        runtimeError("Expected %d arguments but got %d.",
                     closure->function->arity, argCount);
        return false;
    }
    if (vm.frameCount == FRAMES_MAX) {
        runtimeError("Stack overflow.");
        return false;
    }
    CallFrame* frame = &vm.frames[vm.frameCount++];
    frame->closure = closure;
    frame->ip = closure->function->chunk.code;
    frame->slots = vm.stackTop - argCount - 1;
    return true;
}

bool callValue(Value callee, int argCount) {
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_CLOSURE:
                return call(AS_CLOSURE(callee), argCount);
            case OBJ_NATIVE: {
                NativeFn native = AS_NATIVE(callee);
                Value result = native(argCount, vm.stackTop - argCount);
                vm.stackTop -= argCount + 1;
                push(result);
                return true;
            }
            case OBJ_BOUND_METHOD: {
                ObjBoundMethod* bound = AS_BOUND_METHOD(callee);
                vm.stackTop[-argCount - 1] = bound->receiver;
                return call(bound->method, argCount);
            }
            case OBJ_CLASS: {
                ObjClass* klass = AS_CLASS(callee);
                vm.stackTop[-argCount - 1] = OBJ_VAL(newInstance(klass));
                if (klass->initializer != NULL) {
                    return call(klass->initializer, argCount);
                } else if (argCount != 0) {
                    runtimeError(
                        "Initializer %s() expects 0 arguments but got %d.",
                        klass->name->chars, argCount);
                    return false;
                }
                return true;
            }
            case OBJ_ARRAY_METHOD: {
                ObjArrayMethod* method = AS_ARRAY_METHOD(callee);
                return arrayMethods(method->receiver, argCount, method->type);
            }
            default:
                break;  // Non-callable object type.
        }
    } else if (IS_NULL(callee)) {
        runtimeError("Can not call a null value.");
        return false;
    }
    runtimeError("Can only call functions and classes.");
    return false;
}

bool invokeFromClass(ObjClass* klass, ObjString* name, int argCount) {
    Value method;
    if (name == vm.initString) {
        if (klass->initializer == NULL) {
            if (argCount != 0) {
                runtimeError(
                    "Superclass has no initializer accepting %d arguments.",
                    argCount);
                return false;
            }
            return true;  // do nothing
        }
        return call(klass->initializer, argCount);
    } else if (!tableGet(&klass->methods, name, &method)) {
        runtimeError("Undefined property '%s'.", name->chars);
        return false;
    }
    return call(AS_CLOSURE(method), argCount);
}

bool invoke(ObjString* name, int argCount) {
    Value receiver = peek(argCount);

    if (!IS_INSTANCE(receiver)) {
        runtimeError("Only instances have methods.");
        return false;
    }

    ObjInstance* instance = AS_INSTANCE(receiver);

    Value value;
    if (tableGet(&instance->fields, name, &value)) {
        vm.stackTop[-argCount - 1] = value;
        return callValue(value, argCount);
    }

    return invokeFromClass(instance->klass, name, argCount);
}

bool bindMethod(ObjClass* klass, ObjString* name) {
    Value method;
    if (!tableGet(&klass->methods, name, &method)) {
        return false;
    }
    ObjBoundMethod* bound = newBoundMethod(peek(0), AS_CLOSURE(method));
    pop();
    push(OBJ_VAL(bound));
    return true;
}
