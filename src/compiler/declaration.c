#include "compiler_common.h"

void classDeclaration() {
    consume(TOKEN_IDENTIFIER, "Expect class name.");
    Token className = parser.previous;
    uint8_t nameConstant = identifierConstant(&parser.previous);
    declareVariable(true);

    emitBytes(OP_CLASS, nameConstant);
    defineVariable(nameConstant, true);

    ClassCompiler classCompiler;
    classCompiler.name = parser.previous;
    classCompiler.hasSuperclass = false;
    classCompiler.enclosing = currentClass;
    currentClass = &classCompiler;

    if (match(TOKEN_LESS)) {
        consume(TOKEN_IDENTIFIER, "Expect superclass name.");
        variable(false);
        if (identifiersEqual(&className, &parser.previous)) {
            error("A class can't inherit from itself.");
        }

        beginScope();
        addLocal(syntheticToken("super"), true);
        defineVariable(0, true);

        namedVariable(className, false);
        emitByte(OP_INHERIT);
        classCompiler.hasSuperclass = true;
    }

    namedVariable(className, false);
    consume(TOKEN_LEFT_BRACE, "Expect '{' before class body.");
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        method();
    }
    consume(TOKEN_RIGHT_BRACE, "Expect '}' after class body.");
    emitByte(OP_POP);

    if (classCompiler.hasSuperclass) {
        endScope();
    }

    currentClass = currentClass->enclosing;
}

void varDeclaration() {
    uint8_t global = parseVariable("Expect variable name.", false);

    if (match(TOKEN_EQUAL))
        expression();
    else
        emitByte(OP_NULL);

    consume(TOKEN_SEMICOLON, "Expect ';' after var declaration");

    defineVariable(global, false);
}

void constDeclaration() {
    uint8_t global = parseVariable("Expect variable name.", true);

    if (match(TOKEN_EQUAL))
        expression();
    else {
        error("Const variable must be initialized.");
        emitByte(OP_NULL);
    }

    consume(TOKEN_SEMICOLON, "Expect ';' after const declaration");

    defineVariable(global, true);
}

void functionDeclaration() {
    uint8_t global = parseVariable("Expect function name.", true);
    markInitialized();
    function(TYPE_FUNCTION);
    defineVariable(global, true);
}
