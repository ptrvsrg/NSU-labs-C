#ifndef CODE_TABLE_H
#define CODE_TABLE_H

#include <stdlib.h>
#include "error.h"
#include "tree.h"

typedef struct TCode
{
    char Symbol;
    int Length;
    char* Code;
} TCode;

typedef struct TCodeTable
{
    int Count;
    int Max;
    TCode* Table;
} TCodeTable;

int GetCodeIndex(char symbol, TCodeTable table);
void DestroyCodeTable(TCodeTable* table);
TCodeTable CreateHuffmanTable(TTree huffmanTree);

#endif
