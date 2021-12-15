#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)(x);

enum
{
    CHAR_BITS = sizeof(char) * 8,
    CHAR_SIZE = 0xff + 1
};

int Max(int X, int Y)
{
    return (X >= Y) ? X : Y;
}

void StrCat(char* to, const char* from)
{
    int length1 = (int)strlen(to);
    int length2 = (int)strlen(from);
    assert(length1 + length2 <= CHAR_SIZE);

    for (int i = 0; i < length2; ++i)
    {
        to[length1 + i] = from[i];
    }
}


void StrMove(int shift, char* line)
{
    int length = (int)strlen(line);

    if(length <= shift)
    {
        memset(line, 0, length);
        return;
    }

    for(int i = 0; i < length - shift; ++i)
    {
        line[i] = line[i + shift];
        line[i + shift] = '\0';
    }
}

//////////////////// SYMBOL CODE TYPE ////////////////////

typedef struct TSymbolCode
{
    char Symbol;
    char Code[CHAR_SIZE];
} TSymbolCode;

TSymbolCode CreateSymbolCode(char symbol, char* code)
{
    TSymbolCode new = { symbol, { 0 } };
    int length = (int)strlen(code);

    for (int i = 0; i < length; ++i)
    {
        new.Code[i] = code[i];
    }
    
    return new;
}

//////////////////// SYMBOL FRECUENCY TYPE ////////////////////

typedef struct TSymbolFrecuency
{
    char Symbol;
    int Frecuency;
} TSymbolFrecuency;

TSymbolFrecuency CreateSymbolFrecuency(char symbol, int frecuency)
{
    TSymbolFrecuency new = { symbol, frecuency };
    return new;
}

//////////////////// BINARY TREE ////////////////////

struct Ttree
{
    TSymbolFrecuency SymbolFrecuency;
    struct Ttree* Left;
    struct Ttree* Right;
};

typedef struct Ttree* TTree;

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

TTree CreateTree(TSymbolFrecuency symbolFrecuency, TTree left, TTree right)
{
    TTree new = malloc(sizeof(*new));
    assert(new != NULL);

    new->SymbolFrecuency = symbolFrecuency;
    new->Left = left;
    new->Right = right;
    return new;
}

int DepthTree(TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }

    return 1 + Max(DepthTree(tree->Left), DepthTree(tree->Right));
}

int SizeTree(TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }
    else if(IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right))
    {
        return 1;
    }

    return SizeTree(tree->Left) + SizeTree(tree->Right);
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

//////////////////// LIST ////////////////////

struct Tlist
{
    TTree Tree;
    struct Tlist* Next;
};

typedef struct Tlist* TList;

TList CreateList(void)
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

void PushList(TTree tree, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(new != NULL);

    new->Tree = tree;
    new->Next = *list;
    *list = new;
}

