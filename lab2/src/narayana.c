#include "narayana.h"

static void Swap(char* number1, char* number2)
{
	char Buffer = *number1;
	*number1 = *number2;
	*number2 = Buffer;
}

static void ReverseArray(int length, char* array)
{
    int begin = 0;
    int end = length - 1;

	while (begin < end)
	{
		Swap(array + begin, array + end);
		++begin;
		--end;
	}
}

void NarayanasAlgorithm(int permutationCount, char* sequence)
{
    int sequenceLength = (int)strlen(sequence);
	for (int i = 0; i < permutationCount; ++i)
	{
		int index1 = 0;
        int index2 = 0;

		for (index1 = sequenceLength - 2; ; --index1)
		{
			if (index1 < 0)
			{
				return;
			}

			if (sequence[index1] < sequence[index1 + 1])
			{
				break;
			}
		}

		for (index2 = sequenceLength - 1; index2 > index1; --index2)
		{
			if (sequence[index2] > sequence[index1])
			{
				break;
			}
		}

		Swap(sequence + index1, sequence + index2);
		ReverseArray(sequenceLength - index1 - 1, sequence + index1 + 1);
        PrintSequence(sequence);
	}
}
