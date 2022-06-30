#define _CRT_SECURE_NO_WARNINGS
#include "error.h"

void OtherError(char* file, int line)
{
    printf("%s %d", file, line);
    exit(EXIT_SUCCESS);
}
