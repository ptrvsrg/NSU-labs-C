#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNUSED(x) (void)(x);

enum
{
    SIZE_TEMPLATE = 16,
    SIZE_TEXT = 2 * SIZE_TEMPLATE,
    SIZE_CHAR = 256
};

void PrintNumber(int number)
{
    printf("%d ", number);
}

void InputTemplate(int* templateLength, char template[])
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
    {
        int control = fread(template + i, sizeof(char), 1, stdin);
        UNUSED(control);
        assert(control != EOF);

        if (template[i] == '\n')
        {
            template[i] = '\0';
            *templateLength = i;
            return;
        }
    }

    assert(false);
}

void CreateShiftTable(int templateLength, const char template[], int shiftTable[])
{
    for (int i = 0; i < SIZE_CHAR; ++i)
    {
        shiftTable[i] = templateLength;
    }

    for (int i = 0; i < templateLength - 1; ++i)
    {
        int index = template[i];
        shiftTable[index] = templateLength - 1 - i;
    }
}

int ShiftText(char text[])
{
    for (int i = 0; i < SIZE_TEMPLATE; ++i)
    {
        text[i] = text[i + SIZE_TEMPLATE];
    }
        
    int control = fread(text + SIZE_TEMPLATE, sizeof(char), SIZE_TEMPLATE, stdin);
    UNUSED(control);
    assert(control != EOF);

    return control;
}

void BoyerMooreAlgorithm(int templateLength, const char template[])
{
    int currentPosition = templateLength;
    int comparisonPosition = templateLength;
    int lastLength = 0;
        
    int shiftTable[SIZE_CHAR] = { 0 };
    CreateShiftTable(templateLength, template, shiftTable);

    char text[SIZE_TEXT + 1] = { 0 };
    int control = fread(text, sizeof(char), SIZE_TEXT, stdin);
    UNUSED(control);
    assert(control != EOF);
    int textLength = control;

    while (true)
    {
        if ((unsigned int)comparisonPosition > (unsigned int)lastLength + textLength)
        {
            if (ShiftText(text) == 0)
            {
                return;
            }

            lastLength += SIZE_TEMPLATE;
            textLength = SIZE_TEXT;
        }

        for (int i = 0; i < templateLength; ++i)
        {
            PrintNumber(currentPosition);

            if (text[comparisonPosition - lastLength - 1 - i] != template[templateLength - 1 - i] || i == templateLength - 1)
            {               
                comparisonPosition += shiftTable[(unsigned char)text[comparisonPosition - lastLength - 1]];
                currentPosition = comparisonPosition;
                break;
            }
            
            --currentPosition;
        }
    }

}

int main(void)
{
    char template[SIZE_TEMPLATE + 1] = { 0 };
    int templateLength = 0;

    InputTemplate(&templateLength, template);
    BoyerMooreAlgorithm(templateLength, template);

    return EXIT_SUCCESS;
}
