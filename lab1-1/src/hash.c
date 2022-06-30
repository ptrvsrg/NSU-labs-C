#include "hash.h"

int Hash(TCircularList list)
{
    int sum = 0;
    int power = 1;

    for (int i = 0; i < list.Count; ++i)
    {
        int index = (list.BeginIndex + i) % list.Count;
        sum += (unsigned char)list.Array[index] % 3 * power;
        power *= 3;
    }

    return sum;
}

int ChangeHash(unsigned char lastSymbol, unsigned char newSymbol, int powerOf3, int textHash)
{
    return ( textHash - lastSymbol % 3 ) / 3 + ( newSymbol % 3 * powerOf3 );
}