void PushIncreasingList(TTree tree, TList* list)
{
    if(IsEmptyList(*list) || tree->SymbolFrecuency.Frecuency < (*list)->Tree->SymbolFrecuency.Frecuency)
    {
        PushList(tree, list);
    }
    else
    {
        PushIncreasingList(tree, &(*list)->Next);
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

int SizeList(TList list)
{
    if(IsEmptyList(list))
    {
        return 0;
    }

    return 1 + SizeList(list->Next);
}

//////////////////// ENCODE ////////////////////

int* GetFrecuencyTable(void)
{
    int* frecuencyTable = malloc(sizeof(*frecuencyTable) * CHAR_SIZE);
    assert(frecuencyTable != NULL);

    for (int i = 0; i < CHAR_SIZE; ++i)
    {
        frecuencyTable[i] = 0;
    }

    unsigned char readSymbol;
    while(fread(&readSymbol, sizeof(readSymbol), 1, stdin) == 1)
    {
        ++frecuencyTable[readSymbol];
    }

    return frecuencyTable;
}

TList ConvertFrecuencyTableToList(int* frecuencyTable)
{
    TList list = CreateList();

    for(int i = 0; i < CHAR_SIZE; ++i)
    {
        if(frecuencyTable[i] != 0)
        {
            TSymbolFrecuency value = CreateSymbolFrecuency((char)i, frecuencyTable[i]);
            TTree tree = CreateTree(value, NULL, NULL);
            PushIncreasingList(tree, &list);
        }
    }

    free(frecuencyTable);
    return list;
}

TTree ConvertListToCodeTree(TList* list)
{
    if(IsEmptyList(*list))
    {
        return NULL;
    }
    else if(IsEmptyList((*list)->Next))
    {
        return (*list)->Tree;
    }

    TTree tree1 = PopList(list);
    TTree tree2 = PopList(list);
    TSymbolFrecuency value = CreateSymbolFrecuency('\0', tree1->SymbolFrecuency.Frecuency + tree2->SymbolFrecuency.Frecuency);
    TTree result = CreateTree(value, tree1, tree2);
    PushIncreasingList(result, list);

    return ConvertListToCodeTree(list);
}

void ConvertLeavesToCodes(int* index, char* symbolCode, TSymbolCode* codeTable, TTree tree)
{
    if(IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right))
    {
        codeTable[*index] = CreateSymbolCode(tree->SymbolFrecuency.Symbol, symbolCode);
        ++(*index);
        return;
    }
    
    int length = (int)strlen(symbolCode);
    symbolCode[length] = '0';
    ConvertLeavesToCodes(index, symbolCode, codeTable, tree->Left);
    symbolCode[length] = '1';
    ConvertLeavesToCodes(index, symbolCode, codeTable, tree->Right);
    symbolCode[length] = '\0';
}

TSymbolCode* ConvertTreeToCodeTable(int treeSize, TTree tree)
{
    TSymbolCode* codeTable = malloc(sizeof(*codeTable) * treeSize);
    assert(codeTable != NULL);

    int bitCount = DepthTree(tree) + 1;
    char* symbolCode = malloc(sizeof(*symbolCode) * bitCount);
    assert(symbolCode != NULL);
    memset(symbolCode, 0, bitCount);

    if (treeSize == 1)
    {
        symbolCode[0] = '1';
    }
    
    int index = 0;
    ConvertLeavesToCodes(&index, symbolCode, codeTable, tree);

    free(symbolCode);
    return codeTable;
}

void OutputList(TList list)
{
    int size = SizeList(list);
    UNUSED(size);
    assert(fwrite(&size, sizeof(size), 1, stdout) == 1);

    while(!IsEmptyList(list))
    {
        assert(fwrite(&list->Tree->SymbolFrecuency.Symbol, sizeof(char), 1, stdout) == 1);
        assert(fwrite(&list->Tree->SymbolFrecuency.Frecuency, sizeof(int), 1, stdout) == 1);
        list = list->Next;
    }
}

char* ConvertUnzipToBits(char symbol, TSymbolCode* codeTable)
{
    int index = 0;

    while(codeTable[index].Symbol != symbol)
    {
        ++index;
    }

    return codeTable[index].Code;    
}

char ConvertBitsToZip(char* bits)
{
    unsigned char symbol = 0x0;
    for(int i = 0; i < CHAR_BITS; ++i)
    {
        symbol <<= 1;

        if(bits[i] == '1')
        {
            symbol |= 0x1;
        }
    }

    StrMove(CHAR_BITS, bits);
    return symbol;
}

void OutputZipLine(TSymbolCode* codeTable)
{
    char codeBuffer[2 * CHAR_BITS + 1] = { 0 };
    char readSymbol = 0;
    char writeSymbol = 0;
    UNUSED(writeSymbol);

    while(fread(&readSymbol, sizeof(readSymbol), 1, stdin) == 1)
    {
        char* codeReadSymbol = ConvertUnzipToBits(readSymbol, codeTable);
        StrCat(codeBuffer, codeReadSymbol);

        if(strlen(codeBuffer) >= CHAR_BITS)
        { 
            writeSymbol = ConvertBitsToZip(codeBuffer);
            assert(fwrite(&writeSymbol, sizeof(writeSymbol), 1, stdout) == 1);
        }
    }

    for(int i = (int)strlen(codeBuffer); i < CHAR_BITS; ++i)
    {
        StrCat(codeBuffer, "0");
    }

    writeSymbol = ConvertBitsToZip(codeBuffer);
    assert(fwrite(&writeSymbol, sizeof(writeSymbol), 1, stdout) == 1);
}

void Encode(void)
{
    TList list = ConvertFrecuencyTableToList(GetFrecuencyTable());

    if (IsEmptyList(list))
    {
        return;
    }

    OutputList(list);

    int size = SizeList(list);
    TTree tree = ConvertListToCodeTree(&list);
    TSymbolCode* codeTable = ConvertTreeToCodeTable(size, tree);

    assert(fseek(stdin, sizeof(char), SEEK_SET) == 0);

    OutputZipLine(codeTable);

    free(codeTable);
    DestroyList(&list);
}

//////////////////// DECODE ////////////////////

int InputSize(void)
{
    int size = 0;
    if(fread(&size, sizeof(size), 1, stdin) != 1)
    {
        return 0;
    }
    
    return size;
}

void InputList(TList* list)
{
    int size = InputSize();

    for(int i = 0; i < size; ++i)
    {
        TSymbolFrecuency value = CreateSymbolFrecuency(0, 0);
        assert(fread(&value.Symbol, sizeof(value.Symbol), 1, stdin) == 1);
        assert(fread(&value.Frecuency, sizeof(value.Frecuency), 1, stdin) == 1);
        TTree tree = CreateTree(value, NULL, NULL);
        PushIncreasingList(tree, list);
    }
}

void ConvertZipToBits(unsigned char symbol, char* bits)
{
    for(int i = 0; i < CHAR_BITS; ++i)
    {
        StrCat(bits, ((symbol & 0x80) == 0x0) ? "0" : "1");
        symbol <<= 1;
    }
}

char ConvertBitsToUnzip(char* bits, TTree tree)
{
    assert(!IsEmptyTree(tree));

    if(IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right))
    {
        return tree->SymbolFrecuency.Symbol;   
    }
    else
    {
        char symbol = ConvertBitsToUnzip(bits + 1, (*bits == '0') ? tree->Left : tree->Right);
        StrMove(1, bits);
        return symbol;
    }
}

