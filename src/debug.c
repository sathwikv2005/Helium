#include "../include/debug.h"

#include <stdio.h>

#include "../include/line.h"
#include "../include/object.h"
#include "../include/value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
    printf("==+++++++++==\n");
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s [%4d] => '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static int closureInstruction(const char* name, Chunk* chunk, int offset) {
    offset++;
    uint8_t constant = chunk->code[offset++];
    printf("%-16s [%4d] => '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    ObjFunction* function = AS_FUNCTION(chunk->constants.values[constant]);
    for (int j = 0; j < function->upvalueCount; j++) {
        int isLocal = chunk->code[offset++];
        int index = chunk->code[offset++];
        printf("[%04d]   |\t %s %d\n", offset - 2,
               isLocal ? "local" : "upvalue", index);
    }

    return offset;
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int byteInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t slot = chunk->code[offset + 1];
    printf("%-16s [%4d]\n", name, slot);
    return offset + 2;
}

static int jumpInstruction(const char* name, int sign, Chunk* chunk,
                           int offset) {
    uint16_t jump = (uint16_t)(chunk->code[offset + 1] << 8);
    jump |= chunk->code[offset + 2];
    printf("%-16s [%4d] => %d\n", name, offset, offset + 3 + sign * jump);
    return offset + 3;
}

static int invokeInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    uint8_t argCount = chunk->code[offset + 2];
    printf("%-16s (%d args) %4d '", name, argCount, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 3;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("----%04d\t", offset);
    int line = getLine(chunk, offset);
    if (offset > 0 && line == getLine(chunk, offset - 1))
        printf("   |\t");
    else
        printf("%4d\t", line);
    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CREATE_MAP:
            return simpleInstruction("OP_CREATE_MAP", offset);
        case OP_CREATE_ARRAY:
            return constantInstruction("OP_CREATE_ARRAY", chunk, offset);
        case OP_FALSE:
            return simpleInstruction("OP_FALSE", offset);
        case OP_TRUE:
            return simpleInstruction("OP_TRUE", offset);
        case OP_NULL:
            return simpleInstruction("OP_NULL", offset);
        case OP_POP:
            return simpleInstruction("OP_POP", offset);
        case OP_GET_PROPERTY:
            return constantInstruction("OP_GET_PROTERTY", chunk, offset);
        case OP_SET_PROPERTY:
            return constantInstruction("OP_SET_PROPERTY", chunk, offset);
        case OP_GET_INDEX:
            return simpleInstruction("OP_GET_INDEX", offset);
        case OP_SET_INDEX:
            return simpleInstruction("OP_SET_INDEX", offset);
        case OP_GET_UPVALUE:
            return byteInstruction("OP_GET_UPVALUE", chunk, offset);
        case OP_SET_UPVALUE:
            return byteInstruction("OP_SET_UPVALUE", chunk, offset);
        case OP_GET_LOCAL:
            return byteInstruction("OP_GET_LOCAL", chunk, offset);
        case OP_SET_LOCAL:
            return byteInstruction("OP_SET_LOCAL", chunk, offset);
        case OP_EXPORT_DEFINE:
            return constantInstruction("OP_EXPORT_DEFINE", chunk, offset);
        case OP_EXPORT_DEFINE_CONST:
            return constantInstruction("OP_EXPORT_DEFINE_CONST", chunk, offset);
        case OP_EXPORT_SET:
            return constantInstruction("OP_EXPORT_SET", chunk, offset);
        case OP_EXPORT_GET:
            return constantInstruction("OP_EXPORT_GET", chunk, offset);
        case OP_GET_GLOBAL:
            return constantInstruction("OP_GET_GLOBAL", chunk, offset);
        case OP_DEFINE_GLOBAL:
            return constantInstruction("OP_DEFINE_GLOBAL", chunk, offset);
        case OP_DEFINE_GLOBAL_CONST:
            return constantInstruction("OP_DEFINE_GLOBAL_CONST", chunk, offset);
        case OP_SET_GLOBAL:
            return constantInstruction("OP_SET_GLOBAL", chunk, offset);
        case OP_PUSH:
            return simpleInstruction("OP_PUSH", offset);
        case OP_EQUAL:
            return simpleInstruction("OP_EQUAL", offset);
        case OP_GREATER:
            return simpleInstruction("OP_GREATER", offset);
        case OP_LESS:
            return simpleInstruction("OP_LESS", offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_MODULO:
            return simpleInstruction("OP_MODULO", offset);
        case OP_NOT:
            return simpleInstruction("OP_NOT", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_PRINT:
            return simpleInstruction("OP_PRINT", offset);
        case OP_DUP:
            return simpleInstruction("OP_DUP", offset);
        case OP_DUP2:
            return simpleInstruction("OP_DUP2", offset);
        case OP_JUMP:
            return jumpInstruction("OP_JUMP", 1, chunk, offset);
        case OP_JUMP_IF_FALSE:
            return jumpInstruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
        case OP_LOOP:
            return jumpInstruction("OP_LOOP", -1, chunk, offset);
        case OP_CALL:
            return byteInstruction("OP_CALL", chunk, offset);
        case OP_CLOSURE:
            return closureInstruction("OP_CLOSURE", chunk, offset);
        case OP_CLOSE_UPVALUE:
            return closureInstruction("OP_CLOSURE", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CLASS:
            return constantInstruction("OP_CLASS", chunk, offset);
        case OP_METHOD:
            return constantInstruction("OP_METHOD", chunk, offset);
        case OP_INVOKE:
            return invokeInstruction("OP_INVOKE", chunk, offset);
        case OP_GET_SUPER:
            return constantInstruction("OP_GET_SUPER", chunk, offset);
        case OP_SUPER_INVOKE:
            return invokeInstruction("OP_SUPER_INVOKE", chunk, offset);
        case OP_SWAP:
            return byteInstruction("OP_SWAP", chunk, offset);
        case OP_IMPORT:
            return byteInstruction("OP_IMPORT", chunk, offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
