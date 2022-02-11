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

static int lengthBitLine = 0;
static char bitLine[MAX_SIZE] = { 0 };

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

typedef struct TTree* TTree;
struct TTree
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

typedef struct TList* TList;
struct TList
{
    int Frecuency;
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

void PushList(TTree tree, int frecuency, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(!IsEmptyList(new));

    new->Tree = tree;
    new->Frecuency = frecuency;
    new->Next = *list;
    *list = new;
}

void PushPriorityList(TTree tree, int frecuency,  TList* list)
{
    if (IsEmptyList(*list) || frecuency <= (*list)->Frecuency)
    {
        PushList(tree, frecuency, list);
    }
    else
    {
        PushPriorityList(tree, frecuency, &(*list)->Next);
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

void FillFrecuencyTable(int frecuencyTable[], FILE* inFile)
{
    unsigned char readSymbol;
    while (fread(&readSymbol, sizeof(readSymbol), 1, inFile) == 1)
    {
        ++frecuencyTable[readSymbol];
    }
}

TList CreateLeafList(FILE* inFile)
{
    int frecuencyTable[CHAR_SIZE] = { 0 };
    FillFrecuencyTable(frecuencyTable, inFile);
    TList list = CreateList();

    for (int i = 0; i < CHAR_SIZE; ++i)
    {
        if (frecuencyTable[i] != 0)
        {
            TTree tree = CreateTree((char)i, NULL, NULL);
            PushPriorityList(tree, frecuencyTable[i], &list);
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

    int frecuencySum = (*list)->Frecuency;
    TTree left = PopList(list);
    frecuencySum += (*list)->Frecuency;
    TTree right = PopList(list);

    TTree result = CreateTree('\0', left, right);
    PushPriorityList(result, frecuencySum, list);

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

void MoveBitLine(int shift)
{
    for (int i = 0; i < lengthBitLine; ++i)
    {
        bitLine[i] = (lengthBitLine - shift - i > 0) ? bitLine[i + shift] : '\0';
    }

    lengthBitLine -= shift;
}

void AddBitToBitLine(char bit)
{
    bitLine[lengthBitLine] = bit;
    ++lengthBitLine;
}

void AddSymbolCodeToBitLine(unsigned char symbol)
{
    for (int i = 0; i < CHAR_BITS; ++i)
    {
        AddBitToBitLine((symbol & 128) == 0 ? '0' : '1');
        symbol <<= 1;
    }
}

char ExtractSymbolFromBitLine(void)
{
    unsigned char symbol = 0;
    for (int i = 0; i < CHAR_BITS; ++i)
    {
        symbol <<= 1;
        symbol |= (bitLine[i] == '0') ? 0 : 1;
    }

    MoveBitLine(CHAR_BITS);
    return symbol;
}

void AppendNullBits(FILE* outFile)
{
    UNUSED(outFile);
    if(lengthBitLine != 0)
    {
        for (int i = lengthBitLine; i < CHAR_BITS; ++i)
        {
            AddBitToBitLine('0');
        }

        char encodedSymbol = ExtractSymbolFromBitLine();
        UNUSED(encodedSymbol);
        assert(fwrite(&encodedSymbol, sizeof(encodedSymbol), 1, outFile) == 1);
    }
}

void AddSymbolCodeToBitLineUsingHuffmanTable(char symbol, TCode* HuffmanTable)
{
    int index = 0;
    while (HuffmanTable[index].Symbol != symbol)
    {
        ++index;
    }

    for (int i = 0; HuffmanTable[index].Code[i] != '\0'; ++i)
    {
        AddBitToBitLine(HuffmanTable[index].Code[i]);
    }
}

void ExtractSymbolFromBitLineUsingHuffmanTree(TTree tree, FILE* inFile, FILE* outFile)
{
    if(IsLeaf(tree))
    {
        char writtenSymbol = tree->Symbol;
        UNUSED(writtenSymbol);
        assert(fwrite(&writtenSymbol, sizeof(writtenSymbol), 1, outFile) == 1);
        return;
    }

    unsigned char readSymbol;
    if(lengthBitLine == 0 && fread(&readSymbol, sizeof(readSymbol), 1, inFile) == 1)
    {
        AddSymbolCodeToBitLine(readSymbol);
    }

    char bit = *bitLine;
    MoveBitLine(1);
    ExtractSymbolFromBitLineUsingHuffmanTree(bit == '0' ? tree->Left : tree->Right, inFile, outFile);
}

//////////////////////////////////////// INPUT / OUTPUT HUFFMAN TREE ////////////////////////////////////////

void OutputHuffmanTreeValue(TTree tree, FILE* outFile)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    OutputHuffmanTreeValue(tree->Left, outFile);
    OutputHuffmanTreeValue(tree->Right, outFile);

    AddBitToBitLine((IsLeaf(tree)) ? '1' : '0');
    if (IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right))
    {
        AddSymbolCodeToBitLine(tree->Symbol);
    }

    while (lengthBitLine >= CHAR_BITS)
    {
        unsigned char writtenSymbol = ExtractSymbolFromBitLine();
        UNUSED(writtenSymbol);
        assert(fwrite(&writtenSymbol, sizeof(writtenSymbol), 1, outFile) == 1);
    }
}

void OutputHuffmanTree(TTree tree, FILE* outFile)
{
    OutputHuffmanTreeValue(tree, outFile);
    AddBitToBitLine('0');
}

TTree InputHuffmanTree(FILE* inFile)
{
    UNUSED(inFile);
    TList stack = CreateList();

    while(true)
    {
        while(*bitLine != '0' && lengthBitLine < CHAR_BITS + 1)
        {
            unsigned char readSymbol = '\0';
            assert(fread(&readSymbol, sizeof(readSymbol), 1, inFile) == 1);
            AddSymbolCodeToBitLine(readSymbol);
        }

        if(*bitLine == '1')
        {
            MoveBitLine(1);
            char symbol = ExtractSymbolFromBitLine();
            TTree leaf = CreateTree(symbol, NULL, NULL);
            PushList(leaf, 0, &stack);
        }
        else
        {
            MoveBitLine(1);

            if (IsEmptyList(stack->Next))
            {
                return PopList(&stack);
            }
            
            int frecuencySum = stack->Frecuency;
            TTree right = PopList(&stack);
            frecuencySum += stack->Frecuency;
            TTree left = PopList(&stack);

            TTree result = CreateTree('\0', left, right);
            PushList(result, frecuencySum, &stack);
        }
    }
}

//////////////////////////////////////// ENCODER ////////////////////////////////////////

void OutputEncodedMessage(TCode* HuffmanTable, FILE* inFile, FILE* outFile)
{
    char readSymbol;

    while (fread(&readSymbol, sizeof(readSymbol), 1, inFile) == 1)
    {
        AddSymbolCodeToBitLineUsingHuffmanTable(readSymbol, HuffmanTable);
        while (lengthBitLine >= CHAR_BITS)
        {
            char encodedSymbol = ExtractSymbolFromBitLine();
            UNUSED(encodedSymbol);
            assert(fwrite(&encodedSymbol, sizeof(encodedSymbol), 1, outFile) == 1);
        }
    }

    AppendNullBits(outFile);
}

void Encoder(FILE* inFile, FILE* outFile)
{
    TList list = CreateLeafList(inFile);

    if (IsEmptyList(list))
    {
        return;
    }

    TTree tree = ConvertLeafListToHuffmanTree(&list);
    int symbolCount = list->Frecuency;
    UNUSED(symbolCount);
    assert(fwrite(&symbolCount, sizeof(symbolCount), 1, outFile) == 1);
    OutputHuffmanTree(tree, outFile);

    TCode* HuffmanTable = ConvertHuffmanTreeToHuffmanTable(tree);

    assert(fseek(inFile, sizeof(char), SEEK_SET) == 0);
    OutputEncodedMessage(HuffmanTable, inFile, outFile);

    free(HuffmanTable);
    DestroyList(&list);
}

//////////////////////////////////////// DECODER ////////////////////////////////////////

void OutputDecodedMessage(int symbolCount, TTree tree, FILE* inFile, FILE* outFile)
{
    for (int i = 0; i < symbolCount; ++i)
    {
        ExtractSymbolFromBitLineUsingHuffmanTree(tree, inFile, outFile);
    }
}

void Decoder(FILE* inFile, FILE* outFile)
{
    int symbolCount = 0;
    if(fread(&symbolCount, sizeof(symbolCount), 1, inFile) != 1)
    {
        return;
    }

    TTree tree = InputHuffmanTree(inFile);
    OutputDecodedMessage(symbolCount, tree, inFile, outFile);
    DestroyTree(&tree);
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(void)
{
    FILE* inFile = fopen("in.txt", "rb");
    FILE* outFile = fopen("out.txt", "wb");

    assert(inFile != NULL);
    assert(outFile != NULL);
    
    char workMode = '\0';
    assert(fread(&workMode, sizeof(workMode), 1, inFile) == 1);

    switch (workMode)
    {
        case 'c':
            Encoder(inFile, outFile);
            break;
        case 'd':
            Decoder(inFile, outFile);
            break;
        default:
            assert(false);
    } 

    fclose(inFile);
    fclose(outFile);

    return EXIT_SUCCESS;
}