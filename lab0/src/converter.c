#include "converter.h"

static const char* allSymbols = "0123456789abcdef";

static int CharToInt(int systemBase, char symbol)
{
	for (int i = 0; i < systemBase; ++i)
	{
		if (tolower(symbol) == allSymbols[i])
		{
			return i;
		}
	}
	
	BadInputError();
    return -1;
}

static double Pow(unsigned int number, int power)
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

static int GetIntegerSize(const char* number)
{
	char* pointPosition = strchr(number, '.');
	int numberLength = (int)strlen(number);

	if (pointPosition == NULL)
	{
		return numberLength;
	}
    
    int integerSize = (int)(pointPosition - number);

    if (integerSize == 0 || integerSize == numberLength - 1)
    {
        BadInputError();
    }
    
    return integerSize;
}

static double ConvertTo10(int systemBase1, const char* number)
{
	int integerSize = GetIntegerSize(number);
	double sum = 0.0;

	for (int i = 0; i < integerSize; ++i)
	{
		sum += CharToInt(systemBase1, number[i]) * Pow(systemBase1, integerSize - 1 - i);
	}

	int numberLength = (int)strlen(number);

	for (int i = integerSize + 1; i < numberLength; ++i)
	{
		sum += CharToInt(systemBase1, number[i]) * Pow(systemBase1, integerSize - i);
	}

	return sum;
}

static char* ConvertFrom10(int systemBase2, double number, int digitAfterPoint)
{
	long long integer = (long long)number;
	double fractional = number - integer;
	int integerSize = 0;
	
	do
	{
		++integerSize;
	} while (integer >= Pow(systemBase2, integerSize));

	int lineSize = integerSize + digitAfterPoint + 1;
	char* newNumber = calloc(lineSize, sizeof(char));
	if (newNumber == NULL)
	{
		OtherError(__FILE__, __LINE__);
	}

	for (int i = integerSize - 1; i >= 0; i--)
	{
		newNumber[i] = allSymbols[integer % systemBase2];
		integer /= systemBase2;
	}

	if (fractional > 0)
	{
		newNumber[integerSize] = '.';
		for (int i = 0; i < digitAfterPoint - 1; i++)
		{
			fractional *= systemBase2;
			newNumber[integerSize + 1 + i] = allSymbols[(int)fractional];
			fractional -= (int)fractional;
		}
	}

	return newNumber;
}

char* ConvertNumber(int systemBase1, int systemBase2, const char* number, int digitAfterPoint)
{
    double number10 = ConvertTo10(systemBase1, number);
    char* newNumber = ConvertFrom10(systemBase2, number10, digitAfterPoint);
    return newNumber;
}
