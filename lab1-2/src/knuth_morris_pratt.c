#include "knuth_morris_pratt.h"

static void PrintProtokol(int position, int length)
{
    printf("%d %d ", position, length);
}

void KMPAlgorithm(TString sample)
{
    int shiftTable[MAX_SAMPLE_LENGTH] = { 0 };
    PrefixFunction(shiftTable, sample);
    PrintShiftTable(sample.Length, shiftTable);

    TString text = CreateString();
    InputString(&text);
    if (sample.Length > text.Length)
    {
        return;
    }

    int position = 1;

    while (true)
    {
        int matchedLength = 0;
        while (matchedLength < sample.Length &&
        sample.Line[sample.BeginIndex + matchedLength] == text.Line[text.BeginIndex + matchedLength])
        {
            ++matchedLength;
        }

        int shift = 1;
        if (matchedLength != 0)
        {
            shift = matchedLength - shiftTable[matchedLength - 1];
            PrintProtokol(position, matchedLength);
        }

        position += shift;
        if (!ShiftString(shift, sample.Length, &text))
        {
            return;
        }
    }
}
