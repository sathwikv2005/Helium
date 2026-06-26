#ifndef helium_common_h
#define helium_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HELIUM_PI 3.14159265358979323846

#define ANSI_RED "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_CYAN "\033[36m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_DIM "\x1b[2m"
#define ANSI_RESET "\x1b[0m"

#define NAN_BOXING
#define UINT8_COUNT (UINT8_MAX + 1)

#if defined(__GNUC__) || defined(__clang__)
#define HELIUM_NOINLINE __attribute__((noinline))
#else
#define HELIUM_NOINLINE
#endif

#endif