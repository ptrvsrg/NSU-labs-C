#include "error.h"

void BadInputError(void)
{
	printf("bad input");
    exit(EXIT_SUCCESS);
}

void OtherError(char* file, int line)
{
    printf("other error: %s, %d", file, line);
    exit(EXIT_SUCCESS);
}
