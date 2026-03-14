#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/chunk.h"
#include "../include/common.h"
#include "../include/debug.h"
#include "../include/vm.h"

static void printBanner() {
    printf("\033[36m");  // cyan
    printf("\033[3m");   // italic

    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#            _    _      _ _                               #\n");
    printf("#           | |  | |    | (_)                              #\n");
    printf("#           | |__| | ___| |_ _   _ _ __ ___                #\n");
    printf("#           |  __  |/ _ \\ | | | | | '_ ` _ \\               #\n");
    printf("#           | |  | |  __/ | | |_| | | | | | |              #\n");
    printf("#           |_|  |_|\\___|_|_|\\__,_|_| |_| |_|              #\n");
    printf("#                                                          #\n");
    printf("#                       Helium v0.1                        #\n");
    printf("#            Light as gas. Fast as lightning.              #\n");
    printf("#                                                          #\n");
    printf("############################################################\n\n");

    printf("\033[0m");
}

static void repl() {
    printBanner();

    char line[1024];
    for (;;) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);

    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n ", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    if (bytesRead < fileSize) {
        fprintf(stderr, "Cound not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char* path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[]) {
    initVM();

    if (argc == 1) {
        repl();
    } else if (argv[1][0] == '-') {
        fprintf(stderr, "Usage: helium <path> [-d|-dt|-dc]\n");
        exit(64);
    } else {
        const char* file = argv[1];

        for (int i = 2; i < argc; i++) {
            const char* arg = argv[i];

            if (strcmp(arg, "-d") == 0) {
                SET_DEBUG();
            } else if (strcmp(arg, "-dt") == 0) {
                SET_DEBUG_TRACE();
            } else if (strcmp(arg, "-dc") == 0) {
                SET_DEBUG_CODE();
            } else {
                fprintf(stderr, "Unknown flag: %s\n", arg);
                fprintf(stderr, "Usage: helium <path> [-d|-dt|-dc]\n");
                exit(64);
            }
        }

        runFile(file);
    }

    freeVM();
    return 0;
}