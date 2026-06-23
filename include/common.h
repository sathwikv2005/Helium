#ifndef helium_common_h
#define helium_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HELIUM_PI 3.14159265358979323846

#define NAN_BOXING
#define UINT8_COUNT (UINT8_MAX + 1)

#if defined(__GNUC__) || defined(__clang__)
#define HELIUM_NOINLINE __attribute__((noinline))
#else
#define HELIUM_NOINLINE
#endif

#endif