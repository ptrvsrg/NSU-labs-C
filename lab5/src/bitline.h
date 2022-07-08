#ifndef BITLINE_H
#define BITLINE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "code_table.h"
#include "error.h"
#include "stream.h"
#include "tree.h"

typedef struct TBitLine
{
    int BeginIndex;
    int EndIndex;
    int Length;
    int Max;
    char* Line;
} TBitLine;

TBitLine CreateBitLine(int max);
void AddBit(char bit, TBitLine* bitLine);
void AddSymbol(unsigned char symbol, TBitLine* bitLine);
void AddSymbolCode(char symbol, TCodeTable huffmanTable, TBitLine* bitLine);
void AddNullBits(TBitLine* bitLine);
bool IsEmptyBitLine(TBitLine bitLine);
char ExtractBit(TBitLine* bitLine);
char ExtractSymbol(TBitLine* bitLine);
void ExtractEncodedSymbol(TTree huffmanTree, TBitLine* bitLine, TStream stream);
void InputBitline(TBitLine* bitLine, TStream stream);
void OutputBitline(TBitLine* bitLine, TStream stream);
void DestroyBitLine(TBitLine* bitLine);

#endif
