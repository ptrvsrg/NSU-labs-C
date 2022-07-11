#include "error.h"

void OtherError(char* file, int line)
{
    printf("other error: %s, %d\n", file, line);
    exit(EXIT_FAILURE);
}
