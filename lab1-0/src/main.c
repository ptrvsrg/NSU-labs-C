#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    SIZE_TEMPLATE = 16,
    COUNT_CHAR = 256
};

typedef struct
{
    int EndIndex;
    int Length;
    char String[SIZE_TEMPLATE + 1];
} TRingArray;

////////////////////////////////  INPUT  ////////////////////////////////

bool InputTemplate(TRingArray* template)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
    {
        if (fread(template->String + i, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }

        if (template->String[i] == '\n')
        {
            template->String[i] = '\0';
            template->EndIndex = i - 1;
            template->Length = i;

            return true;
        }
    }

    return false;
}

bool InputText(TRingArray* text, int length)
{
    if (fread(text->String, sizeof(char), length, stdin) != (size_t)length)
    {
        return false;
    }

    text->EndIndex = length - 1;
    text->Length = length;
    return true;
}

////////////////////////////////  BOYER MOORE ALGORITHM  ////////////////////////////////

void CreateShiftTable(TRingArray template, int shiftTable[])
{
    for (int i = 0; i < COUNT_CHAR; ++i)
    {
        shiftTable[i] = template.Length;
    }

    for (int i = 0; i < template.Length - 1; ++i)
    {
        unsigned char symbol = template.String[i];
        shiftTable[(int)symbol] = template.Length - 1 - i;
    }
}

bool ShiftText(TRingArray* text, int shift)
{
    for (int i = 0; i < shift; ++i)
    {
        int index = (text->EndIndex + i + 1) % text->Length;
        if (fread(text->String + index, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }
    }
        
    text->EndIndex = (text->EndIndex + shift) % text->Length;
    return true;
}

void BoyerMooreAlgorithm(TRingArray template)
{
    int shiftTable[COUNT_CHAR] = { 0 };
    CreateShiftTable(template, shiftTable);

    TRingArray text;
    if (!InputText(&text, template.Length))
    {
        return;
    }

    int position = template.Length;
    int index = 0;
        
    while (true)
    {
        printf("%d ", position);
        int indexText = (text.EndIndex + text.Length - index) % text.Length;
        int indexTemplate = template.EndIndex - index;

        if (template.String[indexTemplate] != text.String[indexText])
        {
            unsigned char symbol = text.String[(index == 0) ? indexText : text.EndIndex];
            position += shiftTable[(int)symbol] + index;

            if (!ShiftText(&text, shiftTable[(int)symbol]))
            {
                return;
            }

            index = 0;
            continue;
        }

        if (index == text.Length - 1)
        {
            position += text.Length + index;

            if (!ShiftText(&text, text.Length))
            {
                return;
            }

            index = 0;
            continue;
        }

        --position;
        ++index;
    }

}

////////////////////////////////  MAIN  ////////////////////////////////

int main(void)
{
    TRingArray template;
    if (!InputTemplate(&template))
    {
        return EXIT_SUCCESS;
    }

    BoyerMooreAlgorithm(template);

    return EXIT_SUCCESS;
}
