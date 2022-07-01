#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TVector
{
    int Count;
    int Max;
    int Size;
    void* Array;
} TVector;

TVector InputVector(int size, int (*input)(void*));
void OutputVector(TVector vector, int (*output)(const void*));
void DestroyVector(TVector* vector);
void QuickSortVector(TVector* vector, int (*compare)(const void*, const void*));

#endif 
