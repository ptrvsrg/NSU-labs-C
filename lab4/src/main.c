#include "input.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE_NOTATION (int)1000

////////////////////////////////  MAIN  ////////////////////////////////

int main(void)
{
    char infix [SIZE_NOTATION + 1] = { 0 };
    InputInfix(infix, SIZE_NOTATION + 1);
    
    printf("%d", Calc(infix));

    return EXIT_SUCCESS;
}