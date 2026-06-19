#include <stdlib.h>

#include "compiler_common.h"

void binary(bool canAssign) {
    TokenType operatorType = parser.previous.type;

    ParseRule* rule = getRule(operatorType);
    parsePrecedence((Precedence)(rule->precedence + 1));

    switch (operatorType) {
        case TOKEN_BANG_EQUAL:
            emitBytes(OP_EQUAL, OP_NOT);
            break;
        case TOKEN_EQUAL_EQUAL:
            emitByte(OP_EQUAL);
            break;
        case TOKEN_GREATER:
            emitByte(OP_GREATER);
            break;
        case TOKEN_GREATER_EQUAL:
            emitBytes(OP_LESS, OP_NOT);
            break;
        case TOKEN_LESS:
            emitByte(OP_LESS);
            break;
        case TOKEN_LESS_EQUAL:
            emitBytes(OP_GREATER, OP_NOT);
            break;
        case TOKEN_PLUS:
            emitByte(OP_ADD);
            break;
        case TOKEN_MINUS:
            emitByte(OP_SUBTRACT);
            break;
        case TOKEN_STAR:
            emitByte(OP_MULTIPLY);
            break;
        case TOKEN_SLASH:
            emitByte(OP_DIVIDE);
            break;
        case TOKEN_PERCENT:
            emitByte(OP_MODULO);
        default:
            return;
    }
}

void literal(bool canAssign) {
    switch (parser.previous.type) {
        case TOKEN_FALSE:
            emitByte(OP_FALSE);
            break;
        case TOKEN_TRUE:
            emitByte(OP_TRUE);
            break;
        case TOKEN_NULL:
            emitByte(OP_NULL);
            break;
        default:
            return;
    }
}

void unary(bool canAssign) {
    TokenType operatorType = parser.previous.type;

    parsePrecedence(PREC_UNARY);

    switch (operatorType) {
        case TOKEN_MINUS:
            emitByte(OP_NEGATE);
            break;
        case TOKEN_BANG:
            emitByte(OP_NOT);
            break;
        default:
            return;
    }
}

void or_(bool canAssign) {
    int elseJump = emitJump(OP_JUMP_IF_FALSE);
    int endJump = emitJump(OP_JUMP);

    patchJump(elseJump);
    emitByte(OP_POP);

    parsePrecedence(PREC_OR);
    patchJump(endJump);
}

void and_(bool canAssign) {
    int endJump = emitJump(OP_JUMP_IF_FALSE);

    emitByte(OP_POP);
    parsePrecedence(PREC_AND);

    patchJump(endJump);
}

void super_(bool canAssign) {
    if (currentClass == NULL) {
        error("Can't use 'super' outside of a class.");
    } else if (!currentClass->hasSuperclass) {
        error("Can't use 'super' in a class with no superclass.");
    }

    consume(TOKEN_DOT, "Expect '.' after 'super'.");
    consume(TOKEN_IDENTIFIER, "Expect superclass method name.");
    uint8_t name = identifierConstant(&parser.previous);
    namedVariable(syntheticToken("this"), false);
    if (match(TOKEN_LEFT_PAREN)) {
        uint8_t argCount = argumentList();
        namedVariable(syntheticToken("super"), false);
        emitBytes(OP_SUPER_INVOKE, name);
        emitByte(argCount);
    } else {
        namedVariable(syntheticToken("super"), false);
        emitBytes(OP_GET_SUPER, name);
    }
}

void ternary(bool canAssign) {
    int elseJump = emitJump(OP_JUMP_IF_FALSE);
    int endJump;

    emitByte(OP_POP);

    // true branch
    parsePrecedence(PREC_ASSIGNMENT);

    endJump = emitJump(OP_JUMP);

    patchJump(elseJump);
    emitByte(OP_POP);

    consume(TOKEN_COLON, "Expect ':' after expression.");

    // false branch
    parsePrecedence(PREC_ASSIGNMENT);

    patchJump(endJump);
}

void this_(bool canAssign) {
    if (currentClass == NULL) {
        error("Can't use 'this' outside of a class.");
        return;
    }
    variable(false);
}

void call(bool canAssign) {
    uint8_t argCount = argumentList();
    emitBytes(OP_CALL, argCount);
}

void dot(bool canAssign) {
    consume(TOKEN_IDENTIFIER, "Expect property name after '.'.");
    uint8_t name = identifierConstant(&parser.previous);

    updateState.target = UPDATE_TARGET_PROPERTY;
    updateState.arg = name;
    if (updateState.currentUpdate != UPDATE_NONE) {
        return;
    }

    TokenType assignOp = canAssign ? matchAssignmentOperator() : TOKEN_ERROR;

    if (assignOp != TOKEN_ERROR) {
        if (assignOp != TOKEN_EQUAL) {
            emitByte(OP_DUP);
            emitBytes(OP_GET_PROPERTY, name);
        }

        expression();

        emitOpByte(assignOp);
        emitBytes(OP_SET_PROPERTY, name);

    } else if (match(TOKEN_LEFT_PAREN)) {
        uint8_t argCount = argumentList();
        emitBytes(OP_INVOKE, name);
        emitByte(argCount);
    } else
        emitBytes(OP_GET_PROPERTY, name);
}

void hashMap(bool canAssign) {
    emitByte(OP_CREATE_MAP);
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        emitByte(OP_DUP);
        if (match(TOKEN_STRING)) {
            string(canAssign);
        } else if (match(TOKEN_IDENTIFIER) || match(TOKEN_NUMBER)) {
            emitConstant(OBJ_VAL(
                copyString(parser.previous.start, parser.previous.length)));
        } else {
            error("Expect a key");
        }
        consume(TOKEN_COLON, "Expect ':' after key.");
        expression();
        if (!check(TOKEN_RIGHT_BRACE))
            consume(TOKEN_COMMA, "Expect comma after value.");
        emitBytes(OP_SET_INDEX, OP_POP);
    }
    consume(TOKEN_RIGHT_BRACE, "Expect '}' at end of the map");
}

void array(bool canAssign) {
    emitByte(OP_CREATE_ARRAY);

    int capacityOffset = currentChunk()->count;
    emitByte(0);  // placeholder

    int count = 0;
    while (!check(TOKEN_RIGHT_SQUARE) && !check(TOKEN_EOF)) {
        expression();
        if (!check(TOKEN_RIGHT_SQUARE))
            consume(TOKEN_COMMA, "Expect comma after value.");
        emitByte(OP_PUSH);
        count++;
    }
    consume(TOKEN_RIGHT_SQUARE, "Expect ']' at end of the array");
    currentChunk()->code[capacityOffset] = count;
}

void grouping(bool canAssign) {
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

void number(bool canAssign) {
    double value = strtod(parser.previous.start, NULL);
    emitConstant(NUMBER_VAL(value));
}

void string(bool canAssign) {
    emitConstant(OBJ_VAL(
        copyString(parser.previous.start + 1, parser.previous.length - 2)));
}

void expression() { parsePrecedence(PREC_ASSIGNMENT); }