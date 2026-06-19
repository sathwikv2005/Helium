
#include <string.h>

#include "compiler_common.h"

LoopContext loopStack[64];
int loopDepth = 0;

Compiler* current = NULL;

ClassCompiler* currentClass = NULL;

Chunk* currentChunk() { return &current->function->chunk; }

void resetUpdateState() {
    updateState.target = UPDATE_TARGET_NONE;
    updateState.currentUpdate = UPDATE_NONE;
}

void beginScope() { current->scopeDepth++; }

void endScope() {
    current->scopeDepth--;

    while (current->localCount > 0 &&
           current->locals[current->localCount - 1].depth >
               current->scopeDepth) {
        if (current->locals[current->localCount - 1].isCaptured) {
            emitByte(OP_CLOSE_UPVALUE);
        } else
            emitByte(OP_POP);
        current->localCount--;
    }
}

static void emitUpdateBytes() {
    if (updateState.currentUpdate == UPDATE_NONE) return;
    if (updateState.isConst) {
        error("Cannot assign to const variable.");
    }
    emitConstant(NUMBER_VAL(1));

    if (updateState.currentUpdate == UPDATE_PREFIX_INC ||
        updateState.currentUpdate == UPDATE_POSTFIX_INC)
        emitByte(OP_ADD);
    else
        emitByte(OP_SUBTRACT);
}

static void emitPrefixUpdate() {
    emitUpdateBytes();
    emitBytes(updateState.setOp, updateState.arg);
    updateState.currentUpdate = UPDATE_NONE;
}

static void emitPrefixPropertyUpdate() {
    emitByte(OP_DUP);
    emitBytes(OP_GET_PROPERTY, updateState.arg);
    emitUpdateBytes();
    emitBytes(OP_SET_PROPERTY, updateState.arg);
    updateState.currentUpdate = UPDATE_NONE;
}
static void emitPrefixIndexUpdate() {
    emitByte(OP_DUP2);
    emitByte(OP_GET_INDEX);
    emitUpdateBytes();
    emitByte(OP_SET_INDEX);
    updateState.currentUpdate = UPDATE_NONE;
}

static void emitPostFixUpdate() {
    emitByte(OP_DUP);
    emitUpdateBytes();
    emitBytes(updateState.setOp, updateState.arg);
    emitByte(OP_POP);
    updateState.currentUpdate = UPDATE_NONE;
}

static void emitPostFixPropertyUpdate() {
    emitBytes(updateState.classGetOp, updateState.className);
    emitBytes(OP_SWAP, 0);
    emitByte(OP_DUP);
    emitBytes(OP_SWAP, 1);
    emitUpdateBytes();
    emitBytes(OP_SET_PROPERTY, updateState.arg);
    emitByte(OP_POP);
    updateState.currentUpdate = UPDATE_NONE;
}
static void emitPostFixIndexUpdate() {
    emitByte(OP_DUP2);
    emitByte(OP_GET_INDEX);
    emitByte(OP_DUP);
    emitBytes(OP_SWAP, 1);
    emitBytes(OP_SWAP, 2);
    emitUpdateBytes();
    emitByte(OP_SET_INDEX);
    emitByte(OP_POP);
    updateState.currentUpdate = UPDATE_NONE;
}

void instanceIndex(bool canAssign) {
    expression();
    consume(TOKEN_RIGHT_SQUARE, "Expect ']' after index.");

    updateState.target = UPDATE_TARGET_INDEX;
    if (updateState.currentUpdate != UPDATE_NONE) {
        return;
    }

    TokenType assignOp = canAssign ? matchAssignmentOperator() : TOKEN_ERROR;

    if (assignOp != TOKEN_ERROR) {
        if (assignOp != TOKEN_EQUAL) {
            emitByte(OP_DUP2);
            emitByte(OP_GET_INDEX);
        }

        expression();

        emitOpByte(assignOp);
        emitByte(OP_SET_INDEX);

    } else if (parser.current.type != TOKEN_PLUS_PLUS &&
               parser.current.type != TOKEN_MINUS_MINUS) {
        emitByte(OP_GET_INDEX);
    }
}

void preFixIncrement(bool canAssign) {
    if (parser.current.type != TOKEN_IDENTIFIER) {
        error("Invalid increment target.");
    }
    UpdateState old = updateState;
    updateState.currentUpdate = UPDATE_PREFIX_INC;
    parsePrecedence(PREC_UNARY);

    switch (updateState.target) {
        case UPDATE_TARGET_VARIABLE:
            emitPrefixUpdate();
            break;

        case UPDATE_TARGET_PROPERTY:
            emitPrefixPropertyUpdate();
            break;

        case UPDATE_TARGET_INDEX:
            emitPrefixIndexUpdate();
            break;

        default:
            error("Invalid increment target.");
    }
    updateState = old;
}

