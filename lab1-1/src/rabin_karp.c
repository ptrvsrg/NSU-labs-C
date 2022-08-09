#include "rabin_karp.h"

static int Pow(unsigned int number, int power)
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

static void PrintProtokol(int position, TString sample, TString text)
{
    for (int i = 0; i < sample.Length; i++)
    {
        printf("%d ", position + i);

        if (sample.Line[sample.BeginIndex + i] != text.Line[text.BeginIndex + i])
        {
            return;
        }
    }
}

void RabinKarpAlgorithm(TString sample)
{
    const int powerOf3 = Pow(3, sample.Length - 1);
    const int sampleHash = Hash(sample.Length, sample);
    printf("%d ", sampleHash);

    TString text = CreateString();
    InputString(&text);
    if (sample.Length > text.Length)
    {
        return;
    }

    int textHash = Hash(sample.Length, text);
    int position = 1;
    
    while (true)
    {
        if (sampleHash == textHash)
        {
            PrintProtokol(position, sample, text);
        }

        unsigned char symbol = text.Line[text.BeginIndex];

        if (!ShiftString(sample.Length, &text))
        {
            return;
        }

        textHash = ChangeHash(symbol, text.Line[text.BeginIndex + sample.Length - 1], powerOf3, textHash);

        ++position;
    }
}
