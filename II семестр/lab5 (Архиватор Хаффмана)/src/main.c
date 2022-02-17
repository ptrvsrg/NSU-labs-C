#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNUSED(x) (void)(x);

enum
{
    CHAR_SIZE = 256,
    CHAR_BITS = 8,
    MAX_SIZE = CHAR_SIZE + CHAR_BITS + 1
};


//////////////////////////////////////// STREAM TYPE ////////////////////////////////////////

typedef struct TStream
{
    FILE* in;
    FILE* out;
} TStream;

TStream CreateStreams(void)
{
    TStream streams = { NULL, NULL };

    streams.in = fopen("in.txt", "rb");
    assert(streams.in != NULL);

    streams.out = fopen("out.txt", "wb");
    assert(streams.out != NULL);

    return streams;
}

void CloseStreams(TStream* streams)
{
    fclose(streams->in);
    fclose(streams->out);
}

//////////////////////////////////////// BIT LINE TYPE ////////////////////////////////////////

typedef struct TBitLine
{
    int length;
    char line[MAX_SIZE];
} TBitLine;

//////////////////////////////////////// SYMBOL CODE TYPE ////////////////////////////////////////

typedef struct TCode
{
    char Symbol;
    char Code[CHAR_SIZE];
} TCode;

TCode CreateCode(char symbol, int length, char* code)
{
    TCode symbolCode = { symbol, "" };

    for (int i = 0; i < length; ++i)
    {
        symbolCode.Code[i] = code[i];
    }

    return symbolCode;
}

//////////////////////////////////////// BINARY TREE TYPE ////////////////////////////////////////

typedef struct Ttree* TTree;
struct Ttree
{
    char Symbol;
    TTree Left;
    TTree Right;
};

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

bool IsLeaf(TTree tree)
{
    return (IsEmptyTree(tree)) ? false : IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right);
}

TTree CreateTree(char symbol, TTree left, TTree right)
{
    TTree new = malloc(sizeof(*new));
    assert(!IsEmptyTree(new));

    new->Symbol = symbol;
    new->Left = left;
    new->Right = right;
    return new;
}

int CountLeaf(TTree tree)
{
    if (IsEmptyTree(tree))
    {
        return 0;
    }
    else if (IsLeaf(tree))
    {
        return 1;
    }

    return CountLeaf(tree->Left) + CountLeaf(tree->Right);
}

