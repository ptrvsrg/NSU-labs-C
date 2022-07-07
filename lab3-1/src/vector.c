#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"

static TVector CreateVector(int max, int size)
{
    TVector vector = { 0, max, size, NULL};

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

static void* GetNthVector(TVector vector, int n)
{
    if (n >= vector.Max)
    {
        DestroyVector(&vector);
        OtherError(__FILE__, __LINE__);
    }

    return (char*)vector.Array + n * vector.Size;
}

TVector InputVector(int size, int (*input)(void*))
{
    int max = 0;
    if (scanf("%d", &max) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }

    TVector vector = CreateVector(max, size);

    for (int i = 0; i < max; ++i)
    {
        void* value = GetNthVector(vector, i);
        if (input(value) == EOF)
        {
            DestroyVector(&vector);
            OtherError(__FILE__, __LINE__);
        }

        ++vector.Count;
    }
    
    return vector;
}

void OutputVector(TVector vector, int (*output)(const void*))
{
    for (int i = 0; i < vector.Count; ++i)
    {
        if (output(GetNthVector(vector, i)) == EOF)
        {
            DestroyVector(&vector);
            OtherError(__FILE__, __LINE__);
        }
    }
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    *vector = CreateVector(0, 0);
}

static void Swap(void* value1, void* value2, int size)
{
    for (int i = 0; i < size; ++i)
    {
        char buffer = ((char*)value1)[i];
        ((char*)value1)[i] = ((char*)value2)[i];
        ((char*)value2)[i] = buffer;
    }
}

static void HelperQuickSort(TVector* vector, int startPosition, int finishPosition, int (*compare)(const void*, const void*))
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
		void* comprasionValue = GetNthVector(*vector, (startPosition + finishPosition) / 2);
        void* beginValue = GetNthVector(*vector, begin);
        void* endValue = GetNthVector(*vector, end);

		while (begin < end)
		{
			while (compare(beginValue, comprasionValue) < 0)
			{
				++begin;
                beginValue = GetNthVector(*vector, begin);
			}
			while (compare(comprasionValue, endValue) < 0)
			{
				--end;
                endValue = GetNthVector(*vector, end);
			}

			if (begin <= end)
			{
				Swap(beginValue, endValue, vector->Size);

				++begin;
                beginValue = GetNthVector(*vector, begin);
				--end;
                endValue = GetNthVector(*vector, end);
			}
		}

		HelperQuickSort(vector, begin, finishPosition, compare);
		HelperQuickSort(vector, startPosition, end, compare);
	}
}

void QuickSortVector(TVector* vector, int (*compare)(const void*, const void*))
{
    HelperQuickSort(vector, 0, vector->Count - 1, compare);
}
