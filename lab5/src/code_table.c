#include "code_table.h"
#define CHAR_COUNT (int)256

static TCode CreateCode(char symbol, int length, const char* code)
{
    TCode symbolCode = { symbol, length, NULL };

    if (length > 0)
    {
        symbolCode.Code = calloc(length, sizeof(char));
        if (symbolCode.Code == NULL)
        {
            ExitWithError(__FILE__, __LINE__);
        }

        for (int i = 0; i < length; ++i)
        {
            symbolCode.Code[i] = code[i];
        }
    }

    return symbolCode;
}

static void DestroyCode(TCode* code)
{
    free(code->Code);
    *code = CreateCode(0, 0, NULL);
}

static TCodeTable CreateCodeTable(int max)
{
    TCodeTable table = { 0, max, NULL };

    if (max > 0)
    {
        table.Table = calloc(max, sizeof(TCode));
        if (table.Table == NULL)
        {
            ExitWithError(__FILE__, __LINE__);
        }
    }

    return table;
}

int GetCodeIndex(char symbol, TCodeTable table)
{
    for (int i = 0; i < table.Count; ++i)
    {
        if (table.Table[i].Symbol == symbol)
        {
            return i;
        }
    }
    
    return -1;
}

static void PushCodeTable(TCode code, TCodeTable* table)
{
    if (table->Max == table->Count)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    table->Table[table->Count] = code;
    ++table->Count;
}

void DestroyCodeTable(TCodeTable* table)
{
    for (int i = 0; i < table->Count; ++i)
    {
        DestroyCode(table->Table + i);
    }

    free(table->Table);
    *table = CreateCodeTable(0);
}

static void FillHuffmanTable(int lengthSymbolCode, char* symbolCode, TCodeTable* huffmanTable, TTree huffmanTree)
{
    if (IsLeaf(huffmanTree))
    {
        TCode code = CreateCode(huffmanTree->Symbol, lengthSymbolCode, symbolCode);
        PushCodeTable(code, huffmanTable);
        return;
    }

    symbolCode[lengthSymbolCode] = '0';
    FillHuffmanTable(lengthSymbolCode + 1, symbolCode, huffmanTable, huffmanTree->Left);
    symbolCode[lengthSymbolCode] = '1';
    FillHuffmanTable(lengthSymbolCode + 1, symbolCode, huffmanTable, huffmanTree->Right);
    symbolCode[lengthSymbolCode] = '\0';
}

TCodeTable CreateHuffmanTable(TTree huffmanTree)
{
    int count = CountLeaf(huffmanTree);
    TCodeTable huffmanTable = CreateCodeTable(count);
    
    if (count == 1)
    {
        TCode code = CreateCode(huffmanTree->Symbol, 1, "1");
        PushCodeTable(code, &huffmanTable);
        return huffmanTable;
    }

    char symbolCode[CHAR_COUNT] = { 0 };
    FillHuffmanTable(0, symbolCode, &huffmanTable, huffmanTree);

    return huffmanTable;
}
