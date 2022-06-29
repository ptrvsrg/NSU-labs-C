#define _CRT_SECURE_NO_WARNINGS
#include "boyer_moore.h"
#define COUNT_CHAR (int)256

static void CreateShiftTable(TRingArray template, int shiftTable[])
{
    for (int i = 0; i < COUNT_CHAR; ++i)
    {
        shiftTable[i] = template.Count;
    }

    for (int i = 0; i < template.Count - 1; ++i)
    {
        unsigned char symbol = template.Array[i];
        shiftTable[(int)symbol] = template.Count - 1 - i;
    }
}

void BoyerMooreAlgorithm(TRingArray template)
{
    int shiftTable[COUNT_CHAR] = { 0 };
    CreateShiftTable(template, shiftTable);

    TRingArray text = CreateRingArray(template.Count);
    if (!InputRingArray(&text))
    {
        DestroyRingArray(&text);
        return;
    }

    int position = template.Count;
    int index = 0;
        
    while (true)
    {
        printf("%d ", position);
        int indexText = (text.EndIndex + text.Count - index) % text.Count;
        int indexTemplate = template.EndIndex - index;

        if (template.Array[indexTemplate] != text.Array[indexText])
        {
            unsigned char symbol = text.Array[(index == 0) ? indexText : text.EndIndex];
            position += shiftTable[(int)symbol] + index;

            if (!ShiftRingArray(&text, shiftTable[(int)symbol]))
            {
                DestroyRingArray(&text);
                return;
            }

            index = 0;
            continue;
        }

        if (index == text.Count - 1)
        {
            position += text.Count + index;

            if (!ShiftRingArray(&text, text.Count))
            {        
                DestroyRingArray(&text);
                return;
            }

            index = 0;
            continue;
        }

        --position;
        ++index;
    }
}
