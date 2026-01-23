#include "../include/chunk.h"
#include "../include/common.h"
#include "../include/debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, addConstant(&chunk, 1.9), 1);
    writeChunk(&chunk, OP_CONSTANT, 3);
    writeChunk(&chunk, addConstant(&chunk, 1), 3);
    writeChunk(&chunk, OP_RETURN, 4);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}