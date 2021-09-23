#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

int InputArray(int ArraySize, int* Array) //Ввод массива
{
	for (int i = 0; i < ArraySize; i++)
	{
		if (scanf("%d", &Array[i]) == EOF)
		{
			return FAILURE;
		}
	}

	return SUCCESS;
}

void OutputArray(int ArraySize, int* Array) //Вывод массива
{
	for (int i = 0; i < ArraySize; i++)
	{
		printf("%d ", Array[i]);
	}
	printf("\n");
}

void Swap(int* Value1, int* Value2) //Обмен значениями
{
	int Buffer = *Value1;
	*Value1 = *Value2;
	*Value2 = Buffer;
}

void GetAscendingBranch(int ArraySize, int Index, int* Array) //Получение возрастающей ветки
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

void HeapSort(int ArraySize, int* Array) //Сортировка алгоритмом Heap Sort
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

	if (scanf("%d", &ArraySize) == EOF)
	{
		return SUCCESS;
	}

	int* Array = malloc(sizeof(*Array) * ArraySize);

	if (Array == NULL)
	{
		return SUCCESS;
	}

	if (InputArray(ArraySize, Array) == FAILURE)
	{
		free(Array);
		return SUCCESS;
	}

	HeapSort(ArraySize, Array);
	OutputArray(ArraySize, Array);
	free(Array);

	return SUCCESS;
}
