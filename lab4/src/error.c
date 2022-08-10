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

void OtherError(char* file, int line)
{
    printf("other error: %s, %d", file, line);
    exit(EXIT_SUCCESS);
}
