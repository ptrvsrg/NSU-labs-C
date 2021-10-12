#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	SIZE_TEMPLATE = 16,
    SIZE_TEXT = 2 * SIZE_TEMPLATE,
	SIZE_CHAR = 256
};

void PrintNumber(int Number)
{
	printf("%d ", Number);
}

void InputTemplate(char* Template, FILE* InputFile)
{
	memset(Template, 0, SIZE_TEMPLATE + 1);

    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
	{
		if (fscanf(InputFile, "%c", &Template[i]) == EOF)
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

void GetShiftTable(const char* Template, int ShiftTable[])
{
	const int TemplateLength = strlen(Template);

	for (int i = 0; i < SIZE_CHAR; i++)
	{
		ShiftTable[i] = TemplateLength;
	}

	for (int i = 1; i < TemplateLength; i++)
	{
		if (ShiftTable[(unsigned char)Template[TemplateLength - 1 - i]] == TemplateLength)
		{
			ShiftTable[(unsigned char)Template[TemplateLength - 1 - i]] = i;
		}
	}
}

void FindForTemplateInText(const char* Template, FILE* InputFile)
{
	size_t TemplateLength = strlen(Template);
    size_t CurrentPosition = TemplateLength;
    size_t ComparisonPosition = TemplateLength;
    size_t LastLength = 0;

    int ShiftTable[SIZE_CHAR];
    GetShiftTable(Template, ShiftTable);

    char Text[SIZE_TEXT + 1];
	memset(Text, 0, SIZE_TEXT + 1);
    assert(fread(Text, 1, SIZE_TEXT, InputFile) != EOF);

    while (1)
	{
        if(ComparisonPosition > LastLength + strlen(Text))
        {
            LastLength += SIZE_TEMPLATE;
            memmove(Text, Text + SIZE_TEMPLATE, SIZE_TEMPLATE);
            fread(Text + SIZE_TEMPLATE, 1, SIZE_TEMPLATE, InputFile);

            if(strlen(Text) <= SIZE_TEMPLATE)
            {
                break;
            }
        }

		for (int i = 0; i < TemplateLength; ++i)
		{
			PrintNumber(CurrentPosition);

			if (Text[ComparisonPosition - LastLength - 1 - i] != Template[TemplateLength - 1 - i] || i == TemplateLength - 1)
			{				
				ComparisonPosition += ShiftTable[(unsigned char)Text[ComparisonPosition - LastLength - 1]];
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
	FILE* InputFile = fopen("in.txt", "r");

	InputTemplate(Template, InputFile);

	FindForTemplateInText(Template, InputFile);
	fclose(InputFile);

	return SUCCESS;
}
