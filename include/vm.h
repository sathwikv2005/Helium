#ifndef helium_vm_h
#define helium_vm_h

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_MAX 256

// debug macros
#define DEBUG_TRACE (1u << 0)
#define DEBUG_CODE (1u << 1)

#define SET_DEBUG_TRACE() (vm.debugFlags |= DEBUG_TRACE)
#define SET_DEBUG_CODE() (vm.debugFlags |= DEBUG_CODE)

#define SET_DEBUG()        \
    do {                   \
        SET_DEBUG_CODE();  \
        SET_DEBUG_TRACE(); \
    } while (0)

#define GET_DEBUG_TRACE() (((vm.debugFlags) & DEBUG_TRACE) != 0)
#define GET_DEBUG_CODE() (((vm.debugFlags) & DEBUG_CODE) != 0)

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Table strings;
    Table globals;

    Obj* objects;
    Value* stackTop;

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
Value pop();

#endif