#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////// ADDITIONAL FUNCTION /////////////////////////////

int Max(int X, int Y)
{
    return X >= Y ? X : Y;
}

///////////////////////////// MEMORY FUNCTION /////////////////////////////

typedef struct TAVL* TAVL;
struct TAVL
{
    int Value;
    int Height;
    TAVL Left;
    TAVL Right;
};

typedef struct TMemory
{
    int Count;
    int Index;
    TAVL Buffer;
} TMemory;

static TMemory Memory = { 0, 0, NULL };

void CreateMemory(int count)
{
    Memory.Count = count;
    Memory.Index = 0; 

    Memory.Buffer = calloc(count, sizeof(*Memory.Buffer));
    assert(Memory.Buffer != NULL);
}

TAVL AVLAllocate(void)
{
    assert(Memory.Count != Memory.Index);
    ++Memory.Index;
    return &Memory.Buffer[Memory.Index - 1];
}

void DestroyMemory(void)
{
    free(Memory.Buffer);
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

TAVL CreateLeaf(int value, TAVL left, TAVL right)
{
    TAVL new = AVLAllocate();

    new->Height = 1;
    new->Value = value;
    new->Left = left;
    new->Right = right;

    return new;
}

int GetHeight(TAVL tree)
{
    return !IsEmpty(tree) ? tree->Height : 0;
}

int HeightDifference(TAVL tree)
{
    return GetHeight(tree->Right) - GetHeight(tree->Left);
}

void FixHeight(TAVL tree)
{
    tree->Height = Max(GetHeight(tree->Left), GetHeight(tree->Right)) + 1;
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
    
    if(HeightDifference(tree) == 2)
    {
        if(HeightDifference(tree->Right) < 0)
        {
            tree->Right = RotateRight(tree->Right);
        }
        return RotateLeft(tree);
    }
    else if(HeightDifference(tree) == -2)
    {
        if(HeightDifference(tree->Left) > 0)
        {
            tree->Left = RotateLeft(tree->Left);
        }
        return RotateRight(tree);
    }

    return tree;
}

void Insert(int value, TAVL* tree)
{
    if(IsEmpty(*tree)) 
    {
        *tree = CreateLeaf(value, NULL, NULL);
    }
    else if(value < (*tree)->Value)   
    {
        Insert(value, &(*tree)->Left);
    }
    else
    {
        Insert(value, &(*tree)->Right);
    }

    *tree = Balance(*tree);
}

///////////////////////////// INPUT /////////////////////////////

int InputTreeSize(void)
{
    int treeSize = 0;
    assert(scanf("%d", &treeSize) == 1);
    return treeSize;
}

TAVL InputTree(int treeSize)
{
    TAVL tree = CreateAVL();

    for(int i = 0; i < treeSize; ++i)
    {
        int value = 0;
        assert(scanf("%d", &value) == 1);
        Insert(value, &tree);
    }

    return tree;
}

///////////////////////////// MAIN /////////////////////////////

int main(void)
{
    int count = InputTreeSize();

    CreateMemory(count);

    TAVL tree = InputTree(count);
    printf("%d", GetHeight(tree));

    DestroyMemory();
}