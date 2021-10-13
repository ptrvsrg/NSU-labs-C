#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

const char* Symbols1 = "0123456789abcdef", * Symbols2 = "0123456789ABCDEF";

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

void PrintBadInput()
{
	printf("bad input");
}

int CharToInt(long long System, char Symbol, int* Number)//������� �������� � �����
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

int GetSizeOfIntegerPart(char* Line)//��������� ������� ����� ����� �����
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

int DivideIntoParts(long long System1, char* Line, TNumberPart* Number)//���������� ����� �� ����� � ������� �����
{
	Number->SizeIntegerPart = GetSizeOfIntegerPart(Line);

	if (Number->SizeIntegerPart == 0)
	{
		return FAILURE;
	}

	for (int i = 0; i < Number->SizeIntegerPart; i++)
	{
		//�������� ����� �� ������������ (��� �� ������� ����������� System1-������ ��)
		if (CharToInt(System1, Line[i], &(Number->IntegerPart[i])) == FAILURE)
		{
			return FAILURE;
		}
	}

	int SizeNumber = strlen(Line);
	Number->SizeFractionalPart = SizeNumber - Number->SizeIntegerPart - 1;

	//Number->SizeFractionalPart == 0 ��� ����� ���� "111."
	//Number->SizeFractionalPart == -1 ��� ����� ���� "111"
	if (Number->SizeFractionalPart == -1)
	{
		Number->SizeFractionalPart = 0;
	}
	else if (Number->SizeFractionalPart > 0)
	{
		for (int i = 0; i < Number->SizeFractionalPart; i++)
		{
			// �������� ����� �� ������������(��� �� ������� ����������� System1 - ������ ��)
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

double To10(long long System1, TNumberPart Number)//������� � 10-������ ��
{
	double Sum = 0.0;

	for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		Sum += Number.IntegerPart[i] * pow(System1, Number.SizeIntegerPart - 1 - i);
	}

	for (int i = 0; i < Number.SizeFractionalPart; i++)
	{
		Sum += Number.FractionalPart[i] * pow(System1, -i - 1);
	}

	return Sum;
}

TNumberPart From10(long long System2, double Sum, TNumberPart LastNumber)//������� �� 10-������ ��
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
	} while (Integer >= pow(System2, Number.SizeIntegerPart));

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

	if (scanf("%d %d", &System1, &System2) == EOF)
	{
		PrintBadInput();
		return SUCCESS;
	}

	if (scanf("%13s", Line) == EOF)
	{
		PrintBadInput();
		return SUCCESS;
	}

	if (System1 > 16 || System2 > 16 || System1 < 2 || System2 < 2)
	{
		PrintBadInput();
		return SUCCESS;
	}

	if (DivideIntoParts(System1, Line, &Number) == FAILURE)
	{
		PrintBadInput();
		return SUCCESS;
	}

	Number = From10(System2, To10(System1, Number), Number);

	for (int i = 0; i < Number.SizeIntegerPart; i++)
	{
		printf("%c", Symbols1[Number.IntegerPart[i]]);
	}

	if (Number.SizeFractionalPart != 0)
	{
		printf(".");
		for (int i = 0; i < Number.SizeFractionalPart; i++)
		{
			printf("%c", Symbols1[Number.FractionalPart[i]]);
		}
	}


	return SUCCESS;
}
