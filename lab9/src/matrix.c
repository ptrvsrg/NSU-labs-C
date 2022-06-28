#include "matrix.h"

static int SumArithmeticProgression(int begin, int end, int count)
{
    return (begin + end) * count / 2;
}

static int Min(int a, int b)
{
    return (a < b) ? a : b;
}

static int Max(int a, int b)
{
    return (a < b) ? b : a;
}

TMatrix CreateMatrix(int count)
{
    TMatrix matrix = { count, NULL };

    if (count > 0)
    {
        matrix.Array = calloc(SumArithmeticProgression(1, count, count), sizeof(int));
        if (matrix.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return matrix;
}

static int GetElementIndex(int row, int column, TMatrix matrix)
{
    int min = Min(row, column);
    int max = Max(row, column);
    return SumArithmeticProgression(matrix.Count, matrix.Count - min + 1, min) + (max - min);
}

int GetValueMatrix(int row, int column, TMatrix matrix)
{
    int index = GetElementIndex(row, column, matrix);
    return matrix.Array[index];
}

void PushMatrix(int row, int column, int value, TMatrix* matrix)
{
    if (GetValueMatrix(row, column, *matrix) != 0)
    {
        OtherError(__FILE__, __LINE__);
    }

    int index = GetElementIndex(row, column, *matrix);
    matrix->Array[index] = value;
}

void DestroyMatrix(TMatrix* matrix)
{
    free(matrix->Array);
    *matrix = CreateMatrix(0);
}