void preFixDecrement(bool canAssign) {
    if (parser.current.type != TOKEN_IDENTIFIER)
        error("Invalid increment target.");
    UpdateState old = updateState;
    updateState.currentUpdate = UPDATE_PREFIX_DEC;
    parsePrecedence(PREC_UNARY);
    switch (updateState.target) {
        case UPDATE_TARGET_VARIABLE:
            emitPrefixUpdate();
            break;

        case UPDATE_TARGET_PROPERTY:
            emitPrefixPropertyUpdate();
            break;

        case UPDATE_TARGET_INDEX:
            emitPrefixIndexUpdate();
            break;

        default:
            error("Invalid increment target.");
    }
    updateState = old;
}

void postFixIncrement(bool canAssign) {
    UpdateState old = updateState;
    updateState.currentUpdate = UPDATE_POSTFIX_INC;

    switch (updateState.target) {
        case UPDATE_TARGET_VARIABLE:
            emitPostFixUpdate();
            break;

        case UPDATE_TARGET_PROPERTY:
            emitPostFixPropertyUpdate();
            break;

        case UPDATE_TARGET_INDEX:
            emitPostFixIndexUpdate();
            break;

        default:
            error("Invalid increment target.");
    }
    updateState = old;
}
void postFixDecrement(bool canAssign) {
    UpdateState old = updateState;
    updateState.currentUpdate = UPDATE_POSTFIX_DEC;

    switch (updateState.target) {
        case UPDATE_TARGET_VARIABLE:
            emitPostFixUpdate();
            break;

        case UPDATE_TARGET_PROPERTY:
            emitPostFixPropertyUpdate();
            break;

        case UPDATE_TARGET_INDEX:
            emitPostFixIndexUpdate();
            break;

        default:
            error("Invalid increment target.");
    }
    updateState = old;
}

void block() {
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        declaration();
    }

    consume(TOKEN_RIGHT_BRACE, "Expect '}' after block.");
}

static void expressionStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value");
    emitByte(OP_POP);
}

static void ifStatement() {
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

static void whileStatement() {
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

static void forStatement() {
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

static void breakStatement() {
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

static void continueStatement() {
    if (loopDepth == 0) {
        error("Cannot use 'continue' outside of a loop.");
        return;
    }
    LoopContext* ctx = &loopStack[loopDepth - 1];

    emitPopToCount(ctx->localCount);
    consume(TOKEN_SEMICOLON, "Expect ';' after 'continue'.");
    emitLoop(loopStack[loopDepth - 1].start);
}

static void printStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value");
    emitByte(OP_PRINT);
}

static void returnStatement() {
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

void statement() {
    if (match(TOKEN_PRINT))
        printStatement();
    else if (match(TOKEN_IF)) {
        ifStatement();
    } else if (match(TOKEN_FOR)) {
        forStatement();
    } else if (match(TOKEN_WHILE)) {
        whileStatement();
    } else if (match(TOKEN_RETURN)) {
        returnStatement();
    } else if (match(TOKEN_BREAK)) {
        breakStatement();
    } else if (match(TOKEN_CONTINUE)) {
        continueStatement();
    } else if (match(TOKEN_LEFT_BRACE)) {
        beginScope();
        block();
        endScope();
    } else
        expressionStatement();
}

void declaration() {
    if (match(TOKEN_CLASS)) {
        classDeclaration();
    } else if (match(TOKEN_FUNCTION)) {
        functionDeclaration();
    } else if (match(TOKEN_VAR)) {
        varDeclaration();
    } else if (match(TOKEN_CONST)) {
        constDeclaration();
    } else {
        statement();
    }
    // recover from panic mode.
    if (parser.panicMode) synchronize();
}

void initCompiler(Compiler* compiler, FunctionType type) {
    compiler->enclosing = current;
    compiler->function = NULL;
    compiler->type = type;
    compiler->localCount = 0;
    compiler->scopeDepth = 0;
    compiler->function = newFunction();
    current = compiler;

    if (type != TYPE_SCRIPT) {
        current->function->name =
            copyString(parser.previous.start, parser.previous.length);
    }

    // reserve the first slot for VM internal use.
    Local* local = &current->locals[current->localCount++];
    local->depth = 0;
    local->isCaptured = false;
    if (type != TYPE_FUNCTION) {
        local->name.start = "this";
        local->name.length = 4;
    } else {
        local->isConst = false;
        local->name.start = "";
        local->name.length = 0;
    }

    resetUpdateState();
}

ObjFunction* endCompiler() {
    emitReturn();

    ObjFunction* function = current->function;
    current = current->enclosing;

#ifdef HELIUM_DEBUG
    if (GET_DEBUG_CODE() && !parser.hadError)
        disassembleChunk(&function->chunk, function->name != NULL
                                               ? function->name->chars
                                               : "<script>");
#endif

    return function;
}

ObjFunction* compile(const char* source) {
    initScanner(source);

    Compiler compiler;
    initCompiler(&compiler, TYPE_SCRIPT);

    parser.hadError = false;
    parser.panicMode = false;

    advance();

    while (!match(TOKEN_EOF)) {
        declaration();
    }

    ObjFunction* function = endCompiler();
    return parser.hadError ? NULL : function;
}

void markCompilerRoots() {
    Compiler* compiler = current;
    while (compiler != NULL) {
        markObject((Obj*)compiler->function);
        compiler = compiler->enclosing;
    }
}