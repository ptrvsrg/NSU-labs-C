#include "priority_list.h"

TList CreateList(void)
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

void PushList(TTree tree, int frequency, TList* list)
{
    if (IsEmptyList(*list) || frequency <= (*list)->Frequency)
    {
        TList new = malloc(sizeof(*new));
        if (new == NULL)
        {
            ExitWithError(__FILE__, __LINE__);
        }

        new->Tree = tree;
        new->Frequency = frequency;
        new->Next = *list;
        *list = new;
    }
    else
    {
        PushList(tree, frequency, &(*list)->Next);
    }
}

TTree PopList(TList* list)
{
    if (IsEmptyList(*list))
    {
        ExitWithError(__FILE__, __LINE__);
    }

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
        *list = NULL;
    }
}
