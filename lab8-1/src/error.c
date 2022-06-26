#include "error.h"

void BadNumberOfVerticesError(void)
{
    printf("bad number of vertices");
    exit(EXIT_SUCCESS);
}

void BadNumberOfEdgesError(void)
{
    printf("bad number of edges");
    exit(EXIT_SUCCESS);
}

void BadNumberOfLinesError(void)
{
    printf("bad number of lines");
    exit(EXIT_SUCCESS);
}

void BadVertexError(void)
{
    printf("bad vertex");
    exit(EXIT_SUCCESS);
}

void BadLengthError(void)
{
    printf("bad length");
    exit(EXIT_SUCCESS);
}

void NoSpanningTreeError(void)
{
    printf("no spanning tree");
    exit(EXIT_SUCCESS);
}

void OtherError(char* file, int line)
{
    printf("other error (%s, %d)", file, line);
    exit(EXIT_SUCCESS);
}
