#ifndef helium_vm_h
#define helium_vm_h

#include <setjmp.h>

#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

// debug macros
#define DEBUG_TRACE (1u << 0)
#define DEBUG_CODE (1u << 1)
#define DEBUG_STRESS_GC (1u << 2)
#define DEBUG_LOG_GC (1u << 3)

// setters
#define SET_DEBUG_TRACE() (vm.debugFlags |= DEBUG_TRACE)
#define SET_DEBUG_CODE() (vm.debugFlags |= DEBUG_CODE)
#define SET_DEBUG_STRESS_GC() (vm.debugFlags |= DEBUG_STRESS_GC)
#define SET_DEBUG_LOG_GC() (vm.debugFlags |= DEBUG_LOG_GC)

// enable all
#define SET_DEBUG()            \
    do {                       \
        SET_DEBUG_CODE();      \
        SET_DEBUG_TRACE();     \
        SET_DEBUG_STRESS_GC(); \
        SET_DEBUG_LOG_GC();    \
    } while (0)

// getters
#define GET_DEBUG_TRACE() (((vm.debugFlags) & DEBUG_TRACE) != 0)
#define GET_DEBUG_CODE() (((vm.debugFlags) & DEBUG_CODE) != 0)
#define GET_DEBUG_STRESS_GC() (((vm.debugFlags) & DEBUG_STRESS_GC) != 0)
#define GET_DEBUG_LOG_GC() (((vm.debugFlags) & DEBUG_LOG_GC) != 0)

typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

typedef struct {
    CallFrame frames[FRAMES_MAX];
    int frameCount;

    Value stack[STACK_MAX];
    Table strings;
    Table globals;

    ObjString* initString;
    ObjString* pushString;
    ObjString* lengthString;
    ObjString* sortString;
    ObjString* popString;

    ObjUpvalue* openUpvalues;

    size_t bytesAllocated;
    size_t nextGC;

    Obj* objects;
    int grayCount;
    int grayCapacity;
    Obj** grayStack;
    Value* stackTop;

    bool currentGCMark;

    jmp_buf errorJmp;

    // debug flags
    uint8_t debugFlags;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
void swap(uint8_t offset);
Value pop();

bool isFalsey(Value value);

void runtimeError(const char* format, ...);
#endif