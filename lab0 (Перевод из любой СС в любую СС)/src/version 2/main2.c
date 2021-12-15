#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS_JUMP 1

const char* Symbols = "0123456789abcdef";
static jmp_buf position;

void PrintBadInput()
{
	printf("bad input");
	longjmp(position, SUCCESS_JUMP);
}

int CharToInt(int System, char Symbol)
{
	for (int i = 0; i < System; i++)
	{
		if (tolower(Symbol) == Symbols[i])
		{
			return i;
		}
	}
	
	PrintBadInput();
}

double Pow(unsigned int Number, int Power)
{
	if (Number == 0 || Number == 1)
	{
		return Number;
	}

	if (Power == 0)
	{
		return 1;
	}
	else if (Power < 0)
	{
		return (1.0 / Number) * Pow(Number, Power + 1);
	}
	else
	{
		return Number * Pow(Number, Power - 1);
	}
}

int GetIntegerPartSize(const char* Line)
{
	char* PointPosition = strchr(Line, '.');
	int LineLength = strlen(Line);

	if (PointPosition == NULL)
	{
		return LineLength;
	}
	else
	{
		int IntegerPartSize = PointPosition - Line;

		if (IntegerPartSize == 0 || IntegerPartSize == LineLength - 1)
		{
			PrintBadInput();
		}
		
		return IntegerPartSize;
	}
}

double To10(int System1, const char* Line)
{
	int IntegerPartSize = GetIntegerPartSize(Line);
	double Sum = 0.0;

	for (int i = 0; i < IntegerPartSize; i++)
	{
		Sum += CharToInt(System1, Line[i]) * Pow(System1, IntegerPartSize - 1 - i);
	}

	int LineLength = strlen(Line);

	for (int i = IntegerPartSize + 1; i < LineLength; i++)
	{
		Sum += CharToInt(System1, Line[i]) * Pow(System1, IntegerPartSize - i);
	}

	return Sum;
}

char* From10(int System2, double Sum)
{
	long long Integer = (long long)Sum;
	int IntegerSize = 0;
	
	do
	{
		++IntegerSize;
	} while (Integer >= Pow(System2, IntegerSize));

	char* Line;

	if ((Line = malloc(sizeof(char) * (IntegerSize + 14))) == NULL)
	{
		PrintBadInput();
	}

	memset(Line, 0, IntegerSize + 14);

	for (int i = IntegerSize - 1; i >= 0; i--)
	{
		Line[i] = Symbols[Integer % System2];
		Integer /= System2;
	}

	double Fractional = Sum - Integer;

	if (Fractional > 0)
	{
		Line[IntegerSize] = '.';
		for (int i = 0; i < 12; i++)
		{
			Fractional *= System2;
			Line[IntegerSize + 1 + i] = Symbols[(int)Fractional];
			Fractional -= (int)Fractional;
		}
	}


	return Line;
}

int main()
{
	int System1, System2;
	char Line[14];

    if(setjmp(position) == 0)
	{
        if (scanf("%d %d", &System1, &System2) == EOF || System1 > 16 || System2 > 16 || System1 < 2 || System2 < 2)
        {
            PrintBadInput();
        }

        if (scanf("%13s", Line) == EOF)
        {
            PrintBadInput();
        }

        printf("%s", From10(System2, To10(System1, Line)));
    }

	return EXIT_SUCCESS;
}
