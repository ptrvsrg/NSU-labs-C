#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define MAX_SAMPLE_LENGTH (int)16
#define MAX_STRING_LENGTH (int)1024

typedef struct TString
{
    int BeginIndex;
    int Length;
    char Line[MAX_STRING_LENGTH];
} TString;

TString CreateString(void);
void InputSample(TString* string);
void InputString(TString* string);
bool ShiftString(int shift, int sampleLength, TString* string);

#endif