void DestroyTree(TTree* tree)
{
    if (!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

//////////////////////////////////////// PRIORITY LIST TYPE ////////////////////////////////////////

typedef struct Tlist* TList;

struct Tlist
{
    int Frequency;
    TTree Tree;
    TList Next;
};

TList CreateList(void)
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

void PushList(TTree tree, int frequency, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(!IsEmptyList(new));

    new->Tree = tree;
    new->Frequency = frequency;
    new->Next = *list;
    *list = new;
}

void PushPriorityList(TTree tree, int frequency,  TList* list)
{
    if (IsEmptyList(*list) || frequency <= (*list)->Frequency)
    {
        PushList(tree, frequency, list);
    }
    else
    {
        PushPriorityList(tree, frequency, &(*list)->Next);
    }
}

TTree PopList(TList* list)
{
    assert(!IsEmptyList(*list));

    TTree removeTree = (*list)->Tree;
    TList removeItem = *list;
    *list = (*list)->Next;
    free(removeItem);
    return removeTree;
}

void DestroyList(TList* list)
{
    if (!IsEmptyList(*list))
    {
        DestroyList(&(*list)->Next);
        DestroyTree(&(*list)->Tree);
        free(*list);
    }
}

//////////////////////////////////////// TYPECASTING ////////////////////////////////////////

void FillFrequencyTable(int frequencyTable[], TStream streams)
{
    unsigned char readSymbol;
    while (fread(&readSymbol, sizeof(readSymbol), 1, streams.in) == 1)
    {
        ++frequencyTable[readSymbol];
    }
}

TList CreateLeafList(TStream streams)
{
    int frequencyTable[CHAR_SIZE] = { 0 };
    FillFrequencyTable(frequencyTable, streams);
    TList list = CreateList();

    for (int i = 0; i < CHAR_SIZE; ++i)
    {
        if (frequencyTable[i] != 0)
        {
            TTree tree = CreateTree((char)i, NULL, NULL);
            PushPriorityList(tree, frequencyTable[i], &list);
        }
    }
    
    return list;
}

TTree ConvertLeafListToHuffmanTree(TList* list)
{
    if (IsEmptyList(*list))
    {
        return NULL;
    }
    else if (IsEmptyList((*list)->Next))
    {
        return (*list)->Tree;
    }

    int frequencySum = (*list)->Frequency;
    TTree left = PopList(list);
    frequencySum += (*list)->Frequency;
    TTree right = PopList(list);

    TTree result = CreateTree('\0', left, right);
    PushPriorityList(result, frequencySum, list);

    return ConvertLeafListToHuffmanTree(list);
}

void FillHuffmanTable(int lengthSymbolCode, char* symbolCode, TCode* HuffmanTable, TTree tree)
{
    if (IsLeaf(tree))
    {
        static int index = 0;
        HuffmanTable[index] = CreateCode(tree->Symbol, lengthSymbolCode, symbolCode);
        ++index;
        return;
    }

    symbolCode[lengthSymbolCode] = '0';
    FillHuffmanTable(lengthSymbolCode + 1, symbolCode, HuffmanTable, tree->Left);
    symbolCode[lengthSymbolCode] = '1';
    FillHuffmanTable(lengthSymbolCode + 1, symbolCode, HuffmanTable, tree->Right);
    symbolCode[lengthSymbolCode] = '\0';
}

TCode* ConvertHuffmanTreeToHuffmanTable(TTree tree)
{
    int size = CountLeaf(tree);
    TCode* HuffmanTable = calloc(size, sizeof(*HuffmanTable));
    assert(HuffmanTable != NULL);
    
    if (size == 1)
    {
        HuffmanTable[0] = CreateCode(tree->Symbol, 1, "1");
        return HuffmanTable;
    }

    char symbolCode[CHAR_SIZE] = { 0 };
    FillHuffmanTable(0, symbolCode, HuffmanTable, tree);

    return HuffmanTable;
}

//////////////////////////////////////// WORKING WITH BITS ////////////////////////////////////////

void MoveBitLine(int shift, TBitLine* bitLine)
{
    for (int i = 0; i < bitLine->length; ++i)
    {
        bitLine->line[i] = (bitLine->length - shift - i > 0) ? bitLine->line[i + shift] : '\0';
    }

    bitLine->length -= shift;
}

void AddBitToBitLine(char bit, TBitLine* bitLine)
{
    bitLine->line[bitLine->length] = bit;
    ++bitLine->length;
}

void AddSymbolCodeToBitLine(unsigned char symbol, TBitLine* bitLine)
{
    for (int i = 0; i < CHAR_BITS; ++i)
    {
        AddBitToBitLine((symbol & 128) == 0 ? '0' : '1', bitLine);
        symbol <<= 1;
    }
}

char ExtractSymbolFromBitLine(TBitLine* bitLine)
{
    unsigned char symbol = 0;
    for (int i = 0; i < CHAR_BITS; ++i)
    {
        symbol <<= 1;
        symbol |= (bitLine->line[i] == '0') ? 0 : 1;
    }

    MoveBitLine(CHAR_BITS, bitLine);
    return symbol;
}

void AppendNullBits(TBitLine* bitLine, TStream streams)
{
    if (bitLine->length != 0)
    {
        for (int i = bitLine->length; i < CHAR_BITS; ++i)
        {
            AddBitToBitLine('0', bitLine);
        }

        char encodedSymbol = ExtractSymbolFromBitLine(bitLine);
        UNUSED(encodedSymbol);
        int control = fwrite(&encodedSymbol, sizeof(encodedSymbol), 1, streams.out);
        UNUSED(control);
        assert(control == 1);
    }
}

void AddSymbolCodeToBitLineUsingHuffmanTable(char symbol, TCode* HuffmanTable, TBitLine* bitLine)
{
    int index = 0;
    while (HuffmanTable[index].Symbol != symbol)
    {
        ++index;
    }

    for (int i = 0; HuffmanTable[index].Code[i] != '\0'; ++i)
    {
        AddBitToBitLine(HuffmanTable[index].Code[i], bitLine);
    }
}

void ExtractSymbolFromBitLineUsingHuffmanTree(TTree tree, TBitLine* bitLine, TStream streams)
{
    if (IsLeaf(tree))
    {
        char writtenSymbol = tree->Symbol;
        UNUSED(writtenSymbol);
        int control = fwrite(&writtenSymbol, sizeof(writtenSymbol), 1, streams.out);
        UNUSED(control);
        assert(control == 1);
        return;
    }

    unsigned char readSymbol;
    if (bitLine->length == 0 && fread(&readSymbol, sizeof(readSymbol), 1, streams.in) == 1)
    {
        AddSymbolCodeToBitLine(readSymbol, bitLine);
    }

    char bit = *bitLine->line;
    MoveBitLine(1, bitLine);
    ExtractSymbolFromBitLineUsingHuffmanTree(bit == '0' ? tree->Left : tree->Right, bitLine, streams);
}

//////////////////////////////////////// INPUT / OUTPUT HUFFMAN TREE ////////////////////////////////////////

void OutputHuffmanTreeValue(TTree tree, TBitLine* bitLine, TStream streams)
{
    if (IsEmptyTree(tree))
    {
        return;
    }

    OutputHuffmanTreeValue(tree->Left, bitLine, streams);
    OutputHuffmanTreeValue(tree->Right, bitLine, streams);

    AddBitToBitLine((IsLeaf(tree)) ? '1' : '0', bitLine);
    if (IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right))
    {
        AddSymbolCodeToBitLine(tree->Symbol, bitLine);
    }

    while (bitLine->length >= CHAR_BITS)
    {
        unsigned char writtenSymbol = ExtractSymbolFromBitLine(bitLine);
        UNUSED(writtenSymbol);
        int control = fwrite(&writtenSymbol, sizeof(writtenSymbol), 1, streams.out);
        UNUSED(control);
        assert(control == 1);
    }
}

void OutputHuffmanTree(TTree tree, TBitLine* bitLine, TStream streams)
{
    OutputHuffmanTreeValue(tree, bitLine, streams);
    AddBitToBitLine('0', bitLine);
}

TTree InputHuffmanTree(TBitLine* bitLine, TStream streams)
{
    TList stack = CreateList();

    while (true)
    {
        while (*bitLine->line != '0' && bitLine->length < CHAR_BITS + 1)
        {
            unsigned char readSymbol = '\0';
            int control = fread(&readSymbol, sizeof(readSymbol), 1, streams.in);
            UNUSED(control);
            assert(control == 1);
            AddSymbolCodeToBitLine(readSymbol, bitLine);
        }

        if (*bitLine->line == '1')
        {
            MoveBitLine(1, bitLine);
            char symbol = ExtractSymbolFromBitLine(bitLine);
            TTree leaf = CreateTree(symbol, NULL, NULL);
            PushList(leaf, 0, &stack);
        }
        else
        {
            MoveBitLine(1, bitLine);

            if (IsEmptyList(stack->Next))
            {
                return PopList(&stack);
            }
            
            int frequencySum = stack->Frequency;
            TTree right = PopList(&stack);
            frequencySum += stack->Frequency;
            TTree left = PopList(&stack);

            TTree result = CreateTree('\0', left, right);
            PushList(result, frequencySum, &stack);
        }
    }
}

//////////////////////////////////////// ENCODER ////////////////////////////////////////

void OutputEncodedMessage(TCode* HuffmanTable, TBitLine* bitLine, TStream streams)
{
    char readSymbol;

    while (fread(&readSymbol, sizeof(readSymbol), 1, streams.in) == 1)
    {
        AddSymbolCodeToBitLineUsingHuffmanTable(readSymbol, HuffmanTable, bitLine);
        while (bitLine->length >= CHAR_BITS)
        {
            char encodedSymbol = ExtractSymbolFromBitLine(bitLine);
            UNUSED(encodedSymbol);
            int control = fwrite(&encodedSymbol, sizeof(encodedSymbol), 1, streams.out);
            UNUSED(control);
            assert(control == 1);
        }
    }

    AppendNullBits(bitLine, streams);
}

void Encoder(TStream streams)
{
    TList list = CreateLeafList(streams);

    if (IsEmptyList(list))
    {
        return;
    }

    TTree tree = ConvertLeafListToHuffmanTree(&list);

    int symbolCount = list->Frequency;
    UNUSED(symbolCount);
    int control = fwrite(&symbolCount, sizeof(symbolCount), 1, streams.out);
    UNUSED(control);
    assert(control == 1);

    TBitLine bitLine = { 0, "" };
    OutputHuffmanTree(tree, &bitLine, streams);

    TCode* HuffmanTable = ConvertHuffmanTreeToHuffmanTable(tree);

    control = fseek(streams.in, sizeof(char), SEEK_SET);
    assert(control == 0);

    OutputEncodedMessage(HuffmanTable, &bitLine, streams);

    free(HuffmanTable);
    DestroyList(&list);
}

//////////////////////////////////////// DECODER ////////////////////////////////////////

void OutputDecodedMessage(int symbolCount, TTree tree, TBitLine* bitLine, TStream streams)
{
    for (int i = 0; i < symbolCount; ++i)
    {
        ExtractSymbolFromBitLineUsingHuffmanTree(tree, bitLine, streams);
    }
}

void Decoder(TStream streams)
{
    int symbolCount = 0;
    if (fread(&symbolCount, sizeof(symbolCount), 1, streams.in) != 1)
    {
        return;
    }

    TBitLine bitLine = { 0, "" };
    TTree tree = InputHuffmanTree(&bitLine, streams);
    OutputDecodedMessage(symbolCount, tree, &bitLine, streams);
    DestroyTree(&tree);
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(void)
{
    TStream streams = CreateStreams();
    
    char workMode = '\0';
    int control = fread(&workMode, sizeof(workMode), 1, streams.in);
    UNUSED(control);
    assert(control == 1);

    switch (workMode)
    {
        case 'c':
            Encoder(streams);
            break;
        case 'd':
            Decoder(streams);
            break;
        default:
            assert(false);
    } 

    CloseStreams(&streams);

    return EXIT_SUCCESS;
}
