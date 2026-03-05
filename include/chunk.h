#ifndef helium_chunk_h
#define helium_chunk_h

#include "common.h"
#include "line.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_NULL,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

typedef struct {
    int line;
    int count;
} Line;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;         /**< Bytecode array */
    LineArray lines;       // compressed line info
    ValueArray constants;  // constant values storage

} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
int getLine(const Chunk* chunk, int offset);

#endif