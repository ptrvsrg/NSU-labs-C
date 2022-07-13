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

static void HelperQuickSort(TVector* vector, int startPosition, int finishPosition)
{
    if (startPosition < 0 || finishPosition >= vector->Count)
    {
        DestroyVector(vector);
        OtherError(__FILE__, __LINE__);
    }

	if (startPosition < finishPosition)
	{
		int begin = startPosition;
		int end = finishPosition;
		int comprasionValue = vector->Array[(startPosition + finishPosition) / 2];

		while (begin < end)
		{
			while (vector->Array[begin] < comprasionValue)
			{
				++begin;
			}
			while (vector->Array[end] > comprasionValue)
			{
				--end;
			}

			if (begin <= end)
			{
				Swap(vector->Array + begin, vector->Array + end);

				++begin;
				--end;
			}
		}

		HelperQuickSort(vector, begin, finishPosition);
		HelperQuickSort(vector, startPosition, end);
	}
}

void QuickSortVector(TVector* vector)
{
    HelperQuickSort(vector, 0, vector->Count - 1);
}
