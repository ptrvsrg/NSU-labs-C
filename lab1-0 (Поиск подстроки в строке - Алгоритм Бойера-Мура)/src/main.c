#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void InputTemplate(char* template)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
    {
        int control = scanf("%c", &template[i]);
        UNUSED(control);
        assert(control == 1);

        if (template[i] == '\n')
        {
            template[i] = '\0';
            return;
        }
    }

    assert(false);
}

void CreateShiftTable(const char* template, int shiftTable[])
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

int ShiftText(char* text)
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

void BoyerMooreAlgorithm(const char* template)
{
    const int templateLength = strlen(template);
    int currentPosition = templateLength;
    int comparisonPosition = templateLength;
    int lastLength = 0;
        
    int shiftTable[SIZE_CHAR] = { 0 };
    CreateShiftTable(template, shiftTable);

    char text[SIZE_TEXT + 1] = { 0 };
    int control = fread(text, sizeof(char), SIZE_TEXT, stdin);
    UNUSED(control);
    assert(control != EOF);
    int textLength = strlen(text);

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

    InputTemplate(template);
    BoyerMooreAlgorithm(template);

    return EXIT_SUCCESS;
}
