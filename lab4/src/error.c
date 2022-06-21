#include "error.h"

void SyntaxError(void) 
{
    printf("syntax error");
    exit(EXIT_SUCCESS);
}

void DivisionByZero(void) 
{
    printf("division by zero");
    exit(EXIT_SUCCESS);
}

void OtherError(void) 
{
    printf("other error");
    exit(EXIT_SUCCESS);
}
