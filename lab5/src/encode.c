#include "encode.h"
#define BYTE (int)8
#define CHAR_COUNT (int)256
#define MAX_COUNT (BYTE + CHAR_COUNT + 1)

static void OutputEncodedMessage(TCodeTable huffmanTable, TBitLine* bitLine, TStream stream)
{
    while (true)
    {
        unsigned char readSymbol = 0;
        if (InputStream(&readSymbol, sizeof(readSymbol), 1, stream) == EOF)
        {
            break;
        }
        
        AddSymbolCode(readSymbol, huffmanTable, bitLine);

        while (bitLine->Length >= BYTE)
        {
            OutputBitline(bitLine, stream);
        }
    }

    AddNullBits(bitLine);
    if (bitLine->Length == BYTE)
    {
        OutputBitline(bitLine, stream);
    }
}

void Encode(TStream stream)
{
    TList list = CreateLeafList(stream);
    if (IsEmptyList(list))
    {
        return;
    }

    TTree tree = CreateHuffmanTree(&list);
    int symbolCount = list->Frequency;
    OutputStream(&symbolCount, sizeof(symbolCount), 1, stream);

    TBitLine bitLine = CreateBitLine(MAX_COUNT);
    OutputHuffmanTree(tree, &bitLine, stream);

    TCodeTable huffmanTable = CreateHuffmanTable(tree);
    OutputEncodedMessage(huffmanTable, &bitLine, stream);

    DestroyBitLine(&bitLine);
    DestroyCodeTable(&huffmanTable);
    DestroyList(&list);
}
