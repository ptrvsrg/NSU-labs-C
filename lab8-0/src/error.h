#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

void BadNumberOfVerticesError(void);
void BadNumberOfEdgesError(void);
void BadNumberOfLinesError(void);
void BadVertexError(void);
void BadLengthError(void);
void NoSpanningTreeError(void);
void OtherError(char* file, int line);

#endif
