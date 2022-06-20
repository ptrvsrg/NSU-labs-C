#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    SIZE_TEMPLATE = 16
};

int Pow(unsigned int number, int power)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    if (power <= 0)
    {
        return 1;
    }
    
    return number * Pow(number, power - 1);
}

typedef struct
{
    int BeginIndex;
    int Length;
    char String[SIZE_TEMPLATE + 1];
} TRingArray;

////////////////////////////////  INPUT / OUTPUT  ////////////////////////////////

bool InputTemplate(TRingArray* template)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; ++i)
    {
        if ((template->String[i] = getchar()) == EOF)
        {
            return false;
        }

        if (template->String[i] == '\n')
        {
            template->String[i] = '\0';
            template->BeginIndex = 0;
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

    text->BeginIndex = 0;
    text->Length = length;
    return true;
}

void PrintProtokol(TRingArray template, TRingArray text, int position)
{
    for (int i = 0; i < template.Length; i++)
    {
        printf("%d ", position + i);

        int index = (text.BeginIndex + i) % text.Length;
        if (template.String[i] != text.String[index])
        {
            return;
        }
    }
}

////////////////////////////////  TEXT SHIFT  ////////////////////////////////

bool ShiftText(TRingArray* text)
{    
    if ((text->String[text->BeginIndex] = getchar()) == EOF)
    {
        return false;
    }

    text->BeginIndex = (text->BeginIndex + 1) % text->Length;
    return true;
}

////////////////////////////////  HASH FUNCTION  ////////////////////////////////

int Hash(TRingArray array)
{
    int sum = 0;
    int power = 1;

    for (int i = 0; i < array.Length; ++i)
    {
        int index = (array.BeginIndex + i) % array.Length;
        sum += (unsigned char)array.String[index] % 3 * power;
        power *= 3;
    }

    return sum;
}

int ChangeHash(unsigned char symbol1, unsigned char symbol2, int powerOf3, int textHash)
{
    return ( textHash - symbol1 % 3 ) / 3 + ( symbol2 % 3 * powerOf3 );
}

////////////////////////////////  RABIN KARP ALGORITHM  ////////////////////////////////

void RabinKarpAlgorithm(TRingArray template)
{
    const int powerOf3 = Pow(3, template.Length - 1);
    const int templateHash = Hash(template);
    printf("%d ", templateHash);

    TRingArray text;
    if (!InputText(&text, template.Length))
    {
        return;
    }

    int textHash = Hash(text);
    int position = 1;
    
    while (true)
    {
        if (templateHash == textHash)
        {
            PrintProtokol(template, text, position);
        }

        unsigned char symbol = text.String[text.BeginIndex];

        if (!ShiftText(&text))
        {
            return;
        }

        int index = (text.BeginIndex + text.Length - 1) % text.Length;
        textHash = ChangeHash(symbol, text.String[index], powerOf3, textHash);

        ++position;
    }
}

////////////////////////////////  MAIN  ////////////////////////////////

int main(void)
{
    TRingArray template;
    if (!InputTemplate(&template))
    {
        return EXIT_FAILURE;
    }

    RabinKarpAlgorithm(template);

    return EXIT_SUCCESS;
}
