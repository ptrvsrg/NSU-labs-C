#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

static const char* Symbols1 = "0123456789abcdef", * Symbols2 = "0123456789ABCDEF";

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	INTEGER = 2,
	FRACTIONAL = 3
};

typedef struct TNumber
{
	int IntegerPart[100];
	int FractionalPart[100];
	int SizeIntegerPart;
	int SizeFractionalPart;
} TNumber;

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

void PrintBadInput(FILE* OutputFile)
{
	fprintf(OutputFile, "bad input");
}

int CharToInt(long long System, char Symbol, int* Number)//Перевод символов в число
{
	for (int i = 0; i < System; i++)
	{
		if (Symbol == Symbols1[i] || Symbol == Symbols2[i])
		{
			*Number = i;
			return SUCCESS;
		}
	}
	return FAILURE;
}

double To10(long long System1, TNumber Number)//Перевод в 10-ричную СС
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

TNumber From10(long long System2, double Sum, TNumber LastNumber)//Перевод из 10-ричной СС
{
	TNumber Number;
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
	FILE* InputFile = fopen("in.txt", "r");
	FILE* OutputFile = fopen("out.txt", "w");
	int System1, System2;

	if (fscanf(InputFile, "%d %d", &System1, &System2) == EOF || System1 > 16 || System2 > 16 || System1 < 2 || System2 < 2)
	{
		fclose(InputFile);
		PrintBadInput(OutputFile);
		fclose(OutputFile);
		return SUCCESS;
	}

	TNumber Number;
	Number.SizeFractionalPart = 0;
	Number.SizeIntegerPart = 0;
	int PointPosition;
	int NumberPart = INTEGER;
	int Index = 0;
	char Symbol = fgetc(InputFile);

	while(!feof(InputFile))
	{
		if ((Symbol = fgetc(InputFile)) == EOF)
		{
			break;
		}

		if ((Index == 13 && NumberPart == INTEGER) || (Index == 14 && NumberPart == FRACTIONAL))
		{
			fclose(InputFile);
			PrintBadInput(OutputFile);
			fclose(OutputFile);
			return SUCCESS;
		}
		else if (Symbol == '\n')
		{
			if (NumberPart == FRACTIONAL && Number.SizeFractionalPart == 0 || Index == 0)
			{
				fclose(InputFile);
				PrintBadInput(OutputFile);
				fclose(OutputFile);
				return SUCCESS;
			}
			
			break;
		}
		else if (Symbol == '.')
		{
			if (Index == 0 || NumberPart == FRACTIONAL)
			{
				fclose(InputFile);
				PrintBadInput(OutputFile);
				fclose(OutputFile);
				return SUCCESS;
			}

			PointPosition = Index + 1;
			NumberPart = FRACTIONAL;
			Index++;
		}
		else
		{
			if (NumberPart == INTEGER)
			{
				if (CharToInt(System1, Symbol, &(Number.IntegerPart[Index])) == FAILURE)
				{
					fclose(InputFile);
					PrintBadInput(OutputFile);
					fclose(OutputFile);
					return SUCCESS;
				}

				Number.SizeIntegerPart++;
				Index++;
			}
			else
			{
				if (CharToInt(System1, Symbol, &(Number.FractionalPart[Index - PointPosition])) == FAILURE)
				{
					fclose(InputFile);
					PrintBadInput(OutputFile);
					fclose(OutputFile);
					return SUCCESS;
				}

				Number.SizeFractionalPart++;
				Index++;
			}
		}
	}

	Number = From10(System2, To10(System1, Number), Number);

	for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		fprintf(OutputFile, "%c", Symbols1[Number.IntegerPart[i]]);
	}

	if (Number.SizeFractionalPart != 0)
	{
		fprintf(OutputFile, ".");
		for (int i = 0; i < Number.SizeFractionalPart; i++)
		{
			fprintf(OutputFile, "%c", Symbols1[Number.FractionalPart[i]]);
		}
	}

	fclose(InputFile);
	fclose(OutputFile);
	return SUCCESS;
}
