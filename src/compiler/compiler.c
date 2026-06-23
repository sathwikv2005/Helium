#include "compiler_common.h"

LoopContext loopStack[64];
int loopDepth = 0;

Parser parser;
UpdateState updateState;

Compiler* current = NULL;

ClassCompiler* currentClass = NULL;

ObjModule* currentModule = NULL;
bool isExported = false;

Chunk* currentChunk() { return &current->function->chunk; }

void resetUpdateState() {
    updateState.target = UPDATE_TARGET_NONE;
    updateState.currentUpdate = UPDATE_NONE;
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
    } else if (match(TOKEN_IMPORT)) {
        importStatement();
    } else
        expressionStatement();
}

void declaration() {
    bool prev = isExported;
    if (match(TOKEN_EXPORT)) {
        isExported = true;

        if (match(TOKEN_EXPORT)) {
            error("Duplicate 'export' modifier.");
        }
    }

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
    isExported = prev;
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

ObjFunction* compileModule(const char* source, ObjModule* module) {
    currentModule = module;
    return compile(source);
}

void markCompilerRoots() {
    Compiler* compiler = current;
    while (compiler != NULL) {
        markObject((Obj*)compiler->function);
        compiler = compiler->enclosing;
    }
}