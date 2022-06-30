#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "error.h"

typedef struct THeap
{
    int Count;
    int Max;
    int* Key;
} THeap;

THeap InputHeap(void);
void OutputHeap(THeap heap);
void DestroyHeap(THeap* heap);

#endif
