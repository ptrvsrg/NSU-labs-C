#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum
{
	SUCCESS = 0,
	FAILURE = -1,
	SIZE_TEMPLATE = 16,
	SIZE_CHAR = 256
};

void PrintNumber(size_t Number)
{
	printf("%u ", Number);
}

void GetShiftTable(const char* Template, size_t ShiftTable[])
{
	const size_t LengthOfTemplate = strlen(Template);

	for (size_t i = 0; i < SIZE_CHAR; ++i)
	{
		ShiftTable[i] = LengthOfTemplate;
	}

	for (size_t i = 1; i < LengthOfTemplate; ++i)
	{
		if (ShiftTable[(unsigned char)Template[LengthOfTemplate - 1 - i]] == LengthOfTemplate)
		{
			ShiftTable[(unsigned char)Template[LengthOfTemplate - 1 - i]] = i;
		}
	} 
}

void FindForTemplateInText(const char* Template, FILE* InputFile)
{
	const size_t LengthOfTemplate = strlen(Template);
	size_t CurrentPosition = LengthOfTemplate;
	size_t ComparisonPosition = LengthOfTemplate;
	size_t ShiftTable[SIZE_CHAR]; 
	GetShiftTable(Template, ShiftTable);

	char Text[SIZE_TEMPLATE + 1];
	char Buffer[SIZE_TEMPLATE + 1];
	size_t LengthOfText = 0;
	size_t LastLengthOfText = 0;

	while (1)
	{
		if (CurrentPosition > LengthOfText)
		{
			strcpy(Buffer, Text);
			memset(Text, 0, SIZE_TEMPLATE + 1);

			if (fread(Text, 1, SIZE_TEMPLATE, InputFile) == 0)
			{
				break;
			}

			LastLengthOfText = LengthOfText;
			LengthOfText += strlen(Text);
		}

		for (size_t i = 0; i < LengthOfTemplate; ++i)
		{
			PrintNumber(CurrentPosition);
			char Symbol;

			if (ComparisonPosition - 1 - i - LastLengthOfText < 0)
			{
				Symbol = Buffer[SIZE_TEMPLATE + ComparisonPosition - 1 - i - LengthOfText];
			}
			else
			{
				Symbol = Text[ComparisonPosition - 1 - i - LastLengthOfText];
			}

			if (Symbol != Template[LengthOfTemplate - 1 - i] || i == LengthOfTemplate - 1)
			{
				ComparisonPosition += ShiftTable[(unsigned char)Text[ComparisonPosition - 1 - LastLengthOfText]];
				CurrentPosition = ComparisonPosition;
				break;
			}
			else
			{
				CurrentPosition--;
			}
		}
	}
}

int main()
{
	char Template[SIZE_TEMPLATE + 1];
	memset(Template, 0, SIZE_TEMPLATE + 1);
	FILE* InputFile = fopen("in.txt", "r");

	for (size_t i = 0; i < SIZE_TEMPLATE + 1; ++i)
	{
		if (fscanf(InputFile, "%c", &Template[i]) != 1)
		{
			fclose(InputFile);
			return SUCCESS;
		}

		if (Template[i] == '\n')
		{
			if (i == 0)
			{
				fclose(InputFile);
				return SUCCESS;
			}
			else
			{
				Template[i] = '\0';
				break;
			}
		}
	}

	FindForTemplateInText(Template, InputFile);
	fclose(InputFile);

	return SUCCESS;
}
