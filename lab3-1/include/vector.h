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
    int* Array;
} TVector;

TVector InputVector();
void OutputVector(TVector vector);
void DestroyVector(TVector* vector);
void QuickSortVector(TVector* vector);

#endif 
