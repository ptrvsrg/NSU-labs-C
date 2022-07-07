#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "vector.h"

static int InputInt(void* value)
{
    return scanf("%d", (int*)value);
}

static int CompareInt(const void* value1, const void* value2)
{
    int intValue1 = *((int*)value1);
    int intValue2 = *((int*)value2);
    return intValue1 > intValue2 ? 1 :
    intValue1 == intValue2 ? 0 : -1;
}

static int OutputInt(const void* value)
{
    int intValue = *((int*)value);
    return printf("%d ", intValue);
}

int main(void)
{
	TVector vector = InputVector(sizeof(int), InputInt);
	QuickSortVector(&vector, CompareInt);
	OutputVector(vector, OutputInt);
	DestroyVector(&vector);

	return EXIT_SUCCESS;
}
