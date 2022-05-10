#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define UNUSED(x) (void)(x);

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	SIZE_SEQUENCE = 10
};

void PrintBadInput()
{
	assert(puts("bad input") != EOF);
}

void PrintSequence(const char* Sequence)
{
    UNUSED(Sequence);
	assert(puts(Sequence) != EOF);
}

bool ThisIsDigits(char Symbol)
{
	return Symbol >= '0' && Symbol <= '9';
}

int CheckInput(const char* Sequence)
{
	const int Length = strlen(Sequence);
	int CountEachDigit[10] = { 0 };

	for (int i = 0; i < Length; ++i)
	{
		if (ThisIsDigits(Sequence[i]))
		{
			if (CountEachDigit[Sequence[i] - '0'] == 0)
			{
				++CountEachDigit[Sequence[i] - '0'];
			}
			else
			{
				return FAILURE;
			}
		}
		else
		{
			return FAILURE;
		}
	}

	return SUCCESS;
}

int InputSequence(char* Sequence)
{
    for (int i = 0; i < SIZE_SEQUENCE + 1; i++)
	{
		if ((Sequence[i] = getchar()) == EOF)
		{
			return FAILURE;
		}

		if (Sequence[i] == '\n')
		{
			Sequence[i] = '\0';
			break;
		}

		if (i == SIZE_SEQUENCE)
		{
			return FAILURE;
		}
	}

	if (CheckInput(Sequence) == FAILURE)
	{
		return FAILURE;
	}

    return SUCCESS;
}

void Swap(char* Number1, char* Number2)
{
	char Buffer = *Number1;
	*Number1 = *Number2;
	*Number2 = Buffer;
}

void ReverseSequencePart(int Begin, char* Sequence)
{
	int End = strlen(Sequence) - 1;

	while (Begin < End)
	{
		Swap(&Sequence[Begin], &Sequence[End]);
		Begin++;
		End--;
	}
}

void NarayanasAlgorithm(int PermutationCount, char* Sequence)
{
	const int SequenceLength = strlen(Sequence);

	for (int i = 0; i < PermutationCount; i++)
	{
		int Index1, Index2;

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
		PrintSequence(Sequence);
	}
}

int main()
{
	char Sequence[SIZE_SEQUENCE + 1];

	if(InputSequence(Sequence) == FAILURE)
    {
        PrintBadInput();
        return SUCCESS;
    }

	int PermutationCount = 0;

	if (scanf("%d", &PermutationCount) == EOF || PermutationCount < 0)
	{
		PrintBadInput();
		return SUCCESS;
	}

	NarayanasAlgorithm(PermutationCount, Sequence);
	return SUCCESS;
}