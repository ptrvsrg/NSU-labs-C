#include "tree.h"

TTree CreateTree(char value, TTree left, TTree right)
{
    TTree tree = malloc(sizeof(*tree));
    if (tree == NULL)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    tree->Symbol = value;
    tree->Left = left;
    tree->Right = right;
    return tree;
}

TTree CreateLeaf(char value)
{
    return CreateTree(value, NULL, NULL);
}

TTree CloneTree(TTree tree)
{
    if (IsEmptyTree(tree))
    {
        return NULL;
    }

    return CreateTree(tree->Symbol, CloneTree(tree->Left), CloneTree(tree->Right));
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
