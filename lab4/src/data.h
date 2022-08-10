#ifndef DATA_H
#define DATA_H

#include "error.h"
#include "string.h"

typedef struct TData
{
    int Number;
    char Operator;
} TData;

TData CreateData(int number, char operator);
TData GetData(TString* string);

#endif // DATA_H
