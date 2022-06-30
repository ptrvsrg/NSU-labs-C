#define _CRT_SECURE_NO_WARNINGS
#include "circular_list.h"

TCircularList CreateCircularList(int max)
{
    TCircularList circularList = { 0, 0, max, NULL };

    if (max > 0)
    {
        circularList.Array = calloc(max, sizeof(char));
        if (circularList.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }
    
    return circularList;
}

void InputTemplate(int count, TCircularList* circularList)
{
    if (count > circularList->Max)
    {
        OtherError(__FILE__, __LINE__);
    }

    for (int i = 0; i < count + 1; ++i)
    {    
        char symbol = 0;
        if (fread(&symbol, sizeof(char), 1, stdin) != 1)
        {
            OtherError(__FILE__, __LINE__);
        }

        if (symbol == '\n')
        {
            circularList->BeginIndex = 0;
            circularList->Count = i;
            return;
        }

        circularList->Array[i] = symbol;
    }
    
    OtherError(__FILE__, __LINE__);
}

void InputCircularList(int count, TCircularList* circularList)
{
    if (count > circularList->Max)
    {
        OtherError(__FILE__, __LINE__);
    }

    int readCount = (int)fread(circularList->Array, sizeof(char), count, stdin);

    circularList->Count = readCount;
    circularList->BeginIndex = 0;
}

bool ShiftCircularList(TCircularList* circularList, int shift)
{    
    for (int i = 0; i < shift; ++i)
    {
        if (fread(circularList->Array + circularList->BeginIndex, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }

        circularList->BeginIndex = (circularList->BeginIndex + 1) % circularList->Count;
    }
    
    return true;
}

void DestroyCircularList(TCircularList* circularList)
{
    free(circularList->Array);
    *circularList = CreateCircularList(0);
}
