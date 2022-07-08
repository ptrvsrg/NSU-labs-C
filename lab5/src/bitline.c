#include "bitline.h"
#define BYTE (int)8
#define MASK (unsigned char)128

TBitLine CreateBitLine(int max)
{
    TBitLine bitLine = { 0, 0, 0, max, NULL };

    if (max > 0)
    {
        bitLine.Line = calloc(max, sizeof(char));
        if (bitLine.Line == NULL)
        {
            ExitWithError(__FILE__, __LINE__);
        }
    }

    return bitLine;
}

static bool BitLineOverflow(TBitLine bitLine)
{
    return bitLine.Length == bitLine.Max;
}

void AddBit(char bit, TBitLine* bitLine)
{
    if (BitLineOverflow(*bitLine))
    {
        DestroyBitLine(bitLine);
        ExitWithError(__FILE__, __LINE__);
    }

    ++bitLine->Length;
    bitLine->Line[bitLine->EndIndex] = bit;
    bitLine->EndIndex = (bitLine->EndIndex + 1) % bitLine->Max;
}

void AddSymbol(unsigned char symbol, TBitLine* bitLine)
{
    for (int i = 0; i < BYTE; ++i)
    {
        AddBit((symbol & MASK) == 0 ? '0' : '1', bitLine);
        symbol <<= 1;
    }
}

void AddSymbolCode(char symbol, TCodeTable huffmanTable, TBitLine* bitLine)
{
    int index = GetCodeIndex(symbol, huffmanTable);
    for (int i = 0; i < huffmanTable.Table[index].Length; ++i)
    {
        AddBit(huffmanTable.Table[index].Code[i], bitLine);
    }
}

void AddNullBits(TBitLine* bitLine)
{
    if (bitLine->Length > 0 && bitLine->Length < BYTE)
    {
        while (bitLine->Length != BYTE)
        {
            AddBit('0', bitLine);
        }
    }
}

static bool IsEmptyBitLine(TBitLine bitLine)
{
    return bitLine.Length == 0;
}

char ExtractBit(TBitLine* bitLine)
{
    if (IsEmptyBitLine(*bitLine))
    {
        DestroyBitLine(bitLine);
        ExitWithError(__FILE__, __LINE__);
    }
    
    char extractedBit = bitLine->Line[bitLine->BeginIndex];
    bitLine->BeginIndex = (bitLine->BeginIndex + 1) % bitLine->Max;
    --bitLine->Length;
    return extractedBit;
}

char ExtractSymbol(TBitLine* bitLine)
{
    unsigned char symbol = 0;
    for (int i = 0; i < BYTE; ++i)
    {
        symbol <<= 1;
        symbol |= (ExtractBit(bitLine) == '0') ? 0 : 1;
    }

    return symbol;
}

void ExtractEncodedSymbol(TTree huffmanTree, TBitLine* bitLine, TStream* stream)
{
    if (IsLeaf(huffmanTree))
    {
        OutputStream(&(huffmanTree->Symbol), sizeof(char), 1, stream);
        return;
    }

    if (IsEmptyBitLine(*bitLine))
    {
        unsigned char symbol = 0;
        if (InputStream(&symbol, sizeof(symbol), 1, stream) == EOF)
        {
            ExitWithError(__FILE__, __LINE__);
        }

        AddSymbol(symbol, bitLine);
    }

    if (ExtractBit(bitLine) == '0')
    {
        ExtractEncodedSymbol(huffmanTree->Left, bitLine, stream);
    }
    else
    {
        ExtractEncodedSymbol(huffmanTree->Right, bitLine, stream);
    }
}

void InputBitline(TBitLine* bitLine, TStream* stream)
{
    unsigned char symbol = 0;
    if (InputStream(&symbol, sizeof(symbol), 1, stream) == EOF)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    AddSymbol(symbol, bitLine);
}

void OutputBitline(TBitLine* bitLine, TStream* stream)
{
    unsigned char symbol = ExtractSymbol(bitLine);
    OutputStream(&symbol, sizeof(symbol), 1, stream);
}

void DestroyBitLine(TBitLine* bitLine)
{
    free(bitLine->Line);
    *bitLine = CreateBitLine(0);
}
 