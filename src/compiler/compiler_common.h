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

UpdateState updateState;

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
Parser parser;

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

void initCompiler(Compiler* compiler, FunctionType type);
ObjFunction* endCompiler();

// util
void advance();
void consume(TokenType type, const char* message);
bool check(TokenType type);
bool match(TokenType type);
void emitByte(uint8_t byte);
void emitBytes(uint8_t byte1, uint8_t byte2);
int emitJump(uint8_t instruction);
void emitLoop(int loopStart);
void emitConstant(Value value);
void patchJump(int offset);
void emitReturn();
uint8_t makeConstant(Value value);
uint8_t identifierConstant(Token* name);
Token syntheticToken(const char* text);
TokenType matchAssignmentOperator();
bool identifiersEqual(Token* a, Token* b);
void emitPopToCount(int targetCount);
void emitSetBytes(uint8_t setOp, uint8_t getOp, uint8_t arg,
                  TokenType assignOp);

// expression
void expression();
void grouping(bool canAssign);
void number(bool canAssign);
void string(bool canAssign);
void unary(bool canAssign);
void binary(bool canAssign);
void variable(bool canAssign);
void literal(bool canAssign);
void and_(bool canAssign);
void or_(bool canAssign);
void ternary(bool canAssign);
void super_(bool canAssign);
void this_(bool canAssign);
void call(bool canAssign);
void dot(bool canAssign);
void instanceIndex(bool canAssign);
void preFixIncrement(bool canAssign);
void postFixIncrement(bool canAssign);
void preFixDecrement(bool canAssign);
void postFixDecrement(bool canAssign);
void array(bool canAssign);
void hashMap(bool canAssign);
void namedVariable(Token name, bool canAssign);
void emitOpByte(uint8_t op);

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

// declaration
void declaration();
void classDeclaration();
void varDeclaration();
void constDeclaration();
void functionDeclaration();

// variable
void variable(bool canAssign);
void namedVariable(Token name, bool canAssign);
void addLocal(Token name, bool isConst);
int resolveUpvalue(Compiler* compiler, Token* name);
int resolveLocal(Compiler* compiler, Token* name);
void defineVariable(uint8_t global, bool isConst);
void markInitialized();
uint8_t parseVariable(const char* errorMessage, bool isConst);
void declareVariable(bool isConst);

// parser
void parsePrecedence(Precedence precedence);
Chunk* currentChunk();
void synchronize();

// functions
uint8_t argumentList();
void function(FunctionType type);
void method();

// compiler
void resetUpdateState();
void beginScope();
void endScope();

void errorAt(Token* token, const char* message);
void error(const char* message);
void errorAtCurrent(const char* message);

#endif