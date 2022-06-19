#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* symbols = "0123456789abcdef";
static jmp_buf position;

enum
{
	SUCCESS_JUMP = 1,
	SIZE = 13,
	MAX_SYSTEM = 16,
	MIN_SYSTEM = 2
};

void PrintBadInput()
{
	printf("bad input");
	longjmp(position, SUCCESS_JUMP);
}

int CharToInt(int system, char sym)
{
	for (int i = 0; i < system; i++)
	{
		if (tolower(sym) == symbols[i])
		{
			return i;
		}
	}
	
	PrintBadInput();
    return -1;
}

double Pow(unsigned int number, int power)
{
	if (number == 0 || number == 1)
	{
		return number;
	}

	if (power == 0)
	{
		return 1;
	}
	else if (power < 0)
	{
		return (1.0 / number) * Pow(number, power + 1);
	}
	
    return number * Pow(number, power - 1);
}

int GetIntegerSize(const char* line)
{
	char* pointPosition = strchr(line, '.');
	int lineLength = strlen(line);

	if (pointPosition == NULL)
	{
		return lineLength;
	}
	else
	{
		int integerSize = pointPosition - line;

		if (integerSize == 0 || integerSize == lineLength - 1)
		{
			PrintBadInput();
		}
		
		return integerSize;
	}
}

double ConvertTo10(int system1, const char* line)
{
	int integerSize = GetIntegerSize(line);
	double sum = 0.0;

	for (int i = 0; i < integerSize; i++)
	{
		sum += CharToInt(system1, line[i]) * Pow(system1, integerSize - 1 - i);
	}

	int lineLength = strlen(line);

	for (int i = integerSize + 1; i < lineLength; i++)
	{
		sum += CharToInt(system1, line[i]) * Pow(system1, integerSize - i);
	}

	return sum;
}

char* ConvertFrom10(int system2, double sum)
{
	long long integer = (long long)sum;
	double fractional = sum - integer;
	int integerSize = 0;
	
	do
	{
		++integerSize;
	} while (integer >= Pow(system2, integerSize));

	int lineSize = integerSize + SIZE + 1;
	char* line = calloc(lineSize, sizeof(char));
	if (line == NULL)
	{
		PrintBadInput();
	}

	for (int i = integerSize - 1; i >= 0; i--)
	{
		line[i] = symbols[integer % system2];
		integer /= system2;
	}

	if (fractional > 0)
	{
		line[integerSize] = '.';
		for (int i = 0; i < SIZE - 1; i++)
		{
			fractional *= system2;
			line[integerSize + 1 + i] = symbols[(int)fractional];
			fractional -= (int)fractional;
		}
	}

	return line;
}

int main(void)
{
	int system1, system2;
	char line[SIZE + 1];

    if(setjmp(position) == 0)
	{
        if (scanf("%d %d", &system1, &system2) != 2 || system1 > MAX_SYSTEM || system2 > MAX_SYSTEM || system1 < MIN_SYSTEM || system2 < MIN_SYSTEM)
        {
            PrintBadInput();
        }

        if (scanf("%13s", line) != 1)
        {
            PrintBadInput();
        }

        double number10 = ConvertTo10(system1, line);
        char* newNumber = ConvertFrom10(system2, number10);
        printf("%s", newNumber);

        free(newNumber);
    }

	return EXIT_SUCCESS;
}
