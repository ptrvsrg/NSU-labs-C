#include "hash.h"

int Hash(int sampleLength, TString string)
{
    int sum = 0;
    int power = 1;

    for (int i = 0; i < sampleLength; ++i)
    {
        sum += (unsigned char)string.Line[string.BeginIndex + i] % 3 * power;
        power *= 3;
    }

    return sum;
}

int ChangeHash(unsigned char lastSymbol, unsigned char newSymbol, int powerOf3, int textHash)
{
    return ( textHash - lastSymbol % 3 ) / 3 + ( newSymbol % 3 * powerOf3 );
}
