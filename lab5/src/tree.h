#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"

struct Ttree
{
    char Symbol;
    struct Ttree* Left;
    struct Ttree* Right;
};

typedef struct Ttree* TTree;

TTree CreateTree(char value, TTree left, TTree right);
TTree CreateLeaf(char value);
TTree CloneTree(TTree tree);
bool IsEmptyTree(TTree tree);
bool IsLeaf(TTree tree);
int CountLeaf(TTree tree);
void DestroyTree(TTree* tree);

#endif 
