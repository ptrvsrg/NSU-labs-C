#define _CRT_SECURE_NO_WARNINGS
#include "string.h"

TString CreateString(void)
{
    TString string = {
        .Length = 0,
        .Line = { 0 }
    };
    return string;
}

void InputSample(int length, TString* string)
{
    if (length > MAX_LENGTH)
    {
        OtherError(__FILE__, __LINE__);
    }

    for (int i = 0; i < length + 1; ++i)
    {    
        char symbol = 0;
        if (fread(&symbol, sizeof(char), 1, stdin) != 1)
        {
            OtherError(__FILE__, __LINE__);
        }

        if (symbol == '\n')
        {
            string->Length = i;
            return;
        }

        string->Line[i] = symbol;
    }
    
    OtherError(__FILE__, __LINE__);
}

void InputString(int length, TString* string)
{
    if (length > MAX_LENGTH)
    {
        OtherError(__FILE__, __LINE__);
    }

    string->Length = (int)fread(string->Line, sizeof(char), length, stdin);
}

bool ShiftString(int shift, TString* string)
{
    if (shift > string->Length)
    {
        OtherError(__FILE__, __LINE__);
    }

    if (shift < string->Length)
    {
        for (int i = 0; i < string->Length - shift; ++i)
        {
            string->Line[i] = string->Line[i + shift];
        }
    }

    return (fread(string->Line + string->Length - shift, sizeof(char), shift, stdin) == shift) ? true : false;
}
