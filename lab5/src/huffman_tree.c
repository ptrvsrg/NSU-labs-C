#include "huffman_tree.h"
#define BYTE (int)8
#define CHAR_COUNT (int)256

static int* CreateFrequencyTable(TStream* stream)
{
    int* frequencyTable = calloc(CHAR_COUNT, sizeof(int));
    if (frequencyTable == NULL)
    {
        DestroyStream(stream);
        ExitWithError(__FILE__, __LINE__);
    }

    while (true)
    {
        unsigned char symbol = 0;  
        if (InputStream(&symbol, sizeof(symbol), 1, stream) == EOF)
        {
            break;
        }

        ++frequencyTable[(int)symbol];
    }

    if (fseek(stream->In, sizeof(char), SEEK_SET) != 0)
    {
        DestroyStream(stream);
        ExitWithError(__FILE__, __LINE__);
    }

    return frequencyTable;
}

TList CreateLeafList(TStream* stream)
{
    int* frequencyTable = CreateFrequencyTable(stream);
    TList list = CreateList();

    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        if (frequencyTable[i] != 0)
        {
            TTree tree = CreateLeaf((char)i);
            PushList(tree, frequencyTable[i], &list);
        }
    }

    free(frequencyTable);
    return list;
}

TTree CreateHuffmanTree(TList* list)
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
    PushList(result, frequencySum, list);

    return CreateHuffmanTree(list);
}

static void OutputHuffmanTreeValue(TTree huffmanTree, TBitLine* bitLine, TStream* stream)
{
    if (IsEmptyTree(huffmanTree))
    {
        return;
    }

    OutputHuffmanTreeValue(huffmanTree->Left, bitLine, stream);
    OutputHuffmanTreeValue(huffmanTree->Right, bitLine, stream);

    if (IsLeaf(huffmanTree))
    {
        AddBit('1', bitLine);
        AddSymbol(huffmanTree->Symbol, bitLine);
    }
    else
    {
        AddBit('0', bitLine);
    }

    while (bitLine->Length >= BYTE)
    {
        OutputBitline(bitLine, stream);
    }
}

void OutputHuffmanTree(TTree huffmanTree, TBitLine* bitLine, TStream* stream)
{
    OutputHuffmanTreeValue(huffmanTree, bitLine, stream);
    AddBit('0', bitLine);
}

TTree InputHuffmanTree(TBitLine* bitLine, TStream* stream)
{
    TStack stack = CreateStack();

    while (true)
    {
        while (*(bitLine->Line) != '0' && bitLine->Length < BYTE + 1)
        {
            InputBitline(bitLine, stream);
        }

        if (ExtractBit(bitLine) == '1')
        {
            char symbol = ExtractSymbol(bitLine);
            TTree leaf = CreateLeaf(symbol);
            PushStack(leaf, &stack);
        }
        else
        {
            if (IsEmptyStack(stack->Next))
            {
                return PopStack(&stack);
            }

            TTree right = PopStack(&stack);
            TTree left = PopStack(&stack);

            TTree result = CreateTree('\0', left, right);
            PushStack(result, &stack);
        }
    }
}
