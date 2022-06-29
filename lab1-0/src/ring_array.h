#ifndef RING_ARRAY_H
#define RING_ARRAY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TRingArray
{
    int EndIndex;
    int Count;
    char* Array;
} TRingArray;

TRingArray CreateRingArray(int count);
bool InputTemplate(TRingArray* ringArray);
bool InputRingArray(TRingArray* ringArray);
bool ShiftRingArray(TRingArray* ringArray, int shift);
void DestroyRingArray(TRingArray* ringArray);

#endif
