#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"

typedef struct TMatrix
{
    int Count;
    int Size;
    void* Array;
} TMatrix;

TMatrix CreateMatrix(int count, int size);
void* GetValueMatrix(int row, int column, TMatrix matrix);
bool IsNullValueMatrix(int size, void* value);
void PushMatrix(int row, int column, void* value, TMatrix* matrix);
void DestroyMatrix(TMatrix* matrix);

#endif
