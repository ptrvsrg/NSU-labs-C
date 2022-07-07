#define _CRT_SECURE_NO_WARNINGS
#include "in_out.h"
#define	MAX_SYSTEM (int)16
#define MIN_SYSTEM (int)2

void InputSystemBase(int* systemBase)
{
    if (scanf("%d", systemBase) != 1)
    {
        OtherError(__FILE__, __LINE__);
    }

    if (*systemBase < MIN_SYSTEM || *systemBase > MAX_SYSTEM)
    {
        BadInputError();
    }
}

void InputNumber(int count, char* number)
{
    if (scanf("%s", number) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }

    number[count] = '\0';
}

void OutputNumber(const char* number)
{
    printf("%s\n", number);
}
