#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "boyer_moore.h"
#include "ring_array.h"
#define SIZE_TEMPLATE (int)16

int main(void)
{
    TRingArray template = CreateRingArray(SIZE_TEMPLATE);
    if (!InputTemplate(&template))
    {
        return EXIT_SUCCESS;
    }

    BoyerMooreAlgorithm(template);
    DestroyRingArray(&template);

    return EXIT_SUCCESS;
}
