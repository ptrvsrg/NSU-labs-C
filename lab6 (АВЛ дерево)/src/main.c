#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNUSED(x) (void)(x)

///////////////////////////// MEMORY FUNCTION /////////////////////////////

typedef struct TAVL* TAVL;
struct TAVL
{
    char Height;
    char HeightDifference;
    int Value;
    TAVL Left;
    TAVL Right;
};

typedef struct TMemory
{
    int Count;
    int Index;
    TAVL Buffer;
} TMemory;

TMemory CreateMemory(int count)
{
    TMemory Memory = { count, 0, NULL };

    Memory.Buffer = malloc(count * sizeof(*Memory.Buffer));
    assert(Memory.Buffer != NULL);

    return Memory;
}

TAVL AVLAllocate(TMemory* Memory)
{
    assert(Memory->Count != Memory->Index);
    ++Memory->Index;
    return &Memory->Buffer[Memory->Index - 1];
}

void DestroyMemory(TMemory* Memory)
{
    free(Memory->Buffer);
}

///////////////////////////// AVL TREE TYPE /////////////////////////////

TAVL CreateAVL(void)
{
    return NULL;
}

bool IsEmpty(TAVL tree)
{
    return tree == NULL;
}

TAVL CreateLeaf(int value, TMemory* Memory)
{
    TAVL new = AVLAllocate(Memory);

    new->Height = 1;
    new->HeightDifference = 0;
    new->Value = value;
    new->Left = NULL;
    new->Right = NULL;

    return new;
}

int GetHeight(TAVL tree)
{
    if(IsEmpty(tree))
    {
        return 0;
    }
    return tree->Height;
}

int GetHeightDifference(TAVL tree)
{
    if(IsEmpty(tree))
    {
        return 0;
    }
    return tree->HeightDifference;
}

int Max(int X, int Y)
{
    return X >= Y ? X : Y;
}

void FixHeight(TAVL tree)
{
    tree->Height = Max(GetHeight(tree->Left), GetHeight(tree->Right)) + 1;
    tree->HeightDifference = GetHeight(tree->Right) - GetHeight(tree->Left);
}

TAVL RotateRight(TAVL tree)
{
    TAVL buffer = tree->Left;
    tree->Left = buffer->Right;
    buffer->Right = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

TAVL RotateLeft(TAVL tree)
{
    TAVL buffer = tree->Right;
    tree->Right = buffer->Left;
    buffer->Left = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

TAVL Balance(TAVL tree)
{
    FixHeight(tree);

    if(GetHeightDifference(tree) == 2)
    {
        if(GetHeightDifference(tree->Right) < 0)
        {
            tree->Right = RotateRight(tree->Right);
        }
        return RotateLeft(tree);
    }
    else if(GetHeightDifference(tree) == -2)
    {
        if(GetHeightDifference(tree->Left) > 0)
        {
            tree->Left = RotateLeft(tree->Left);
        }
        return RotateRight(tree);
    }

    return tree;
}

void Insert(int value, TAVL* tree, TMemory* memory)
{
    if(IsEmpty(*tree))
    {
        *tree = CreateLeaf(value, memory);
    }
    else if(value < (*tree)->Value)
    {
        Insert(value, &(*tree)->Left, memory);
    }
    else
    {
        Insert(value, &(*tree)->Right, memory);
    }

    *tree = Balance(*tree);
}

///////////////////////////// INPUT /////////////////////////////

int InputTreeSize(void)
{
    int treeSize = 0;
    int control = scanf("%d", &treeSize);
    UNUSED(control);
    assert(control == 1);
    return treeSize;
}

TAVL InputTree(int treeSize, TMemory* memory)
{
    TAVL tree = CreateAVL();

    for(int i = 0; i < treeSize; ++i)
    {
        int value = 0;
        int control = scanf("%d", &value);
        UNUSED(control);
        assert(control == 1);
        Insert(value, &tree, memory);
    }

    return tree;
}

///////////////////////////// MAIN /////////////////////////////

int main(void)
{
    int count = InputTreeSize();

    TMemory Memory = CreateMemory(count);

    TAVL tree = InputTree(count, &Memory);
    printf("%d", GetHeight(tree));

    DestroyMemory(&Memory);

    return EXIT_SUCCESS;
}