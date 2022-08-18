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

TTree CreateLeaf(char value);
TTree CreateTree(char value, TTree left, TTree right);
bool IsEmptyTree(TTree tree);
bool IsLeaf(TTree tree);
int CountLeaf(TTree tree);
void DestroyTree(TTree* tree);

#endif 
