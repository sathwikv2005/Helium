#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/chunk.h"
#include "../include/common.h"
#include "../include/debug.h"
#include "../include/vm.h"
#include "version.h"

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
    printf("#                      Helium v%-28s#\n", HELIUM_VERSION_STRING);
    printf("#            Light as gas. Fast as lightning.              #\n");
    printf("#                                                          #\n");
    printf("############################################################\n\n");

    printf("\033[0m");
}

static void printVersion() {
    printf("Helium v%s", HELIUM_VERSION_STRING);
#ifdef HELIUM_DEBUG
    printf("-debug");
#endif
    printf("\n");
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

char* readFile(const char* path) {
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
    if (result == INTERPRET_EXIT) exit(vm.exitCode);
}
int main(int argc, const char* argv[]) {
    initVM();

    if (argc == 1) {
        repl();
    } else if (strcmp(argv[1], "-v") == 0 ||
               strcmp(argv[1], "--version") == 0) {
        printVersion();
    } else if (argv[1][0] == '-') {
        fprintf(stderr, "Unknown option '%s'.\n", argv[1]);
        fprintf(stderr, "Usage: helium <path>");

#ifdef HELIUM_DEBUG
        fprintf(stderr, " [-d|-dt|-dc|-dsgc|-dlgc]");
#endif

        fprintf(stderr, " | -v | --version\n");
        exit(64);
    } else {
        const char* file = argv[1];

        for (int i = 2; i < argc; i++) {
            const char* arg = argv[i];

#ifdef HELIUM_DEBUG
            if (strcmp(arg, "-d") == 0) {
                SET_DEBUG();

            } else if (strcmp(arg, "-dt") == 0) {
                SET_DEBUG_TRACE();

            } else if (strcmp(arg, "-dc") == 0) {
                SET_DEBUG_CODE();

            } else if (strcmp(arg, "-dsgc") == 0) {
                SET_DEBUG_STRESS_GC();

            } else if (strcmp(arg, "-dlgc") == 0) {
                SET_DEBUG_LOG_GC();

            } else
#endif
            {
                fprintf(stderr, "Unknown option '%s'.\n", arg);
                exit(64);
            }
        }

        runFile(file);
    }

    freeVM();
    return 0;
}