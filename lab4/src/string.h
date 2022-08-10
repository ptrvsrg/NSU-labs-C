#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>
#include "error.h"

#define MAX_LENGTH (int)256

typedef struct TString
{
    int BeginIndex;
    int Length;
    char Line[MAX_LENGTH];
} TString;

TString CreateString(void);
bool IsDigit(char symbol);
int CharToInt(char digit);
bool IsOperator(char symbol);
bool IsEmptyString(TString string);
void InputString(TString* string);
char ExtractSymbol(TString* string);

#endif // STRING_H
