#include <stdio.h>
#include "vector.h"

int main(void)
{
	TVector vector = InputVector();
	QuickSortVector(&vector);
	OutputVector(vector);
	DestroyVector(&vector);

	return EXIT_SUCCESS;
}
