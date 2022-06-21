#define _CRT_SECURE_NO_WARNINGS
#include "avl-tree.h"

TAVLPtr AVLAllocate(TMemory* Memory)
{
    if (Memory->Count == Memory->Index)
    {
        return NULL;
    }

    TAVLPtr tree = (TAVLPtr)((char*)Memory->Buffer + Memory->Index * sizeof(TAVL));
    ++Memory->Index;
    return tree;
}

TAVLPtr CreateAVL(void)
{
    return NULL;
}

TAVLPtr CreateLeaf(int value, TMemory* Memory)
{
    TAVLPtr new = AVLAllocate(Memory);

    new->Height = 1;
    new->HeightDifference = 0;
    new->Value = value;
    new->Left = NULL;
    new->Right = NULL;

    return new;
}

bool IsEmpty(TAVLPtr tree)
{
    return tree == NULL;
}

char GetHeight(TAVLPtr tree)
{
    if (IsEmpty(tree))
    {
        return 0;
    }

    return tree->Height;
}

static char GetHeightDifference(TAVLPtr tree)
{
    if (IsEmpty(tree))
    {
        return 0;
    }

    return tree->HeightDifference;
}

static char Max(char X, char Y)
{
    return X >= Y ? X : Y;
}

static void FixHeight(TAVLPtr tree)
{
    tree->Height = Max(GetHeight(tree->Left), GetHeight(tree->Right)) + 1;
    tree->HeightDifference = GetHeight(tree->Right) - GetHeight(tree->Left);
}

static TAVLPtr RotateRight(TAVLPtr tree)
{
    TAVLPtr buffer = tree->Left;
    tree->Left = buffer->Right;
    buffer->Right = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

static TAVLPtr RotateLeft(TAVLPtr tree)
{
    TAVLPtr buffer = tree->Right;
    tree->Right = buffer->Left;
    buffer->Left = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

static TAVLPtr Balance(TAVLPtr tree)
{
    FixHeight(tree);

    if (GetHeightDifference(tree) == 2)
    {
        if (GetHeightDifference(tree->Right) < 0)
        {
            tree->Right = RotateRight(tree->Right);
        }
        return RotateLeft(tree);
    }
    else if (GetHeightDifference(tree) == -2)
    {
        if (GetHeightDifference(tree->Left) > 0)
        {
            tree->Left = RotateLeft(tree->Left);
        }
        return RotateRight(tree);
    }

    return tree;
}

void Insert(int value, TAVLPtr* tree, TMemory* memory)
{
    if (IsEmpty(*tree))
    {
        *tree = CreateLeaf(value, memory);
    }
    else if (value < (*tree)->Value)
    {
        Insert(value, &(*tree)->Left, memory);
    }
    else
    {
        Insert(value, &(*tree)->Right, memory);
    }

    *tree = Balance(*tree);
}

TAVLPtr InputTree(int treeSize, TMemory* memory)
{
    TAVLPtr tree = CreateAVL();

    for (int i = 0; i < treeSize; ++i)
    {
        int value = 0;
        if (scanf("%d", &value) == EOF)
        {
            exit(EXIT_FAILURE);
        }

        Insert(value, &tree, memory);
    }

    return tree;
}
