#include "vm_common.h"

VM vm;

void initVM() {
    resetStack();
    vm.objects = NULL;
    vm.grayCount = 0;
    vm.grayCapacity = 0;
    vm.grayStack = NULL;
    vm.debugFlags = 0;
    vm.bytesAllocated = 0;
    vm.nextGC = 1024 * 1024;
    vm.currentGCMark = true;
    initTable(&vm.strings);
    initTable(&vm.builtins);

    initSpecialStrings();

    mapNatives();
}

void freeVM() {
    freeObjects();
    freeTable(&vm.builtins);
    freeTable(&vm.strings);
}

static InterpretResult run() {
    CallFrame* frame = &vm.frames[vm.frameCount - 1];
    register uint8_t* ip = frame->ip;
#define RUNTIME_ERROR(...)         \
    do {                           \
        frame->ip = ip;            \
        runtimeError(__VA_ARGS__); \
    } while (false)
#define READ_BYTE() (*ip++)
#define READ_CONSTANT() \
    (frame->closure->function->chunk.constants.values[READ_BYTE()])
#define READ_SHORT() (ip += 2, (uint16_t)((ip[-2] << 8) | ip[-1]))
#define READ_STRING() AS_STRING(READ_CONSTANT())
#define BINARY_OP(valueType, op)                          \
    do {                                                  \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            RUNTIME_ERROR("Operands must be numbers.");   \
        }                                                 \
        double b = AS_NUMBER(pop());                      \
        double a = AS_NUMBER(pop());                      \
        push(valueType(a op b));                          \
    } while (false)

    while (true) {
#ifdef HELIUM_DEBUG
        if (GET_DEBUG_TRACE()) {
            printf("Stack=>\t");
            printf("[ ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printValue(*slot);
                printf(", ");
            }
            printf("]");
            printf("\n");
            disassembleInstruction(
                &frame->closure->function->chunk,
                (int)(ip - frame->closure->function->chunk.code));
            // printf("==+++++++++==\n");
        }
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_FALSE:
                push(BOOL_VAL(false));
                break;
            case OP_TRUE:
                push(BOOL_VAL(true));
                break;
            case OP_NULL:
                push(NULL_VAL);
                break;
            case OP_POP:
                pop();
                break;
            case OP_GET_LOCAL: {
                uint8_t slot = READ_BYTE();
                push(frame->slots[slot]);
                break;
            }
            case OP_SET_LOCAL: {
                uint8_t slot = READ_BYTE();
                frame->slots[slot] = peek(0);
                break;
            }
            case OP_SET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;

                if (!tableGet(&frame->module->globals, name, &value)) {
                    RUNTIME_ERROR("Undefined variable '%s'.", name->chars);
                }

                if (!IS_VARIABLE(value)) {
                    RUNTIME_ERROR("Internal error: expected variable.",
                                  name->chars);
                }
                ObjVariable* var = AS_VARIABLE(value);

                if (var->isConst) {
                    RUNTIME_ERROR("Cannot assign to const variable '%s'.",
                                  name->chars);
                }

                var->value = peek(0);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;

                if (!tableGet(&frame->module->globals, name, &value)) {
                    if (!tableGet(&vm.builtins, name, &value)) {
                        RUNTIME_ERROR("Undefined variable '%s'.", name->chars);
                    }
                }

                if (IS_VARIABLE(value)) {
                    ObjVariable* var = AS_VARIABLE(value);
                    push(var->value);
                } else {
                    push(value);
                }

                break;
            }
            case OP_DEFINE_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value = peek(0);

                push(OBJ_VAL(name));

                ObjVariable* variable = newVariable(value, false);
                push(OBJ_VAL(variable));

                tableSet(&frame->module->globals, name, OBJ_VAL(variable));

                pop();  // variable
                pop();  // name
                pop();  // original value

                break;
            }

            case OP_DEFINE_GLOBAL_CONST: {
                ObjString* name = READ_STRING();
                Value value = peek(0);

                push(OBJ_VAL(name));

                ObjVariable* variable = newVariable(value, true);
                push(OBJ_VAL(variable));

                tableSet(&frame->module->globals, name, OBJ_VAL(variable));

                pop();  // variable
                pop();  // name
                pop();  // original value

                break;
            }
            case OP_GET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                push(*frame->closure->upvalues[slot]->location);
                break;
            }
            case OP_SET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                *frame->closure->upvalues[slot]->location = peek(0);
                break;
            }

            case OP_CREATE_MAP: {
                ObjHashMap* hashMap = newHashMap();
                push(OBJ_VAL(hashMap));
                break;
            }
            case OP_CREATE_ARRAY: {
                uint8_t capacity = READ_BYTE();
                ObjArray* array = newArray((int)capacity);
                push(OBJ_VAL(array));
                break;
            }

            case OP_GET_PROPERTY: {
                if (!IS_OBJ(peek(0))) {
                    RUNTIME_ERROR("Only instances and maps have fields.");
                }
                Obj* target = AS_OBJ(peek(0));
                ObjString* name = READ_STRING();
                Value value;
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        ObjInstance* instance = (ObjInstance*)target;
                        if (tableGet(&instance->fields, name, &value)) {
                            pop();
                            push(value);
                        } else if (!bindMethod(instance->klass, name)) {
                            pop();
                            push(NULL_VAL);  // return null as default
                        }
                        break;
                    }
                    case OBJ_HASHMAP: {
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        if (tableGet(&hashMap->map, name, &value)) {
                            pop();
                            push(value);
                        } else {
                            pop();
                            push(NULL_VAL);  // return null as default
                        }
                        break;
                    }
                    default: {
                        RUNTIME_ERROR("Only instances and maps have fields.");
                        break;
                    }
                }

                break;
            }
            case OP_SET_PROPERTY: {
                if (!IS_OBJ(peek(1))) {
                    RUNTIME_ERROR("Only instances and maps have fields.");
                }
                Obj* target = AS_OBJ(peek(1));
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        ObjInstance* instance = (ObjInstance*)target;
                        tableSet(&instance->fields, READ_STRING(), peek(0));
                        break;
                    }
                    case OBJ_HASHMAP: {
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        tableSet(&hashMap->map, READ_STRING(), peek(0));
                        break;
                    }
                    default: {
                        RUNTIME_ERROR("Only instances and maps have fields.");
                        break;
                    }
                }
                Value value = pop();
                pop();
                push(value);
                break;
            }
            case OP_INVOKE: {
                ObjString* method = READ_STRING();
                int argCount = READ_BYTE();

                Value receiver = peek(argCount);
                if (!IS_OBJ(receiver)) {
                    RUNTIME_ERROR("Only instances have methods.");
                }

                switch (OBJ_TYPE(receiver)) {
                    case OBJ_ARRAY:
                        if (!arrayMethodsFromName(AS_ARRAY(receiver), argCount,
                                                  method)) {
                            RUNTIME_ERROR("Undefined array method '%s'.",
                                          method->chars);
                        }
                        break;

                    case OBJ_STRING:
                        if (!stringMethodsFromName(AS_STRING(receiver),
                                                   argCount, method)) {
                            RUNTIME_ERROR("Undefined string method '%s'.",
                                          method->chars);
                        }
                        break;

                    default:
                        frame->ip = ip;

                        if (!invoke(method, argCount)) {
                            return INTERPRET_RUNTIME_ERROR;
                        }

                        frame = &vm.frames[vm.frameCount - 1];
                        ip = frame->ip;
                        break;
                }

                break;
            }
            case OP_GET_INDEX: {
                Value key = pop();

                if (!IS_OBJ(peek(0))) {
                    RUNTIME_ERROR(
                        "Only instances, maps, arrays and strings support "
                        "indexing.");
                }
                Value value;
                Obj* target = AS_OBJ(peek(0));
                bool get = false;
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjInstance* instance = (ObjInstance*)target;
                        get =
                            tableGet(&instance->fields, AS_STRING(key), &value);
                        break;
                    }
                    case OBJ_HASHMAP: {
                        if (IS_NUMBER(key)) {
                            key = OBJ_VAL(valueToString(key));
                        }
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        get = tableGet(&hashMap->map, AS_STRING(key), &value);
                        break;
                    }
                    case OBJ_ARRAY: {
                        if (!IS_NUMBER(key)) {
                            RUNTIME_ERROR("Index must be a number");
                        }
                        double index = AS_NUMBER(key);

                        if (index < 0 || index != (int)index) {
                            RUNTIME_ERROR(
                                "Array index must be a non-negative integer");
                        }

                        int i = (int)index;
                        ObjArray* array = (ObjArray*)target;

                        if (i >= array->array.count) {
                            RUNTIME_ERROR("Array index out of bounds");
                        }
                        value = array->array.values[i];
                        get = true;
                        break;
                    }
                    case OBJ_STRING: {
                        if (!IS_NUMBER(key)) {
                            RUNTIME_ERROR("Index must be a number");
                        }
                        double index = AS_NUMBER(key);

                        if (index < 0 || index != (int)index) {
                            RUNTIME_ERROR(
                                "String index must be a non-negative integer");
                        }

                        int i = (int)index;
                        ObjString* string = (ObjString*)target;

                        if (i >= string->length) {
                            RUNTIME_ERROR("String index out of bounds");
                        }
                        value = OBJ_VAL(copyString(&string->chars[i], 1));
                        get = true;
                        break;
                    }
                    default: {
                        RUNTIME_ERROR(
                            "Only instances, maps, arrays and strings support "
                            "indexing.");
                        break;
                    }
                }

                if (get) {
                    pop();
                    push(value);
                } else {
                    pop();
                    push(NULL_VAL);
                }

                break;
            }

            case OP_SET_INDEX: {
                Value value = peek(0);
                Value key = peek(1);

                if (!IS_OBJ(peek(2))) {
                    RUNTIME_ERROR(
                        "Only instances, maps and arrays support index "
                        "assignment.");
                }
                Obj* target = AS_OBJ(peek(2));
                switch (target->type) {
                    case OBJ_INSTANCE: {
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjInstance* instance = (ObjInstance*)target;
                        tableSet(&instance->fields, AS_STRING(key), value);
                        break;
                    }
                    case OBJ_HASHMAP: {
                        if (IS_NUMBER(key)) {
                            key = OBJ_VAL(valueToString(key));
                        }
                        if (!IS_STRING(key)) {
                            RUNTIME_ERROR("Field name must be a string.");
                        }
                        ObjHashMap* hashMap = (ObjHashMap*)target;
                        tableSet(&hashMap->map, AS_STRING(key), value);
                        break;
                    }
                    case OBJ_ARRAY: {
                        if (!IS_NUMBER(key)) {
                            RUNTIME_ERROR("Index must be a number");
                        }
                        double index = AS_NUMBER(key);

                        if (index < 0 || index != (int)index) {
                            RUNTIME_ERROR(
                                "Array index must be a non-negative integer");
                        }

                        int i = (int)index;
                        ObjArray* array = (ObjArray*)target;

                        if (i >= array->array.count) {
                            RUNTIME_ERROR("Array index out of bounds");
                        }
                        array->array.values[i] = value;
                        break;
                    }
                    default: {
                        RUNTIME_ERROR(
                            "Only instances, maps and arrays support "
                            "index assignment.");
                        break;
                    }
                }

                pop();  // value
                pop();  // key
                pop();  // instance

                push(value);

                break;
            }
            case OP_PUSH: {
                Value value = peek(0);
                if (!IS_ARRAY(peek(1))) {
                    RUNTIME_ERROR("Only arrays support push.");
                }
                ObjArray* array = AS_ARRAY(peek(1));

                writeValueArray(&array->array, value);
                pop();  // value
                break;
            }
            case OP_INHERIT: {
                Value superclass = peek(1);
                if (!IS_CLASS(superclass)) {
                    RUNTIME_ERROR("Superclass must be a class.");
                }
                ObjClass* subclass = AS_CLASS(peek(0));
                tableAddAll(&AS_CLASS(superclass)->methods, &subclass->methods);
                subclass->initializer = AS_CLASS(superclass)->initializer;
                pop();  // subclass
                break;
            }
            case OP_GET_SUPER: {
                ObjString* name = READ_STRING();
                ObjClass* superclass = AS_CLASS(pop());

                if (!bindMethod(superclass, name)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUPER_INVOKE: {
                ObjString* method = READ_STRING();
                int argCount = READ_BYTE();
                ObjClass* superclass = AS_CLASS(pop());
                if (!invokeFromClass(superclass, method, argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame->ip = ip;
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_GREATER:
                BINARY_OP(BOOL_VAL, >);
                break;
            case OP_LESS:
                BINARY_OP(BOOL_VAL, <);
                break;
            case OP_ADD: {
                if (IS_STRING(peek(0)) || IS_STRING(peek(1))) {
                    concatenate();
                } else if (IS_NUMBER(peek(0)) && IS_NUMBER(peek(1))) {
                    double b = AS_NUMBER(pop());
                    double a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a + b));
                } else {
                    RUNTIME_ERROR("Operands must be numbers or strings.");
                }
                break;
            }
            case OP_SUBTRACT:
                BINARY_OP(NUMBER_VAL, -);
                break;
            case OP_MULTIPLY:
                BINARY_OP(NUMBER_VAL, *);
                break;
            case OP_DIVIDE:
                if (IS_NUMBER(peek(0)) && AS_NUMBER(peek(0)) == 0) {
                    RUNTIME_ERROR("Division by zero.");
                }
                BINARY_OP(NUMBER_VAL, /);
                break;
            case OP_MODULO: {
                if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) {
                    RUNTIME_ERROR("Operands must be numbers.");
                }
                if (AS_NUMBER(peek(0)) == 0) {
                    RUNTIME_ERROR("Modulo by zero.");
                }

                double b = AS_NUMBER(pop());
                double a = AS_NUMBER(pop());

                push(NUMBER_VAL(fmod(a, b)));
                break;
            }
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE: {
                if (!IS_NUMBER(peek(0))) {
                    RUNTIME_ERROR("Operand must be a number.");
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            }
            case OP_PRINT: {
                printValue(pop());
                printf("\n");
                break;
            }
            case OP_JUMP: {
                uint16_t offset = READ_SHORT();
                ip += offset;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t offset = READ_SHORT();
                if (isFalsey(peek(0))) ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = READ_SHORT();
                ip -= offset;
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();
                frame->ip = ip;
                if (!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            case OP_CLOSURE: {
                ObjFunction* function = AS_FUNCTION(READ_CONSTANT());
                ObjClosure* closure = newClosure(function);
                push(OBJ_VAL(closure));
                closure->module = frame->module;
                for (int i = 0; i < closure->upvalueCount; i++) {
                    uint8_t isLocal = READ_BYTE();
                    uint8_t index = READ_BYTE();
                    if (isLocal) {
                        closure->upvalues[i] =
                            captureUpvalue(frame->slots + index);
                    } else {
                        closure->upvalues[i] = frame->closure->upvalues[index];
                    }
                }

                break;
            }
            case OP_IMPORT: {
                Value value = pop();
                ObjString* name = AS_STRING(value);

                ObjModule* module = newModule(name);
                push(OBJ_VAL(module));
                break;
            }
            case OP_CLOSE_UPVALUE:
                closeUpvalues(vm.stackTop - 1);
                pop();
                break;
            case OP_RETURN: {
                Value result = pop();
                closeUpvalues(frame->slots);
                vm.frameCount--;
                if (vm.frameCount == 0) {
                    pop();
                    frame->ip = ip;
                    return INTERPRET_OK;
                }

                vm.stackTop = frame->slots;
                push(result);
                frame = &vm.frames[vm.frameCount - 1];
                ip = frame->ip;
                break;
            }
            case OP_CLASS: {
                push(OBJ_VAL(newClass(READ_STRING())));
                break;
            }
            case OP_METHOD:
                defineMethod(READ_STRING());
                break;
            case OP_DUP:
                push(peek(0));
                break;
            case OP_DUP2:
                push(peek(1));
                push(peek(1));
                break;
            case OP_SWAP:
                swap(READ_BYTE());
                break;
            case OP_TYPE:
                ObjString* type = valueType(peek(0));
                Value result = OBJ_VAL(type);
                pop();
                push(result);
                break;
            default:
                break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_SHORT
#undef READ_STRING
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    switch (setjmp(vm.vmJump)) {
        case JUMP_RUNTIME_ERROR:
            return INTERPRET_RUNTIME_ERROR;

        case JUMP_EXIT:
            return INTERPRET_EXIT;
    }

    ObjFunction* function = compile(source);

    if (function == NULL) {
        return INTERPRET_COMPILE_ERROR;
    }
    push(OBJ_VAL(function));
    ObjModule* mainModule = newModule(vm.specialStrings[SPECIAL_SCRIPT]);
    push(OBJ_VAL(mainModule));
    ObjClosure* closure = newClosure(function);
    closure->module = mainModule;
    pop();
    pop();
    push(OBJ_VAL(closure));
    callValue(OBJ_VAL(closure), 0);

    return run();
}
