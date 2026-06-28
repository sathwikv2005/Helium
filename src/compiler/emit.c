#include "compiler_common.h"

void emitPopToCount(int targetCount) {
    for (int i = current->localCount - 1; i >= targetCount; i--) {
        if (current->locals[i].isCaptured) {
            emitByte(OP_CLOSE_UPVALUE);
        } else
            emitByte(OP_POP);
    }
}

void emitSetBytes(uint8_t setOp, uint8_t getOp, uint8_t arg,
                  TokenType assignOp) {
    if (assignOp != TOKEN_EQUAL) {
        emitBytes(getOp, arg);
    }
    if (assignOp == TOKEN_PLUS_PLUS || assignOp == TOKEN_MINUS_MINUS) {
        emitByte(OP_DUP);
        emitConstant(NUMBER_VAL(1));
    } else {
        expression();
    }
    emitOpByte(assignOp);
    emitBytes(setOp, (uint8_t)arg);
    if (assignOp == TOKEN_PLUS_PLUS || assignOp == TOKEN_MINUS_MINUS)
        emitByte(OP_POP);
}

void emitOpByte(uint8_t token) {
    switch (token) {
        case TOKEN_PLUS_EQUAL:
            emitByte(OP_ADD);
            break;

        case TOKEN_MINUS_EQUAL:
            emitByte(OP_SUBTRACT);
            break;
        case TOKEN_STAR_EQUAL:
            emitByte(OP_MULTIPLY);
            break;
        case TOKEN_SLASH_EQUAL:
            emitByte(OP_DIVIDE);
            break;
        case TOKEN_PERCENT_EQUAL:
            emitByte(OP_MODULO);
            break;
        case TOKEN_EQUAL:
        default:
            break;
    }
}

void emitByte(uint8_t byte) {
    if (parser.hadError) return;
    writeChunk(currentChunk(), byte, parser.previous.line);
}
void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

int emitJump(uint8_t instruction) {
    emitByte(instruction);
    emitByte(0xff);
    emitByte(0xff);
    return currentChunk()->count - 2;
}

void emitLoop(int loopStart) {
    emitByte(OP_LOOP);

    int offset = currentChunk()->count - loopStart + 2;
    if (offset > UINT16_MAX) error("Loop body too large.");

    emitByte((offset >> 8) & 0xff);
    emitByte(offset & 0xff);
}

void emitConstant(Value value) { emitBytes(OP_CONSTANT, makeConstant(value)); }

/*
    Forward jumps are created and emitted using a placeholder offset.

    Once the final distance is known, patchJump() overwrites the placeholder
    with the final distance.
*/
void patchJump(int offset) {
    // +2 to adjust for the bytecodes for the jump offset itself.
    int jump = currentChunk()->count - (offset + 2);

    if (jump > UINT16_MAX) {
        error("Too much code to jump over.");
    }

    currentChunk()->code[offset] = (jump >> 8) & 0xff;
    currentChunk()->code[offset + 1] = jump & 0xff;
}

void emitReturn() {
    if (current->type == TYPE_INITIALIZER) {
        emitBytes(OP_GET_LOCAL, 0);
    } else
        emitByte(OP_NULL);
    emitByte(OP_RETURN);
}