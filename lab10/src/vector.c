#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"

TVector CreateVector(int max, int size)
{
    TVector vector = { 0, max, size, NULL };

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

static bool IsEmptyVector(TVector vector)
{
    return vector.Count == 0;
}

void AssignVector(int size, const void* src, void* dest)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void* GetNthVector(TVector vector, int n)
{
    if (n >= vector.Max)
    {
        OtherError(__FILE__, __LINE__);
    }

    return (char*)vector.Array + n * vector.Size;
}

TVector InputVector(int count, int size, int (*Scan)(void*))
{
    TVector vector = CreateVector(count, size);

    for (int i = 0; i < count; ++i)
    {
        if (Scan(GetNthVector(vector, i)) == EOF)
        {
            DestroyVector(&vector);
            BadNumberOfLinesError();
        }

        ++vector.Count;
    }

    return vector;
} 

void DestroyVector(TVector* vector)
{
    if (!IsEmptyVector(*vector))
    {
        free(vector->Array);
    }
    
    vector->Array = NULL;
    vector->Count = 0;
    vector->Max = 0;
    vector->Size = 0;
}
