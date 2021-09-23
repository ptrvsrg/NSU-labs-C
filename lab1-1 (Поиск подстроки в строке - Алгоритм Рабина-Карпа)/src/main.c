#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	SIZE_TEMPLATE = 16
};

void PrintNumber(int Number)
{
	printf("%d ", Number);
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

void RabinKarpAlgorithm(const char* Template, FILE* InputFile)
{
	const int TemplateLength = strlen(Template);
	const int TemplateHash = HashFunction(Template);
	PrintNumber(TemplateHash);
	char Text[SIZE_TEMPLATE + 1];
	int Position = 1;
	memset(Text, 0, SIZE_TEMPLATE + 1);
	const int PowerOf3 = (int)pow(3, TemplateLength - 1);

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

		TextHash -= (unsigned char)Text[0] % 3;
		TextHash /= 3;

		memmove(Text, Text + 1, TemplateLength);

		Text[TemplateLength - 1] = (char)fgetc(InputFile);

		TextHash += (unsigned char)Text[TemplateLength - 1] % 3 * PowerOf3;

		++Position;	
	}
}

int main(void)
{
	char Template[SIZE_TEMPLATE + 1];
	memset(Template, 0, SIZE_TEMPLATE + 1);
	FILE* InputFile = fopen("in.txt", "r");

	for (int i = 0; i < SIZE_TEMPLATE + 1; i++)
	{
		if ((Template[i] = (char)fgetc(InputFile)) == EOF)
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

	RabinKarpAlgorithm(Template, InputFile);
	fclose(InputFile);

	return SUCCESS;
}
