#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool InputArray(int arraySize, int* array)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if (scanf("%d", &array[i]) == EOF)
        {
            return false;
        }
	}

    return true;
}

bool OutputArray(int arraySize, const int* array)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if (printf("%d ", array[i]) == EOF)
        {
            return false;
        }
	}

    return true;
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

int main(void)
{
	int arraySize = 0;
	if (scanf("%d", &arraySize) == EOF)
    {
        return EXIT_FAILURE;
    }

	int* array = malloc(sizeof(*array) * arraySize);
    if (array == NULL)
    {
        return EXIT_FAILURE;
    }

	if (!InputArray(arraySize, array))
    {
        free(array);
        return EXIT_FAILURE;
    }

	QuickSort(array, 0, arraySize - 1);

	if (!OutputArray(arraySize, array))
    {
        free(array);
        return EXIT_FAILURE;
    }

	free(array);

	return EXIT_SUCCESS;
}
