#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNUSED(x) (void)(x);

enum
{
	SIZE_SEQUENCE = 10
};

bool PrintBadInput()
{
	if (puts("bad input") == EOF)
    {
        return false;
    }

    return true;
}

bool PrintSequence(const char* Sequence)
{
    UNUSED(Sequence);
	if (puts(Sequence) == EOF)
    {
        return false;
    }

    return true;
}

bool ThisIsDigits(char Symbol)
{
	return Symbol >= '0' && Symbol <= '9';
}

bool CheckInput(const char* Sequence)
{
	int CountEachDigit[10] = { 0 };

	for (int i = 0; Sequence[i] != '\0'; ++i)
	{
		if (ThisIsDigits(Sequence[i]) && CountEachDigit[Sequence[i] - '0'] == 0)
        {
            ++CountEachDigit[Sequence[i] - '0'];
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputSequence(char* Sequence)
{
    for (int i = 0; i < SIZE_SEQUENCE + 1; i++)
	{
		if ((Sequence[i] = (char)getchar()) == EOF)
		{
			return false;
		}

		if (Sequence[i] == '\n')
		{
			Sequence[i] = '\0';
			break;
		}

		if (i == SIZE_SEQUENCE)
		{
			return false;
		}
	}

	if (!CheckInput(Sequence))
	{
		return false;
	}

    return true;
}

void Swap(char* Number1, char* Number2)
{
	char Buffer = *Number1;
	*Number1 = *Number2;
	*Number2 = Buffer;
}

void ReverseSequencePart(int Begin, char* Sequence)
{
	int End = (int)strlen(Sequence) - 1;

	while (Begin < End)
	{
		Swap(&Sequence[Begin], &Sequence[End]);
		Begin++;
		End--;
	}
}

bool NarayanasAlgorithm(int PermutationCount, char* Sequence)
{
	int SequenceLength = (int)strlen(Sequence);

	for (int i = 0; i < PermutationCount; i++)
	{
		int Index1 = 0;
        int Index2 = 0;

		for (Index1 = SequenceLength - 2; ; Index1--)
		{
			if (Index1 < 0)
			{
				return;
			}

			if (Sequence[Index1] < Sequence[Index1 + 1])
			{
				break;
			}
		}

		for (Index2 = SequenceLength - 1; Index2 > Index1; Index2--)
		{
			if (Sequence[Index2] > Sequence[Index1])
			{
				break;
			}
		}

		Swap(&Sequence[Index1], &Sequence[Index2]);
		ReverseSequencePart(Index1 + 1, Sequence);

		if (!PrintSequence(Sequence))
        {
            return false;
        }
	}

    return true;
}

int main(void)
{
	char Sequence[SIZE_SEQUENCE + 1] = { 0 };

	if(!InputSequence(Sequence))
    {
        return PrintBadInput() ? EXIT_SUCCESS : EXIT_FAILURE;
    }

	int PermutationCount = 0;

	if (scanf("%d", &PermutationCount) == EOF || PermutationCount < 0)
	{
		return PrintBadInput() ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	if (!NarayanasAlgorithm(PermutationCount, Sequence))
    {
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}