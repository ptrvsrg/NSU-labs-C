#include <stdlib.h>
#include "heap.h"

int main(void)
{
	THeap heap = InputHeap();
    OutputHeap(heap);
    DestroyHeap(&heap);

	return EXIT_SUCCESS;
}
