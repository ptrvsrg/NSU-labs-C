#ifndef INOUT_H
#define INOUT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define SIZE_SEQUENCE (int)10

void PrintSequence(const char* sequence);
void InputSequence(char* sequence);
void InputPermutationCount(unsigned int* count);

#endif
