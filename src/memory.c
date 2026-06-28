#include "../include/memory.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/compiler.h"
#include "../include/debug.h"
#include "../include/vm.h"

#define GC_HEAP_GROW_FACTOR 2

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    vm.bytesAllocated += newSize - oldSize;

#ifdef HELIUM_DEBUG
    if (newSize > oldSize) {
        if (GET_DEBUG_STRESS_GC()) collectGarbage();
    }
#endif

    if (newSize > oldSize && vm.bytesAllocated > vm.nextGC) collectGarbage();

    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    void* newPointer = realloc(pointer, newSize);
    if (newPointer == NULL) exit(1);
    return newPointer;
}

/*
    Marks an object and pushes it onto the VM's gray stack so that its
   references can later be traversed and marked.
*/
void markObject(Obj* object) {
    if (object == NULL || object->isMarked == vm.currentGCMark) return;
#ifdef HELIUM_DEBUG
    if (GET_DEBUG_LOG_GC()) {
        printf("%p mark ", (void*)object);
        printValue(OBJ_VAL(object));
        printf("\n");
    }
#endif
    object->isMarked = vm.currentGCMark;

    if (vm.grayCapacity < vm.grayCount + 1) {
        vm.grayCapacity = GROW_CAPACITY(vm.grayCapacity);
        vm.grayStack = realloc(vm.grayStack, sizeof(Obj*) * vm.grayCapacity);
        if (vm.grayStack == NULL) exit(1);
    }

    vm.grayStack[vm.grayCount++] = object;
}

void markValue(Value value) {
    if (!IS_OBJ(value)) return;
    markObject(AS_OBJ(value));
}

static void markArray(ValueArray* array) {
    for (int i = 0; i < array->count; i++) {
        markValue(array->values[i]);
    }
}
/*
    Marks all objects referenced by this object.
*/
static void blackenObject(Obj* object) {
#ifdef HELIUM_DEBUG
    if (GET_DEBUG_LOG_GC()) {
        printf("%p blacken ", (void*)object);
        printValue(OBJ_VAL(object));
        printf("\n");
    }
#endif
    switch (object->type) {
        case OBJ_UPVALUE:
            markValue(((ObjUpvalue*)object)->closed);
            break;
        case OBJ_CLASS: {
            ObjClass* klass = (ObjClass*)object;
            markObject((Obj*)klass->name);
            markObject((Obj*)klass->initializer);
            markTable(&klass->methods);
            break;
        }
        case OBJ_BOUND_METHOD: {
            ObjBoundMethod* bound = (ObjBoundMethod*)object;
            markValue(bound->receiver);
            markObject((Obj*)bound->method);
            break;
        }
        case OBJ_INSTANCE: {
            ObjInstance* instance = (ObjInstance*)object;
            markObject((Obj*)instance->klass);
            markTable(&instance->fields);
            break;
        }
        case OBJ_FUNCTION: {
            ObjFunction* function = (ObjFunction*)object;
            markObject((Obj*)function->name);
            markArray(&function->chunk.constants);
            break;
        }
        case OBJ_CLOSURE: {
            ObjClosure* closure = (ObjClosure*)object;
            markObject((Obj*)closure->function);
            markObject((Obj*)closure->module);
            for (int i = 0; i < closure->upvalueCount; i++) {
                markObject((Obj*)closure->upvalues[i]);
            }
            break;
        }
        case OBJ_MODULE: {
            ObjModule* module = (ObjModule*)object;
            markObject((Obj*)module->path);
            markTable(&module->globals);
            break;
        }
        case OBJ_VARIABLE: {
            ObjVariable* variable = (ObjVariable*)object;
            markValue(variable->value);
            break;
        }
        case OBJ_HASHMAP: {
            ObjHashMap* hashMap = (ObjHashMap*)object;
            markTable(&hashMap->map);
            break;
        }
        case OBJ_ARRAY: {
            ObjArray* array = (ObjArray*)object;
            markArray(&array->array);
            break;
        }
        case OBJ_ARRAY_METHOD: {
            ObjArrayMethod* arrayMethod = (ObjArrayMethod*)object;
            markObject((Obj*)arrayMethod->receiver);
            break;
        }
        case OBJ_NATIVE:
        case OBJ_STRING:
            break;
    }
}

