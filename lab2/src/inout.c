#define _CRT_SECURE_NO_WARNINGS
#include "inout.h"

void PrintSequence(const char* sequence)
{
	if (printf("%s\n", sequence) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }
}

static bool IsDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

static bool CheckInput(const char* sequence)
{
	int digitCount[10] = { 0 };

	for (int i = 0; sequence[i] != '\0'; ++i)
	{
		if (IsDigit(sequence[i]) && digitCount[sequence[i] - '0'] == 0)
        {
            ++digitCount[sequence[i] - '0'];
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputSequence(char* sequence)
{
    for  (int i = 0; i < SIZE_SEQUENCE + 1; ++i)
	{
		if ((sequence[i] = (char)getchar()) == EOF)
		{
			OtherError(__FILE__, __LINE__);
		}

		if (sequence[i] == '\n')
		{
			sequence[i] = '\0';
			break;
		}
	}

	if (!CheckInput(sequence))
	{
        BadInputError();
	}
}

void InputPermutationCount(unsigned int* count)
{
    if (scanf("%u", count) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }
}
