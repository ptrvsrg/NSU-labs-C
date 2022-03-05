#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

enum
{
	SIZE_TEMPLATE = 16,
    SIZE_TEXT = 2 * SIZE_TEMPLATE,
	SIZE_CHAR = 256
};

void PrintNumber(int number)
{
	printf("%u ", number);
}

void InputTemplate(uchar* template)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
	{
		int control = scanf("%c", &template[i]);
		assert(control == 1);

		if (template[i] == '\n')
		{
			template[i] = '\0';
			return;
		}
	}

	assert(false);
}

void CreateShiftTable(const uchar* template, int shiftTable[])
{
	const int templateLength = strlen(template);

	for (int i = 0; i < SIZE_CHAR; ++i)
	{
		shiftTable[i] = templateLength;
	}

	for (int i = 1; i < templateLength; ++i)
	{
        int index = template[templateLength - 1 - i];

		if (shiftTable[index] == templateLength)
		{
			shiftTable[index] = i;
		}
	}
}

void StrCpy(uchar* strDest, const uchar* strSrc)
{
    assert(strDest != NULL && strSrc != NULL);
    uchar *temp = strDest;

    while(*strDest)
    {
        *strDest = *strSrc;
        ++strDest;
        ++strSrc;
    }
}

void ShiftText(uchar* text)
{
    StrCpy(text, text + SIZE_TEMPLATE);
    int control = fread(text + SIZE_TEMPLATE, sizeof(uchar), SIZE_TEMPLATE, stdin);
    assert(control != EOF);
}

void BoyerMooreAlgorithm(const uchar* template)
{
	const int templateLength = strlen(template);
    int currentPosition = templateLength;
    int comparisonPosition = templateLength;
    int lastLength = 0;
    
	int shiftTable[SIZE_CHAR];
	CreateShiftTable(template, shiftTable);

    uchar text[SIZE_TEXT + 1] = {0};
    int control = fread(text, sizeof(uchar), SIZE_TEXT, stdin);
    assert(control != EOF);

    while (true)
	{
        if (comparisonPosition > lastLength + strlen(text))
        {
            lastLength += SIZE_TEMPLATE;
            ShiftText(text);

            if (strlen(text) <= SIZE_TEMPLATE)
            {
                return;
            }
        }

		for (int i = 0; i < templateLength; ++i)
		{
			PrintNumber(currentPosition);

			if (text[comparisonPosition - lastLength - 1 - i] != template[templateLength - 1 - i] || i == templateLength - 1)
			{				
				comparisonPosition += shiftTable[text[comparisonPosition - lastLength - 1]];
				currentPosition = comparisonPosition;
				break;
			}
			
            --currentPosition;
		}
	}

}

int main()
{
	char template[SIZE_TEMPLATE + 1];

	InputTemplate(template);
	BoyerMooreAlgorithm(template);

	return EXIT_SUCCESS;
}
