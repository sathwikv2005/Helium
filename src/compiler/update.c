#include "compiler_common.h"

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
