#ifndef helium_compiler_common
#define helium_compiler_common
#include "../../include/common.h"
#include "../../include/compiler.h"
#include "../../include/debug.h"
#include "../../include/memory.h"
#include "../../include/scanner.h"

typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_TERNARY,     // condition ? if_true : else
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // / *
    PREC_UNARY,       // - !
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)(bool canAssign);

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

typedef struct {
    Token name;
    int depth;
    bool isConst;
    bool isCaptured;
} Local;

typedef struct {
    uint8_t index;
    bool isLocal;
    bool isConst;
} Upvalue;

typedef enum {
    UPDATE_NONE,
    UPDATE_PREFIX_INC,
    UPDATE_PREFIX_DEC,
    UPDATE_POSTFIX_INC,
    UPDATE_POSTFIX_DEC
} UpdateType;
typedef enum {
    UPDATE_TARGET_NONE,
    UPDATE_TARGET_VARIABLE,
    UPDATE_TARGET_PROPERTY,
    UPDATE_TARGET_INDEX
} UpdateTarget;

typedef struct {
    UpdateType currentUpdate;
    UpdateTarget target;

    uint8_t getOp;
    uint8_t setOp;
    uint8_t arg;

    uint8_t ownerGetOp;
    uint8_t ownerArg;

    uint8_t className;
    uint8_t classGetOp;

    bool isConst;
} UpdateState;

extern UpdateState updateState;

typedef enum {
    TYPE_FUNCTION,
    TYPE_METHOD,
    TYPE_SCRIPT,
    TYPE_INITIALIZER
} FunctionType;

typedef struct Compiler {
    struct Compiler* enclosing;

    ObjFunction* function;
    FunctionType type;

    Local locals[UINT8_COUNT];
    int localCount;
    Upvalue upvalues[UINT8_COUNT];
    int scopeDepth;
} Compiler;

typedef struct ClassCompiler {
    struct ClassCompiler* enclosing;
    Token name;
    bool hasSuperclass;
} ClassCompiler;

extern ParseRule rules[];
extern Parser parser;

#define MAX_BREAKS 256
typedef struct {
    int start;
    int scopeDepth;
    int localCount;
    int breakCount;
    int breaks[MAX_BREAKS];
} LoopContext;

ParseRule* getRule(TokenType type);

extern Compiler* current;
extern ClassCompiler* currentClass;
extern LoopContext loopStack[64];
extern int loopDepth;

// util
void errorAt(Token* token, const char* message);
void error(const char* message);
void errorAtCurrent(const char* message);
void advance();
void consume(TokenType type, const char* message);
bool check(TokenType type);
bool match(TokenType type);
Token syntheticToken(const char* text);
TokenType matchAssignmentOperator();
bool identifiersEqual(Token* a, Token* b);
uint8_t makeConstant(Value value);

// emit
void emitByte(uint8_t byte);
void emitBytes(uint8_t byte1, uint8_t byte2);
int emitJump(uint8_t instruction);
void emitLoop(int loopStart);
void emitConstant(Value value);
void patchJump(int offset);
void emitReturn();
void emitPopToCount(int targetCount);
void emitOpByte(uint8_t op);
void emitSetBytes(uint8_t setOp, uint8_t getOp, uint8_t arg,
                  TokenType assignOp);

// expression
void expression();
void grouping(bool canAssign);
void number(bool canAssign);
void string(bool canAssign);
void unary(bool canAssign);
void binary(bool canAssign);
void literal(bool canAssign);
void and_(bool canAssign);
void or_(bool canAssign);
void ternary(bool canAssign);
void super_(bool canAssign);
void this_(bool canAssign);
void call(bool canAssign);
void dot(bool canAssign);
void instanceIndex(bool canAssign);
void array(bool canAssign);
void hashMap(bool canAssign);
void typeof_(bool canAssign);

// statement
void statement();
void block();
void expressionStatement();
void ifStatement();
void whileStatement();
void forStatement();
void breakStatement();
void continueStatement();
void printStatement();
void returnStatement();
void importStatement();

// declaration
void declaration();
void classDeclaration();
void varDeclaration();
void constDeclaration();
void functionDeclaration();

// variable
void variable(bool canAssign);
void namedVariable(Token name, bool canAssign);
void defineVariable(uint8_t global, bool isConst);
uint8_t parseVariable(const char* errorMessage, bool isConst);
uint8_t identifierConstant(Token* name);

// inplace update
void preFixIncrement(bool canAssign);
void postFixIncrement(bool canAssign);
void preFixDecrement(bool canAssign);
void postFixDecrement(bool canAssign);

// function
uint8_t argumentList();
void function(FunctionType type);
void method();

// scope
void beginScope();
void endScope();
void markInitialized();
void declareVariable(bool isConst);
void addLocal(Token name, bool isConst);
int resolveLocal(Compiler* compiler, Token* name);
int resolveUpvalue(Compiler* compiler, Token* name);

// parser
void parsePrecedence(Precedence precedence);
void synchronize();

// compiler
Chunk* currentChunk();
void initCompiler(Compiler* compiler, FunctionType type);
ObjFunction* endCompiler();
void resetUpdateState();
extern ObjModule* currentModule;
extern bool isExported;

#endif