void OutputUnzipLine(TTree tree)
{
    char buffer[2 * CHAR_BITS + 1] = { 0 };
    int symbolCount = tree->SymbolFrecuency.Frecuency;
    
    for(int i = 0; i < symbolCount; ++i)
    {
        char readSymbol;
        while(strlen(buffer) < CHAR_BITS && fread(&readSymbol, sizeof(readSymbol), 1, stdin) == 1)
        {
            ConvertZipToBits(readSymbol, buffer);
        }

        char writeSymbol = ConvertBitsToUnzip(buffer, tree);
        UNUSED(writeSymbol);        
        assert(fwrite(&writeSymbol, sizeof(writeSymbol), 1, stdout) == 1);
    }
}

void Decode(void)
{
    TList list = CreateList();

    InputList(&list);

    if (IsEmptyList(list))
    {
        return;
    }

    TTree tree = ConvertListToCodeTree(&list);

    OutputUnzipLine(tree);

    DestroyList(&list);
}

//////////////////// MAIN ////////////////////

int main(void)
{
    assert(freopen("in.txt", "rb", stdin) != NULL);
    assert(freopen("out.txt", "wb", stdout) != NULL);

    char workMode = 0;
    assert(fread(&workMode, sizeof(workMode), 1, stdin) == 1);

    switch (workMode)
    {
        case 'c':
            Encode();
            break;
        case 'd':
            Decode();
            break;    
        default:
            assert(false);
    }

    fclose(stdin);
    fclose(stdout);

    return EXIT_SUCCESS;
}