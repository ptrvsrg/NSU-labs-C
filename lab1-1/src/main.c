#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    SIZE_TEMPLATE = 16
};

int Pow(unsigned int number, int power)
{
    if (power < 0)
    {
        return -1;
    }
    else if (power == 0)
    {
        return 1;
    }
    else if (number == 0 || number == 1)
    {
        return number;
    }
    
    return number * Pow(number, power - 1);
}

////////////////////////////////  HASH FUNCTION  ////////////////////////////////

int Hash(const char* string)
{
    int sum = 0;
    int power = 1;
    int stringLength = strlen(string);

    for (int i = 0; i < stringLength; i++)
    {
        sum += (unsigned char)string[i] % 3 * power;
        power *= 3;
    }

    return sum;
}

void ChangeHash(unsigned char symbol1, unsigned char symbol2, int powerOf3, int* textHash)
{
    *textHash -= (unsigned char)symbol1 % 3;
    *textHash /= 3;
    *textHash += (unsigned char)symbol2 % 3 * powerOf3;
}

////////////////////////////////  INPUT / OUTPUT  ////////////////////////////////

void PrintNumber(int number)
{
    printf("%d ", number);
}

bool InputTemplate(char* template)
{
    for (int i = 0; i < SIZE_TEMPLATE + 1; i++)
    {
        if (scanf("%c", template + i) == EOF)
        {
            return false;
        }

        if (template[i] == '\n')
        {
            if (i == 0)
            {
                return false;
            }
            else
            {
                template[i] = '\0';
                break;
            }
        }
    }

    return true;
}

////////////////////////////////  STRING FUNCTION  ////////////////////////////////

bool ShiftText(int templateLength, char* text)
{
    for (int i = 0; i < templateLength - 1; ++i)
    {
        text[i] = text[i + 1];
    }
    
    if ((text[templateLength - 1] = (char)fgetc(stdin)) == EOF)
    {
        return false;
    }

    return true;
}

void CompareString(const char* string1, const char* string2, int length, int position)
{
    for (int i = 0; i < length; i++)
    {
        PrintNumber(position + i);

        if (string1[i] != string2[i])
        {
            break;
        }
    }
}

////////////////////////////////  RABIN KARP ALGORITHM  ////////////////////////////////

void RabinKarpAlgorithm(const char* template)
{
    const int templateLength = strlen(template);
    const int powerOf3 = Pow(3, templateLength - 1);
    const int templateHash = Hash(template);
    int position = 1;
    PrintNumber(templateHash);

    char text[SIZE_TEMPLATE + 1] = { 0 };
    memset(text, 0, SIZE_TEMPLATE + 1);

    if (fread(text, sizeof(char), templateLength, stdin) != (size_t)templateLength)
    {
        return;
    }

    int textHash = Hash(text);

    while (true)
    {
        if (templateHash == textHash)
        {
            CompareString(template, text, templateLength, position);
        }

        unsigned char symbol = text[0];

        if (!ShiftText(templateLength, text))
        {
            return;
        }

        ChangeHash(symbol, text[templateLength - 1], powerOf3, &textHash);

        ++position; 
    }
}

////////////////////////////////  MAIN  ////////////////////////////////

int main(void)
{
    char template[SIZE_TEMPLATE + 1] = { 0 };

    if (freopen("in.txt", "r", stdin) == NULL)
    {
        return EXIT_FAILURE;
    }

    if (freopen("out.txt", "w", stdout) == NULL)
    {
        return EXIT_FAILURE;
    }

    if (!InputTemplate(template))
    {
        return EXIT_FAILURE;
    }

    RabinKarpAlgorithm(template);

    fclose(stdin);
    fclose(stdout);

    return EXIT_SUCCESS;
}
