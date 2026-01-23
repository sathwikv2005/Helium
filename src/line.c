#include "../include/line.h"

#include "../include/common.h"
#include "../include/memory.h"

void initLineArray(LineArray* lines) {
    lines->count = 0;
    lines->capacity = 0;
    lines->runs = NULL;
}

void freeLineArray(LineArray* lines) {
    FREE_ARRAY(LineRun, lines->runs, lines->capacity);
    initLineArray(lines);
}