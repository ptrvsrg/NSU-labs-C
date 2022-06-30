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

static void PrintProtokol(TCircularList template, TCircularList text, int position)
{
    for (int i = 0; i < template.Count; i++)
    {
        printf("%d ", position + i);

        int index = (text.BeginIndex + i) % text.Count;
        if (template.Array[i] != text.Array[index])
        {
            return;
        }
    }
}

void RabinKarpAlgorithm(TCircularList template)
{
    const int powerOf3 = Pow(3, template.Count - 1);
    const int templateHash = Hash(template);
    printf("%d ", templateHash);

    TCircularList text = CreateCircularList(template.Count);
    InputCircularList(template.Count, &text);
    if (template.Count != text.Count)
    {
        DestroyCircularList(&text);
        return;
    }

    int textHash = Hash(text);
    int position = 1;
    
    while (true)
    {
        if (templateHash == textHash)
        {
            PrintProtokol(template, text, position);
        }

        unsigned char symbol = text.Array[text.BeginIndex];

        if (!ShiftCircularList(&text, 1))
        {
            DestroyCircularList(&text);
            return;
        }

        int index = (text.BeginIndex + text.Count - 1) % text.Count;
        textHash = ChangeHash(symbol, text.Array[index], powerOf3, textHash);

        ++position;
    }
}
