#define _CRT_SECURE_NO_WARNINGS
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    freopen("in.txt", "r", stdin);
    printf("%d", Calc());
    return EXIT_SUCCESS;
}
