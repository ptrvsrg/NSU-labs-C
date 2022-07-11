#ifndef TABLE_H
#define TABLE_H

#include "error.h"
#include <stdlib.h>

typedef struct TTable
{
    int Row;
    int Column;
    int Size;
    void* Array;
} TTable;

TTable CreateTable(int row, int column, int size);
void SetTableValue(const void* value, int rowIndex, int columnIndex, TTable* table);
void* GetTableValue(int rowIndex, int columnIndex, TTable table);
void DestroyTable(TTable* table);

#endif
