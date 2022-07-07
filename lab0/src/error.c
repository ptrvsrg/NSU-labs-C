#include "error.h"

void BadInputError(void)
{
	printf("bad input\n");
    exit(EXIT_SUCCESS);
}

void OtherError(char* file, int line)
{
    printf("other error: %s, %d\n", file, line);
    exit(EXIT_SUCCESS);
}