static void freeObject(Obj* object) {
#ifdef HELIUM_DEBUG
    if (GET_DEBUG_LOG_GC())
        printf("%p free type %d\n", (void*)object, object->type);
#endif
    switch (object->type) {
        case OBJ_CLASS: {
            ObjClass* klass = (ObjClass*)object;
            freeTable(&klass->methods);
            FREE(ObjClass, object);
            break;
        }
        case OBJ_BOUND_METHOD: {
            FREE(ObjBoundMethod, object);
            break;
        }
        case OBJ_INSTANCE: {
            ObjInstance* instance = (ObjInstance*)object;
            freeTable(&instance->fields);
            FREE(ObjInstance, object);
            break;
        }
        case OBJ_MODULE: {
            ObjModule* module = (ObjModule*)object;
            freeTable(&module->globals);
            FREE(ObjModule, object);
            break;
        }
        case OBJ_CLOSURE: {
            ObjClosure* closure = (ObjClosure*)object;
            FREE_ARRAY(ObjUpvalue*, closure->upvalues, closure->upvalueCount);
            FREE(ObjClosure, object);
            break;
        }
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, object);
            break;
        }
        case OBJ_UPVALUE: {
            FREE(ObjUpvalue, object);
            break;
        }
        case OBJ_FUNCTION: {
            ObjFunction* function = (ObjFunction*)object;
            freeChunk(&function->chunk);
            FREE(ObjFunction, object);
            break;
        }
        case OBJ_HASHMAP: {
            ObjHashMap* hashMap = (ObjHashMap*)object;
            freeTable(&hashMap->map);
            FREE(ObjHashMap, object);
            break;
        }
        case OBJ_ARRAY: {
            ObjArray* array = (ObjArray*)object;
            freeValueArray(&array->array);
            FREE(ObjArray, object);
            break;
        }
        case OBJ_ARRAY_METHOD: {
            FREE(ObjArrayMethod, object);
            break;
        }
        case OBJ_NATIVE:
            FREE(ObjNative, object);
            break;
        case OBJ_VARIABLE:
            FREE(ObjVariable, object);
            break;
    }
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }

    free(vm.grayStack);
}

/*
    Mark all GC roots.

    Any object reachable from these roots is considered live.
*/
static void markRoots() {
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
        markValue(*slot);
    }

    for (int i = 0; i < vm.frameCount; i++) {
        markObject((Obj*)vm.frames[i].closure);
    }

    for (ObjUpvalue* upvalue = vm.openUpvalues; upvalue != NULL;
         upvalue = upvalue->next) {
        markObject((Obj*)upvalue);
    }

    markCompilerRoots();

    for (int i = 0; i < SPECIAL_COUNT; i++) {
        if (vm.specialStrings[i] != NULL) {
            markObject((Obj*)vm.specialStrings[i]);
        }
    }
}

/*
    Traverses the gray stack until all reachable objects are visited
*/
static void traceReferences() {
    while (vm.grayCount > 0) {
        Obj* object = vm.grayStack[--vm.grayCount];
        blackenObject(object);
    }
}

/*
    Frees every unmarked(unreachable) object from memory.
*/
static void sweep() {
    Obj* previous = NULL;
    Obj* object = vm.objects;
    while (object != NULL) {
        if (object->isMarked == vm.currentGCMark) {
            previous = object;
            object = object->next;
            continue;
        }
        Obj* unreached = object;
        object = object->next;
        if (previous != NULL) {
            previous->next = object;
        } else {
            vm.objects = object;
        }

        freeObject(unreached);
    }
}

/*
    Helium's mark and sweep garbage collector.

    collection happens in four phases:
      1. mark all roots.
      2. traverse and mark every reachable object.
      3. remove dead strings from the intern table.
      4. sweep and free all unmarked(unreachable) objects.

    Helium uses a toggle mark bit (`currentGCMark`) instead of clearing every
    object's mark before every collection cycle. After a sweep, the global mark
    value is flipped, effectively making all remaining objects as unmarked for
    the next GC cycle.
 */
void collectGarbage() {
#ifdef HELIUM_DEBUG
    size_t before = 0;
    if (GET_DEBUG_LOG_GC()) {
        printf("------ gc begin\n");
        before = vm.bytesAllocated;
    }
#endif

    markRoots();
    traceReferences();
    tableRemoveWhite(&vm.strings);
    sweep();

    // flip the mark bit, so all surviving objects appear as unmarked for next
    // cycle.
    vm.currentGCMark = !vm.currentGCMark;

    vm.nextGC = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;

#ifdef HELIUM_DEBUG
    if (GET_DEBUG_LOG_GC()) {
        printf("------ gc end\n");
        printf("   collected %zu bytes (from %zu to %zu) next at %zu\n",
               before - vm.bytesAllocated, before, vm.bytesAllocated,
               vm.nextGC);
    }
#endif
}