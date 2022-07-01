#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "vector.h"

static int InputInt(int* value)
{
    return scanf("%d", value);
}

static int CompareInt(const int* value1, const int* value2)
{
    return ((*value1) > (*value2)) ? 1 :
    ((*value1) == (*value2)) ? 0 : -1;
}

static int OutputInt(const int* value)
{
    return printf("%d ", *value);
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	TVector vector = InputVector(sizeof(int), InputInt);
	QuickSortVector(&vector, CompareInt);
	OutputVector(vector, OutputInt);
	DestroyVector(&vector);

	return EXIT_SUCCESS;
}
