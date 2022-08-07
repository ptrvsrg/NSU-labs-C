#define _CRT_SECURE_NO_WARNINGS
#include "boyer_moore.h"
#define COUNT_CHAR (int)256

static void CreateShiftTable(TString sample, int shiftTable[])
{
    for (int i = 0; i < COUNT_CHAR; ++i)
    {
        shiftTable[i] = sample.Length;
    }

    for (int i = 0; i < sample.Length - 1; ++i)
    {
        unsigned char symbol = sample.Line[i];
        shiftTable[(int)symbol] = sample.Length - 1 - i;
    }
}

void BoyerMooreAlgorithm(TString sample)
{
    int shiftTable[COUNT_CHAR] = { 0 };
    CreateShiftTable(sample, shiftTable);

    TString text = CreateString();
    InputString(sample.Length, &text);
    if (text.Length != sample.Length)
    {
        return;
    }

    int position = sample.Length;
    int index = 0;
        
    while (true)
    {
        printf("%d ", position);
        int textIndex = text.Length - index - 1;
        int sampleIndex = sample.Length - index - 1;

        if (sample.Line[sampleIndex] != text.Line[textIndex])
        {
            unsigned char symbol = text.Line[text.Length - 1];
            int shift = shiftTable[(int)symbol];
            position += shift + index;

            if (!ShiftString(shift, &text))
            {
                return;
            }

            index = 0;
            continue;
        }

        if (index == text.Length - 1)
        {
            position += text.Length + index;

            if (!ShiftString(text.Length, &text))
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
