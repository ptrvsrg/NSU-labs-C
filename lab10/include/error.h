#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

void BadNumberOfPointsError(void);
void BadNumberOfLinesError(void);
void OtherError(char* file, int line);

#endif
