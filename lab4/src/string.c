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

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int CharToInt(char digit)
{
    return digit - '0';
}

bool IsOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')';
}

bool IsEmptyString(TString string)
{
    return string.Length <= 0 || string.Line[string.BeginIndex] == '\n';
}

void InputString(TString* string)
{
    string->BeginIndex = 0;
    string->Length = (int)fread(string->Line, sizeof(char), MAX_LENGTH, stdin);
}

char ExtractSymbol(TString* string)
{
    if (IsEmptyString(*string))
    {
        OtherError(__FILE__, __LINE__);
    }

    char symbol = string->Line[string->BeginIndex];
    ++string->BeginIndex;

    if (string->BeginIndex == string->Length)
    {
        InputString(string);
    }

    return symbol;
}
