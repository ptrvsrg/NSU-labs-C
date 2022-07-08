#include "decode.h"
#define BYTE (int)8
#define CHAR_COUNT (int)256
#define MAX_COUNT (BYTE + CHAR_COUNT + 1)

void Decode(TStream stream)
{
    int symbolCount = 0;
    if (InputStream(&symbolCount, sizeof(symbolCount), 1, stream) == EOF)
    {
        return;
    }

    TBitLine bitLine = CreateBitLine(MAX_COUNT);
    TTree huffmanTree = InputHuffmanTree(&bitLine, stream);
    
    for (int i = 0; i < symbolCount; ++i)
    {
        ExtractEncodedSymbol(huffmanTree, &bitLine, stream);
    }

    DestroyBitLine(&bitLine);
    DestroyTree(&huffmanTree);
}
