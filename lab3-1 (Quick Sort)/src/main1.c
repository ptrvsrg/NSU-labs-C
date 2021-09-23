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
}

void Swap(int* Value1, int* Value2) //Обмен значениями
{
	int Buffer = *Value1;
	*Value1 = *Value2;
	*Value2 = Buffer;
}

void QuickSort(int* Array, int StartPosition, int EndPosition) //Сортировка алгоритмом Quick Sort
{
	if (StartPosition < EndPosition)
	{
		int Start = StartPosition;
		int End = EndPosition;
		int ComprasionValue = Array[(StartPosition + EndPosition) / 2];

		while (Start < End)
		{
			while (Array[Start] < ComprasionValue)
			{
				Start++;
			}
			while (Array[End] > ComprasionValue)
			{
				End--;
			}

			if (Start <= End)
			{
				Swap(&Array[Start], &Array[End]);

				Start++;
				End--;
			}
		}

		QuickSort(Array, Start, EndPosition);
		QuickSort(Array, StartPosition, End);
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

	QuickSort(Array, 0, ArraySize - 1);
	OutputArray(ArraySize, Array);
	free(Array);

	return SUCCESS;
}
