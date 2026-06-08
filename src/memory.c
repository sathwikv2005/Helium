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

    if (vm.bytesAllocated > vm.nextGC) collectGarbage();

    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    void* newPointer = realloc(pointer, newSize);
    if (newPointer == NULL) exit(1);
    return newPointer;
}

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
            for (int i = 0; i < closure->upvalueCount; i++) {
                markObject((Obj*)closure->upvalues[i]);
            }
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
            FREE(ObjClass, object);
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
        case OBJ_NATIVE:
            FREE(ObjNative, object);
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

    markTable(&vm.globals);
    markCompilerRoots();
}

static void traceReferences() {
    while (vm.grayCount > 0) {
        Obj* object = vm.grayStack[--vm.grayCount];
        blackenObject(object);
    }
}

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