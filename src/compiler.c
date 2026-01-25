#include "../include/compiler.h"

#include <stdio.h>

#include "../include/common.h"
#include "../include/compiler.h"
#include "../include/scanner.h"

void compile(const char* source) {
    initScanner(source);
    int line = -1;
    for (;;) {
        Token token = scanToken();
        if (token.line != line) {
            printf("%4d\t", token.line);
            line = token.line;
        } else
            printf("    |\t");
        printf("%2d\t'%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF) break;
    }
}