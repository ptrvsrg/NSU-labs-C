#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

void SyntaxError(void);
void DivisionByZero(void);
void OtherError(char* file, int line);

#endif
