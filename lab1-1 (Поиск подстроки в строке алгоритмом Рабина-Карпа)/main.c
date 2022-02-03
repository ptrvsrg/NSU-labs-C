#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum
{
	SUCCESS = 0,
	SIZE_TEMPLATE = 16
};

void PrintNumber(int Number)
{
	printf("%d ", Number);
}

void InputTemplate(char* Template, FILE* InputFile)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; i++)
	{
		if ((Template[i] = (char)fgetc(InputFile)) == EOF)
		{
			fclose(InputFile);
			assert(false);
		}

		if (Template[i] == '\n')
		{
			if (i == 0)
			{
				fclose(InputFile);
				assert(false);
			}
			else
			{
				Template[i] = '\0';
				break;
			}
		}
	}
}

int Pow(unsigned int Number, int Power)
{
    assert(Power >= 0);

	if (Number == 0 || Number == 1)
	{
		return Number;
	}

	if (Power == 0)
	{
		return 1;
	}
	else
	{
		return Number * Pow(Number, Power - 1);
	}
}

int HashFunction(const char* Line)
{
	int Sum = 0;
	int Power = 1;
	int LineLength = strlen(Line);

	for (int i = 0; i < LineLength; i++)
	{
		Sum += (unsigned char)Line[i] % 3 * Power;
		Power *= 3;
	}

	return Sum;
}

void ShiftText(int TemplateLength, char* Text, FILE* InputFile)
{
    memmove(Text, Text + 1, TemplateLength);
	Text[TemplateLength - 1] = (char)fgetc(InputFile);
}

void ChangeHash(unsigned char Symbol1, unsigned char Symbol2, int PowerOf3, int* TextHash)
{
    *TextHash -= (unsigned char)Symbol1 % 3;
    *TextHash /= 3;
    *TextHash += (unsigned char)Symbol2 % 3 * PowerOf3;
}

void RabinKarpAlgorithm(const char* Template, FILE* InputFile)
{
	const int TemplateLength = strlen(Template);
	const int TemplateHash = HashFunction(Template);
	PrintNumber(TemplateHash);

	char Text[SIZE_TEMPLATE + 1];
	int Position = 1;
	memset(Text, 0, SIZE_TEMPLATE + 1);
	const int PowerOf3 = Pow(3, TemplateLength - 1);

	if (fread(Text, 1, TemplateLength, InputFile) != (size_t)TemplateLength)
	{
		return;
	}

	int TextHash = HashFunction(Text);

	while (!feof(InputFile))
	{
		if (TemplateHash == TextHash)
		{
			for (int i = 0; i < TemplateLength; i++)
			{
				PrintNumber(Position + i);

				if (Template[i] != Text[i])
				{
					break;
				}
			}
		}

		unsigned char Symbol = Text[0];

		ShiftText(TemplateLength, Text, InputFile);
		ChangeHash(Symbol, Text[TemplateLength - 1], PowerOf3, &TextHash);

		++Position;	
	}
}

int main(void)
{
	char Template[SIZE_TEMPLATE + 1];
	memset(Template, 0, SIZE_TEMPLATE + 1);
	FILE* InputFile = fopen("in.txt", "r");

	InputTemplate(Template, InputFile);

	RabinKarpAlgorithm(Template, InputFile);
	fclose(InputFile);

	return SUCCESS;
}
