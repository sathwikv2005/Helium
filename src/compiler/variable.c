#include "compiler_common.h"

void declareVariable(bool isConst) {
    if (current->scopeDepth == 0) return;

    Token* name = &parser.previous;

    for (int i = current->localCount - 1; i >= 0; i--) {
        Local* local = &current->locals[i];
        if (local->depth != -1 && local->depth < current->scopeDepth) {
            break;
        }

        if (identifiersEqual(name, &local->name)) {
            error("Already a variable with this name in this scope.");
        }
    }

    addLocal(*name, isConst);
}

uint8_t parseVariable(const char* errorMessage, bool isConst) {
    consume(TOKEN_IDENTIFIER, errorMessage);

    declareVariable(isConst);
    if (current->scopeDepth > 0) return 0;

    return identifierConstant(&parser.previous);
}

void markInitialized() {
    if (current->scopeDepth == 0) return;
    current->locals[current->localCount - 1].depth = current->scopeDepth;
}

void defineVariable(uint8_t global, bool isConst) {
    if (current->scopeDepth > 0) {
        markInitialized();
        return;
    }
    emitBytes(isConst ? OP_DEFINE_GLOBAL_CONST : OP_DEFINE_GLOBAL, global);
}

int resolveLocal(Compiler* compiler, Token* name) {
    for (int i = compiler->localCount - 1; i >= 0; i--) {
        Local* local = &compiler->locals[i];
        if (identifiersEqual(name, &local->name)) {
            if (local->depth == -1) {
                error("Can't read local variable in its own initializer.");
            }
            return i;
        }
    }

    return -1;
}

static int addUpvalue(Compiler* compiler, uint8_t index, bool isLocal,
                      bool isConst) {
    int upvalueCount = compiler->function->upvalueCount;

    for (int i = 0; i < upvalueCount; i++) {
        Upvalue* upvalue = &compiler->upvalues[i];
        if (upvalue->index == index && upvalue->isLocal == isLocal) return i;
    }

    if (upvalueCount == UINT8_COUNT) {
        error("Too many closure variables in function.");
        return 0;
    }

    compiler->upvalues[upvalueCount].isLocal = isLocal;
    compiler->upvalues[upvalueCount].index = index;
    compiler->upvalues[upvalueCount].isConst = isConst;
    return compiler->function->upvalueCount++;
}

int resolveUpvalue(Compiler* compiler, Token* name) {
    if (compiler->enclosing == NULL) return -1;

    int local = resolveLocal(compiler->enclosing, name);
    if (local != -1) {
        bool isConst = compiler->enclosing->locals[local].isConst;
        compiler->enclosing->locals[local].isCaptured = true;
        return addUpvalue(compiler, (uint8_t)local, true, isConst);
    }

    int upvalue = resolveUpvalue(compiler->enclosing, name);
    if (upvalue != -1) {
        return addUpvalue(compiler, (uint8_t)upvalue, false,
                          compiler->enclosing->upvalues[upvalue].isConst);
    }

    return -1;
}
void addLocal(Token name, bool isConst) {
    if (current->localCount == UINT8_COUNT) {
        error("Too many local variables in function.");
        return;
    }
    Local* local = &current->locals[current->localCount++];
    local->name = name;
    local->isConst = isConst;
    local->isCaptured = false;
    local->depth = -1;
}

void variable(bool canAssign) { namedVariable(parser.previous, canAssign); }

void namedVariable(Token name, bool canAssign) {
    int arg;
    uint8_t getOp;
    uint8_t setOp;
    bool isConst = false;

    TokenType assignOp = canAssign ? matchAssignmentOperator() : TOKEN_ERROR;

    if ((arg = resolveLocal(current, &name)) != -1) {
        getOp = OP_GET_LOCAL;
        setOp = OP_SET_LOCAL;
        isConst = current->locals[arg].isConst;
    } else if ((arg = resolveUpvalue(current, &name)) != -1) {
        getOp = OP_GET_UPVALUE;
        setOp = OP_SET_UPVALUE;
        isConst = current->upvalues[arg].isConst;
    } else {
        arg = identifierConstant(&name);
        getOp = OP_GET_GLOBAL;
        setOp = OP_SET_GLOBAL;
    }

    updateState.getOp = getOp;
    updateState.setOp = setOp;
    updateState.target = UPDATE_TARGET_VARIABLE;

    updateState.arg = arg;
    updateState.className = arg;
    updateState.classGetOp = getOp;
    updateState.isConst = isConst;

    if (updateState.currentUpdate != UPDATE_NONE) {
        emitBytes(getOp, arg);
        return;
    }

    if (canAssign && assignOp != TOKEN_ERROR) {
        if (isConst) {
            error("Cannot assign to const variable.");
        }

        emitSetBytes(setOp, getOp, arg, assignOp);
    } else {
        emitBytes(getOp, arg);
    }
}