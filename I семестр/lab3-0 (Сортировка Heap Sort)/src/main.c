#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void InputArray(int ArraySize, int* Array)
{
	for (int i = 0; i < ArraySize; i++)
	{
		if (scanf("%d", &Array[i]) == EOF)
		{
			free(Array);
            assert(false);
		}
	}
}

void OutputArray(int ArraySize, const int* Array)
{
	for (int i = 0; i < ArraySize; i++)
	{
		printf("%d ", Array[i]);
	}
}

void Swap(int* Value1, int* Value2)
{
	int Buffer = *Value1;
	*Value1 = *Value2;
	*Value2 = Buffer;
}

void GetAscendingBranch(int ArraySize, int Index, int* Array)
{
	int Largest = Index;

	if ((2 * Index + 1) < ArraySize && Array[2 * Index + 1] > Array[Largest])
	{
		Largest = 2 * Index + 1;
	}

	if ((2 * Index + 2) < ArraySize && Array[2 * Index + 2] > Array[Largest])
	{
		Largest = 2 * Index + 2;
	}

	if (Largest != Index)
	{
		Swap(&Array[Index], &Array[Largest]);
		GetAscendingBranch(ArraySize, Largest, Array);
	}
}

void HeapSort(int ArraySize, int* Array)
{
	for (int i = ArraySize / 2 - 1; i >= 0; i--)
	{
		GetAscendingBranch(ArraySize, i, Array);
	}

	for (int i = ArraySize - 1; i > 0; i--)
	{
		Swap(&Array[0], &Array[i]);
		GetAscendingBranch(i, 0, Array);
	}
}

int main()
{
	int ArraySize = 0;
	assert(scanf("%d", &ArraySize) != EOF);

	int* Array = malloc(sizeof(*Array) * ArraySize);
    assert(Array != NULL);

	InputArray(ArraySize, Array);
	HeapSort(ArraySize, Array);
	OutputArray(ArraySize, Array);
    
	free(Array);

	return EXIT_SUCCESS;
}
