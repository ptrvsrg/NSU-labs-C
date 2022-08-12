#include "prefix_function.h"

void PrefixFunction(int shiftTable[], TString sample)
{
	for (int i = 1; i < sample.Length; ++i)
    {
		int j = shiftTable[i - 1];
		while (j > 0 && sample.Line[sample.BeginIndex + i] != sample.Line[sample.BeginIndex + j])
        {
			j = shiftTable[j-1];
        }

        if (sample.Line[sample.BeginIndex + i] == sample.Line[sample.BeginIndex + j])
        {
            ++j;
        }

		shiftTable[i] = j;
	}
}

void PrintShiftTable(int sampleLength, int shiftTable[])
{
    for (int i = 0; i < sampleLength; ++i)
    {
        printf("%d ", shiftTable[i]);
    }
}
