#include "table.h"

TTable CreateTable(int row, int column, int size)
{
    TTable table = {
        .Row = row,
        .Column = column,
        .Size = size,
        .Array = NULL
    };

    if (row * column > 0)
    {
        table.Array = calloc(row * column, size);
        if (table.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return table;
}

static void AssignValue(int size, void* dest, const void* src)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void SetTableValue(const void* value, int rowIndex, int columnIndex, TTable* table)
{
    if (rowIndex < 0 || columnIndex < 0 || rowIndex >= table->Row || columnIndex >= table->Column)
    {
        OtherError(__FILE__, __LINE__);
    }

    int index = rowIndex * table->Column + columnIndex;
    AssignValue(table->Size, (char*)table->Array + index * table->Size, value);
}

void* GetTableValue(int rowIndex, int columnIndex, TTable table)
{
    if (rowIndex < 0 || columnIndex < 0 || rowIndex >= table.Row || columnIndex >= table.Column)
    {
        OtherError(__FILE__, __LINE__);
    }

    int index = rowIndex * table.Column + columnIndex;
    return (char*)table.Array + index * table.Size;
}

void DestroyTable(TTable* table)
{
    free(table->Array);
    *table = CreateTable(0, 0, 0);
}
