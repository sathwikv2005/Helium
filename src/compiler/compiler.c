
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