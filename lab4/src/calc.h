#ifndef CALC_H
#define CALC_H

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "input.h"
#include "stack.h"

int Calc(const char* infix);

#endif