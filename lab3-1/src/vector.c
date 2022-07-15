#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"

static TVector CreateVector(int max)
{
    TVector vector = { 0, max, NULL};

    if (max > 0)
    {
        vector.Array = calloc(max, sizeof(int));
        if (vector.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }
    
    return vector;
}

TVector InputVector()
{
    int max = 0;
    if (scanf("%d", &max) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }

    TVector vector = CreateVector(max);

    for (int i = 0; i < max; ++i)
    {
        if (scanf("%d", vector.Array + i) == EOF)
        {
            DestroyVector(&vector);
            OtherError(__FILE__, __LINE__);
        }

        ++vector.Count;
    }
    
    return vector;
}

void OutputVector(TVector vector)
{
    for (int i = 0; i < vector.Count; ++i)
    {
        if (printf("%d ", vector.Array[i]) == EOF)
        {
            DestroyVector(&vector);
            OtherError(__FILE__, __LINE__);
        }
    }
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    *vector = CreateVector(0);
}

static void Swap(int* value1, int* value2)
{
    int buffer = *value1;
    *value1 = *value2;
    *value2 = buffer;
}

void QuickSortVector(TVector* vector)
{
    if (vector->Count > 1)
    {
        int beginPosition = 0;
        int endPosition = vector->Count - 1;
        int comprasionValue = vector->Array[endPosition / 2];

        while (beginPosition < endPosition)
        {
            while (vector->Array[beginPosition] < comprasionValue)
            {
                ++beginPosition;
            }
            while (vector->Array[endPosition] > comprasionValue)
            {
                --endPosition;
            }

            if (beginPosition <= endPosition)
            {
                Swap(vector->Array + beginPosition, vector->Array + endPosition);

                ++beginPosition;
                --endPosition;
            }
        }

        if (endPosition > 0)
        {
            int vectorCount = vector->Count;
            vector->Count = endPosition + 1;
            QuickSortVector(vector);
            vector->Count = vectorCount;
        }

        if (beginPosition < vector->Count - 1)
        {
            int* vectorArray = vector->Array;
            int vectorCount = vector->Count;
            vector->Array = vector->Array + beginPosition;
            vector->Count = vector->Count - beginPosition;
            QuickSortVector(vector);
            vector->Array = vectorArray;
            vector->Count = vectorCount;
        }
    }
}
