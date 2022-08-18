#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"

typedef struct TMatrix
{
    int Size;
    char* Array;
} TMatrix;

TMatrix CreateMatrix(int size);
void AddMatrixValue(int row, int column, TMatrix* matrix);
bool GetMatrixValue(int row, int column, TMatrix matrix);
void DestroyMatrix(TMatrix* matrix);

#endif
