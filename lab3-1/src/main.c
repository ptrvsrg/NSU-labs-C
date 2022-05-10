#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

void InputArray(int arraySize, int* array)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if(scanf("%d", &array[i]) != 1)
        {
            free(array);
            assert(false);
        }
	}
}

void OutputArray(int arraySize, const int* array)
{
	for (int i = 0; i < arraySize; ++i)
	{
		printf("%d ", array[i]);
	}
}

void Swap(int* value1, int* value2)
{
	int buffer = *value1;
	*value1 = *value2;
	*value2 = buffer;
}

void QuickSort(int* array, int startPosition, int finishPosition)
{
	if (startPosition < finishPosition)
	{
		int begin = startPosition;
		int end = finishPosition;
		int comprasionValue = array[(startPosition + finishPosition) / 2];

		while (begin < end)
		{
			while (array[begin] < comprasionValue)
			{
				++begin;
			}
			while (array[end] > comprasionValue)
			{
				--end;
			}

			if (begin <= end)
			{
				Swap(array + begin, array + end);

				++begin;
				--end;
			}
		}

		QuickSort(array, begin, finishPosition);
		QuickSort(array, startPosition, end);
	}
}

int main()
{
	int arraySize = 0;

	assert(scanf("%d", &arraySize) == 1);

	int* array = malloc(sizeof(*array) * arraySize);
    assert(array != NULL);

	InputArray(arraySize, array);

	QuickSort(array, 0, arraySize - 1);
	OutputArray(arraySize, array);
	free(array);

	return SUCCESS;
}
