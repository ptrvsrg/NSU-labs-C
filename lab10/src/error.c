#include "error.h"

void BadNumberOfPointsError(void)
{
    printf("bad number of points");
    exit(EXIT_SUCCESS);
}

void BadNumberOfLinesError(void)
{
    printf("bad number of lines");
    exit(EXIT_SUCCESS);
}

void OtherError(char* file, int line)
{
    printf("other error (%s, %d)", file, line);
    exit(EXIT_SUCCESS);
}
