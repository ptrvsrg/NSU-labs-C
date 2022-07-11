#include "vector.h"

TVector CreateVector(int size, int max)
{
    TVector vector = { 
        .Count = 0,
        .Max = max,
        .Size = size,
        .Array = NULL 
    };

    if (max > 0)
    {
        vector.Array = calloc(max, size);
        if (vector.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return vector;
}

void* GetVectorValue(int index, TVector vector)
{
    if (index < 0 || index >= vector.Max)
    {
        OtherError(__FILE__, __LINE__);
    }

    return (char*)vector.Array + index * vector.Size;
}

static bool IsEmptyVector(TVector vector)
{
    return vector.Count == 0;
}

static bool VectorOverflow(TVector vector)
{
    return vector.Count == vector.Max;
}

static void AssignValue(int size, void* dest, const void* src)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void PushFrontVector(void* value, TVector* vector)
{
    if (VectorOverflow(*vector))
    {
        OtherError(__FILE__, __LINE__);
    }

    AssignValue(vector->Size, GetVectorValue(vector->Max - 1 - vector->Count, *vector), value);
    ++vector->Count;
}

TVector ScanReverseVector(int size, int count, int (*Scan)(void*))
{
    TVector vector = CreateVector(size, count);

    void* value = malloc(size);
    if (value == NULL)
    {
        OtherError(__FILE__, __LINE__);
    }

    for (int i = 0; i < count; ++i)
    {
        if (Scan(value) != 1)
        {
            OtherError(__FILE__, __LINE__);
        }
        PushFrontVector(value, &vector);
    }

    free(value);
    return vector;
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    *vector = CreateVector(0, 0);
}
