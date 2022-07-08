#include "tree.h"

TTree CreateLeaf(char value)
{
    TTree tree = malloc(sizeof(*tree));
    if (tree == NULL)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    tree->Symbol = value;
    tree->Left = NULL;
    tree->Right = NULL;
    return tree;
}

TTree CreateTree(char value, TTree left, TTree right)
{
    TTree tree = CreateLeaf(value);
    tree->Left = left;
    tree->Right = right;
    
    return tree;
}

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

bool IsLeaf(TTree tree)
{
    return !IsEmptyTree(tree) && IsEmptyTree(tree->Left) && IsEmptyTree(tree->Right);
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
        *tree = NULL;
    }
}
