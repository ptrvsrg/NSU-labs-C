#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool InputArray(int ArraySize, int* Array)
{
	for (int i = 0; i < ArraySize; i++)
	{
		if (scanf("%d", &Array[i]) == EOF)
		{
            return false;
		}
	}

    return true;
}

bool OutputArray(int ArraySize, const int* Array)
{
	for (int i = 0; i < ArraySize; i++)
	{
		if (printf("%d ", Array[i]) == EOF)
        {
            return false;
        }
	}

    return true;
}

void Swap(int* Value1, int* Value2)
{
	int Buffer = *Value1;
	*Value1 = *Value2;
	*Value2 = Buffer;
}

void GetAscendingBranch(int ArraySize, int Index, int* Array)
{
	int LargestIndex = Index;
    int LeftIndex = 2 * Index + 1;
    int RightIndex = 2 * Index + 2;

	if (LeftIndex < ArraySize && Array[LeftIndex] > Array[LargestIndex])
	{
		LargestIndex = LeftIndex;
	}

	if (RightIndex < ArraySize && Array[RightIndex] > Array[LargestIndex])
	{
		LargestIndex = RightIndex;
	}

	if (LargestIndex != Index)
	{
		Swap(&Array[Index], &Array[LargestIndex]);
		GetAscendingBranch(ArraySize, LargestIndex, Array);
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

int main(void)
{
	int ArraySize = 0;
	if (scanf("%d", &ArraySize) == EOF)
    {
        return EXIT_FAILURE;
    }

	int* Array = malloc(sizeof(*Array) * ArraySize);
    if (Array == NULL)
    {
        return EXIT_FAILURE;
    }

	if (!InputArray(ArraySize, Array))
    {
        free(Array);
        return EXIT_FAILURE;
    }

	HeapSort(ArraySize, Array);

	if (!OutputArray(ArraySize, Array))
    {
        free(Array);
        return EXIT_FAILURE;
    }
    
	free(Array);

	return EXIT_SUCCESS;
}
