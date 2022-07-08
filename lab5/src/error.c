#include "error.h"

void ExitWithError(char* file, int line)
{
    fprintf(stderr, "error: %s, %d\n", file, line);
    exit(EXIT_FAILURE);
}
