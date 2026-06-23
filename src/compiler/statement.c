#include "compiler_common.h"

void block() {
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        declaration();
    }

    consume(TOKEN_RIGHT_BRACE, "Expect '}' after block.");
}

void expressionStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value");
    emitByte(OP_POP);
}

void ifStatement() {
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after condition.");

    int ifJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);
    statement();

    int elseJump = emitJump(OP_JUMP);

    patchJump(ifJump);

    emitByte(OP_POP);

    if (match(TOKEN_ELSE)) statement();

    patchJump(elseJump);
}

void whileStatement() {
    int loopStart = currentChunk()->count;
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after while condition.");

    int exitJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);

    LoopContext ctx;
    ctx.start = loopStart;
    ctx.localCount = current->localCount;
    ctx.scopeDepth = current->scopeDepth;
    ctx.breakCount = 0;

    loopStack[loopDepth++] = ctx;

    statement();
    emitLoop(loopStart);

    patchJump(exitJump);
    emitByte(OP_POP);

    LoopContext* loopCtx = &loopStack[--loopDepth];

    for (int i = 0; i < loopCtx->breakCount; i++) {
        patchJump(loopCtx->breaks[i]);
    }
}

void forStatement() {
    beginScope();
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");

    if (match(TOKEN_SEMICOLON)) {
        // no initializer.
    } else if (match(TOKEN_VAR)) {
        varDeclaration();
    } else {
        expressionStatement();
    }

    int loopStart = currentChunk()->count;

    int exitJump = -1;
    if (!match(TOKEN_SEMICOLON)) {
        expression();
        consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

        // exit loop if false.
        exitJump = emitJump(OP_JUMP_IF_FALSE);
        emitByte(OP_POP);  // pop condition.
    }

    if (!match(TOKEN_RIGHT_PAREN)) {
        int bodyJump = emitJump(OP_JUMP);
        int incrementStart = currentChunk()->count;
        expression();
        emitByte(OP_POP);
        consume(TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

        emitLoop(loopStart);
        loopStart = incrementStart;
        patchJump(bodyJump);
    }

    LoopContext ctx;
    ctx.start = loopStart;
    ctx.localCount = current->localCount;
    ctx.breakCount = 0;
    ctx.scopeDepth = current->scopeDepth;

    loopStack[loopDepth++] = ctx;

    statement();
    emitLoop(loopStart);

    if (exitJump != -1) {
        patchJump(exitJump);
        emitByte(OP_POP);
    }

    LoopContext* loopCtx = &loopStack[--loopDepth];

    for (int i = 0; i < loopCtx->breakCount; i++) {
        patchJump(loopCtx->breaks[i]);
    }
    endScope();
}

void breakStatement() {
    if (loopDepth == 0) {
        error("Cannot use 'break' outside of a loop.");
        return;
    }

    consume(TOKEN_SEMICOLON, "Expect ';' after 'break'.");

    LoopContext* ctx = &loopStack[loopDepth - 1];

    emitPopToCount(ctx->localCount);

    int jump = emitJump(OP_JUMP);
    ctx->breaks[ctx->breakCount++] = jump;
}

void continueStatement() {
    if (loopDepth == 0) {
        error("Cannot use 'continue' outside of a loop.");
        return;
    }
    LoopContext* ctx = &loopStack[loopDepth - 1];

    emitPopToCount(ctx->localCount);
    consume(TOKEN_SEMICOLON, "Expect ';' after 'continue'.");
    emitLoop(loopStack[loopDepth - 1].start);
}

void printStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value");
    emitByte(OP_PRINT);
}

void returnStatement() {
    if (current->type == TYPE_SCRIPT) {
        error("Can't return from top-level code.");
    }

    if (match(TOKEN_SEMICOLON)) {
        emitReturn();
    } else {
        if (current->type == TYPE_INITIALIZER) {
            error("Can't return a value from an initializer.");
        }
        expression();
        consume(TOKEN_SEMICOLON, "Expect ';' after return value.");
        emitByte(OP_RETURN);
    }
}

void importStatement() {
    if (match(TOKEN_IDENTIFIER)) {
        ObjString* name =
            copyString(parser.previous.start, parser.previous.length);

        uint8_t global = identifierConstant(&parser.previous);

        emitConstant(OBJ_VAL(name));
        emitByte(OP_IMPORT);

        defineVariable(global, true);
    } else if (match(TOKEN_STRING)) {
        ObjString* name =
            copyString(parser.previous.start + 1, parser.previous.length - 2);

        consume(TOKEN_AS, "Expect 'as' after path.");
        uint8_t global = parseVariable("Expect alias for import.", true);

        emitConstant(OBJ_VAL(name));
        emitByte(OP_IMPORT);

        defineVariable(global, true);
    } else {
        error("Invalid import.");
    }
}