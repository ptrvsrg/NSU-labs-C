#include "string.h"

TString CreateString(void)
{
    TString string = {
        .BeginIndex = 0,
        .Length = 0,
        .Line = { 0 }
    };
    return string;
}

void InputSample(TString* string)
{
    for (int i = 0; i < MAX_SAMPLE_LENGTH + 1; ++i)
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

void InputString(TString* string)
{
    string->Length = (int)fread(string->Line, sizeof(char), MAX_STRING_LENGTH, stdin);
    string->BeginIndex = 0;
}

bool ShiftString(int sampleLength, TString* string)
{
    if (string->BeginIndex + sampleLength + 1 > string->Length)
    {
        for (int i = 0; i < sampleLength - 1; ++i)
        {
            string->Line[i] = string->Line[string->BeginIndex + 1 + i];
        }

        string->Length = sampleLength - 1 + (int)fread(string->Line + sampleLength - 1, sizeof(char), MAX_STRING_LENGTH - sampleLength + 1, stdin);
        string->BeginIndex = 0;
        return (string->Length > sampleLength);
    }

    ++string->BeginIndex;
    return true;
}
