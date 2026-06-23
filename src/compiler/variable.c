#include "compiler_common.h"

uint8_t parseVariable(const char* errorMessage, bool isConst) {
    consume(TOKEN_IDENTIFIER, errorMessage);

    declareVariable(isConst);
    if (current->scopeDepth > 0) return 0;

    return identifierConstant(&parser.previous);
}

void defineVariable(uint8_t global, bool isConst) {
    if (current->scopeDepth > 0) {
        markInitialized();
        return;
    }
    uint8_t op = isConst ? OP_DEFINE_GLOBAL_CONST : OP_DEFINE_GLOBAL;
    if (isExported) op = isConst ? OP_EXPORT_DEFINE_CONST : OP_EXPORT_DEFINE;
    emitBytes(op, global);
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
        if (isExported) {
            setOp = OP_EXPORT_SET;
            getOp = OP_EXPORT_GET;
        }
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

uint8_t identifierConstant(Token* name) {
    return makeConstant(OBJ_VAL(copyString(name->start, name->length)));
}