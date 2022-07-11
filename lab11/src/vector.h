#ifndef VECTOR_H
#define VECTOR_H

#include "error.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct TVector
{
    int Count;
    int Max;
    int Size;
    void* Array;
} TVector;

TVector CreateVector(int size, int max);
void* GetVectorValue(int index, TVector vector);
void PushFrontVector(void* value, TVector* vector);
TVector ScanReverseVector(int size, int count, void (*Scan)(void*));
void DestroyVector(TVector* vector);

#endif
