#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "boyer_moore.h"
#include "circular_list.h"
#define SIZE_TEMPLATE (int)16

int main(void)
{
    TCircularList template = CreateCircularList(SIZE_TEMPLATE);
    InputTemplate(SIZE_TEMPLATE, &template);
    BoyerMooreAlgorithm(template);
    DestroyCircularList(&template);

    return EXIT_SUCCESS;
}
