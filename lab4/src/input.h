#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include "error.h"
#include "stack.h"

bool IsDigit(char symbol);
void InputInfix(char* infix, int length);

#endif