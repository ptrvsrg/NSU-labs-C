#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"

typedef struct TMatrix
{
    int Count;
    int* Array;
} TMatrix;

TMatrix CreateMatrix(int count);
int GetValueMatrix(int row, int column, TMatrix matrix);
void PushMatrix(int row, int column, int value, TMatrix* matrix);
void DestroyMatrix(TMatrix* matrix);

#endif
