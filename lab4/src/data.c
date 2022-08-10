#include "data.h"

TData CreateData(int number, char operator)
{
    TData data = {
        .Number = number,
        .Operator = operator
    };

    return data;
}

TData GetData(TString* string)
{
    if (IsEmptyString(*string))
    {
        OtherError(__FILE__, __LINE__);
    }

    if (IsDigit(string->Line[string->BeginIndex]))
    {
        int number = 0;
        while (IsDigit(string->Line[string->BeginIndex]))
        {
            number *= 10;
            number += CharToInt(ExtractSymbol(string));
        }

        return CreateData(number, '\0');
    }
    else if (IsOperator(string->Line[string->BeginIndex]))
    {
        return CreateData(0, ExtractSymbol(string));
    }

    SyntaxError();
    return CreateData(0, '\0');
}
