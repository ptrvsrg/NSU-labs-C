#include "matrix.h"
#define CHAR_SIZE (int)8
#define MASK_BASE (int)128

TMatrix CreateMatrix(int size)
{
    TMatrix matrix = { size, NULL };
    int matrixSize = size * size / CHAR_SIZE;
    matrixSize += (size * size % CHAR_SIZE == 0) ? 0 : 1;

    if (matrixSize > 0)
    {
        matrix.Array = calloc(matrixSize, sizeof(char));
        if (matrix.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return matrix;
}

void AddMatrixValue(int row, int column, TMatrix* matrix)
{
    if (row < 0 || column < 0 || row >= matrix->Size || column >= matrix->Size)
    {
        DestroyMatrix(matrix);
        OtherError(__FILE__, __LINE__);
    }

    int bitIndex = row * matrix->Size + column;
    int symbolIndex = bitIndex / CHAR_SIZE;
    unsigned char mask = MASK_BASE >> (bitIndex % CHAR_SIZE);
    matrix->Array[symbolIndex] |= mask;
}

bool GetMatrixValue(int row, int column, TMatrix matrix)
{
    if (row < 0 || column < 0 || row >= matrix.Size || column >= matrix.Size)
    {
        DestroyMatrix(&matrix);
        OtherError(__FILE__, __LINE__);
    }

    int bitIndex = row * matrix.Size + column;
    int symbolIndex = bitIndex / CHAR_SIZE;
    unsigned char mask = MASK_BASE >> bitIndex % CHAR_SIZE;
    return (mask & matrix.Array[symbolIndex]) != 0;
}

void DestroyMatrix(TMatrix* matrix)
{
    free(matrix->Array);    
    *matrix = CreateMatrix(0);
}
