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
    InputString(&text);
    if (text.Length < sample.Length)
    {
        return;
    }

    int position = sample.Length;

    while (true)
    {
        int textEndIndex = text.BeginIndex + sample.Length - 1;
        int sampleEndIndex = sample.BeginIndex + sample.Length - 1;
        int shift = shiftTable[(unsigned char)text.Line[textEndIndex]];

        for (int i = 0; i < sample.Length; ++i)
        {
            printf("%d ", position - i);
            if (sample.Line[sampleEndIndex - i] != text.Line[textEndIndex - i])
            {
                break;
            }
        }

        position += shift;
        if (!ShiftString(shift, sample.Length, &text))
        {
            return;
        }
    }
}
