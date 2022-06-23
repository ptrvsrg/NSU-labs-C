#ifndef VECTOR_H
#define VECTOR_H

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

TVector CreateVector(int max, int size);
void AssignVector(int size, const void* src, void* dest);
void* GetNthElementVector(TVector vector, int n);
TVector InputVector(int count, int size, int (*Scan)(void*));
void DestroyVector(TVector* vector);

#endif
