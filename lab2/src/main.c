#include <stdlib.h>
#include "inout.h"
#include "narayana.h"

int main(void)
{
	char sequence[SIZE_SEQUENCE + 1] = { 0 };
	InputSequence(sequence);

	unsigned int permutationCount = 0;
    InputPermutationCount(&permutationCount);

	NarayanasAlgorithm(permutationCount, sequence);

	return EXIT_SUCCESS;
}
