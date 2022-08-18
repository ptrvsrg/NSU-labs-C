#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

typedef struct TAVL
{
    char Height;
    char HeightDifference;
    int Value;
    struct TAVL* Left;
    struct TAVL* Right;
} TAVL;

typedef struct TAVL* TAVLPtr;

TAVLPtr AVLAllocate(TMemory* memory);
TAVLPtr CreateAVL(void);
TAVLPtr CreateLeaf(int value, TMemory* memory);
bool IsEmpty(TAVLPtr tree);
char GetHeight(TAVLPtr tree);
void Insert(int value, TAVLPtr* tree, TMemory* memory);
TAVLPtr InputTree(int treeSize, TMemory* memory);

#endif
