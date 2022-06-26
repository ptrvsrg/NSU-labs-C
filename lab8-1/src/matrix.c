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

TMatrix CreateMatrix(int count, int size)
{
    TMatrix matrix = { count, size, NULL };

    if (count > 0)
    {
        matrix.Array = calloc(SumArithmeticProgression(1, count, count), size);
        if (matrix.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return matrix;
}

void* GetValueMatrix(int row, int column, TMatrix matrix)
{
    int min = Min(row, column);
    int max = Max(row, column);
    return (char*)matrix.Array + matrix.Size * (SumArithmeticProgression(matrix.Count, matrix.Count - min + 1, min) + (max - min));
}

static void AssignMatrix(int size, const void* src, void* dest)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

bool IsNullValueMatrix(int size, void* value)
{
    for (int i = 0; i < size; ++i)
    {
        if (((char*)value)[i] != 0)
        {
            return false;
        }
    }

    return true;
}

void PushMatrix(int row, int column, void* value, TMatrix* matrix)
{
    void* dest = GetValueMatrix(row, column, *matrix);
    if (!IsNullValueMatrix(matrix->Size, dest))
    {
        OtherError(__FILE__, __LINE__);
    }

    AssignMatrix(matrix->Size, value, dest);
}

void DestroyMatrix(TMatrix* matrix)
{
    free(matrix->Array);
    *matrix = CreateMatrix(0, 0);
}
