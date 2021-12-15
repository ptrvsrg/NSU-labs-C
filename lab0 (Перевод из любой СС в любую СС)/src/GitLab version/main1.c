#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char* Symbols = "0123456789abcdef";

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

typedef struct TNumberPart
{
	int IntegerPart[100];
	int FractionalPart[100];
	int SizeIntegerPart;
	int SizeFractionalPart;
} TNumberPart;

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

void PrintBadInput()
{
	printf("bad input");
}

void PrintNumber(TNumberPart Number)
{
    for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		putc(Symbols[Number.IntegerPart[i]], stdout);
	}

	if (Number.SizeFractionalPart != 0)
	{
		putc('.', stdout);
		for (int i = 0; i < Number.SizeFractionalPart; i++)
		{
			putc(Symbols[Number.FractionalPart[i]], stdout);
		}
	}
}

int CharToInt(long long System, char Symbol, int* Number)
{
	for (int i = 0; i < System; i++)
	{
		if (tolower(Symbol) == Symbols[i])
		{
			*Number = i;
			return SUCCESS;
		}
	}
	return FAILURE;
}

int GetIntegerPartSize(const char* Line)
{
	char* PointPosition = strchr(Line, '.');

	if (PointPosition == NULL)
	{
		return strlen(Line);
	}
	else
	{
		return PointPosition - Line;
	}
}

int DivideIntoParts(int System1, const char* Line, TNumberPart* Number)
{
	Number->SizeIntegerPart = GetIntegerPartSize(Line);

	if (Number->SizeIntegerPart == 0)
	{
		return FAILURE;
	}

	for (int i = 0; i < Number->SizeIntegerPart; i++)
	{
		if (CharToInt(System1, Line[i], &(Number->IntegerPart[i])) == FAILURE)
		{
			return FAILURE;
		}
	}

	int SizeNumber = strlen(Line);
	Number->SizeFractionalPart = SizeNumber - Number->SizeIntegerPart - 1;

	if (Number->SizeFractionalPart == -1)
	{
		Number->SizeFractionalPart = 0;
	}
	else if (Number->SizeFractionalPart > 0)
	{
		for (int i = 0; i < Number->SizeFractionalPart; i++)
		{
			if (CharToInt(System1, Line[i + Number->SizeIntegerPart + 1], &(Number->FractionalPart[i])) == FAILURE)
			{
				return FAILURE;
			}
		}
	}
	else
	{
		return FAILURE;
	}

	return SUCCESS;
}

double To10(int System1, TNumberPart Number)
{
	double Sum = 0.0;

	for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		Sum += Number.IntegerPart[i] * Pow(System1, Number.SizeIntegerPart - 1 - i);
	}

	for (int i = 0; i < Number.SizeFractionalPart; i++)
	{
		Sum += Number.FractionalPart[i] * Pow(System1, -i - 1);
	}

	return Sum;
}

TNumberPart From10(int System2, double Sum, TNumberPart LastNumber)
{
	TNumberPart Number;
	double Fractional = Sum - (long long)Sum;
	Number.SizeFractionalPart = 0;

	if (LastNumber.SizeFractionalPart != 0)
	{
		Number.SizeFractionalPart = 12;

		for (int i = 0; i < 12; i++)
		{
			Fractional *= System2;
			Number.FractionalPart[i] = (int)Fractional;
			Fractional -= (int)Fractional;
		}
	}

	long long Integer = (long long)Sum;
	Number.SizeIntegerPart = 0;

	do
	{
		++Number.SizeIntegerPart;
	} while (Integer >= Pow(System2, Number.SizeIntegerPart));

	for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		Number.IntegerPart[Number.SizeIntegerPart - 1 - i] = Integer % System2;
		Integer /= System2;
	}

	return Number;
}

int main()
{
	TNumberPart Number;
	int System1, System2;
	char Line[14];

	if (scanf("%d %d", &System1, &System2) == EOF || System1 > 16 || System2 > 16 || System1 < 2 || System2 < 2)
	{
		PrintBadInput();
		return SUCCESS;
	}

	if (scanf("%13s", Line) == EOF)
	{
		PrintBadInput();
		return SUCCESS;
	}

	if (DivideIntoParts(System1, Line, &Number) == FAILURE)
	{
		PrintBadInput();
		return SUCCESS;
	}

	PrintNumber(From10(System2, To10(System1, Number), Number));

	return SUCCESS;
}
