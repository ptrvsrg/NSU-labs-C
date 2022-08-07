#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define MAX_LENGTH 16

typedef struct TString
{
    int Length;
    char Line[MAX_LENGTH];
} TString;

TString CreateString(void);
void InputSample(int length, TString* string);
void InputString(int length, TString* string);
bool ShiftString(int shift, TString* string);

#endif
