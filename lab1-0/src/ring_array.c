#define _CRT_SECURE_NO_WARNINGS
#include "ring_array.h"

TRingArray CreateRingArray(int count)
{
    TRingArray ringArray = { 0, count, NULL };

    if (count > 0)
    {
        ringArray.Array = calloc(count, sizeof(char));
        if (ringArray.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }
    
    return ringArray;
}

bool InputTemplate(TRingArray* ringArray)
{
    for (int i = 0; i < ringArray->Count + 1; ++i)
    {    
        if (fread(ringArray->Array + i, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }

        if (ringArray->Array[i] == '\n')
        {
            ringArray->Array[i] = '\0';
            ringArray->EndIndex = i - 1;
            ringArray->Count = i;

            return true;
        }
    }
    
    return false;
}

bool InputRingArray(TRingArray* ringArray)
{
    for (int i = 0; i < ringArray->Count; ++i)
    {    
        if (fread(ringArray->Array + i, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }
    }

    ringArray->EndIndex = ringArray->Count - 1;
    return true;
}

bool ShiftRingArray(TRingArray* ringArray, int shift)
{
    for (int i = 0; i < shift; ++i)
    {
        int index = (ringArray->EndIndex + i + 1) % ringArray->Count;
        if (fread(ringArray->Array + index, sizeof(char), 1, stdin) != 1)
        {
            return false;
        }
    }
        
    ringArray->EndIndex = (ringArray->EndIndex + shift) % ringArray->Count;
    return true;
}

void DestroyRingArray(TRingArray* ringArray)
{
    free(ringArray->Array);
    *ringArray = CreateRingArray(0);
}
