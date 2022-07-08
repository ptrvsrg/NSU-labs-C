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
            DestroyList(list);
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

    TTree removeTree = CloneTree((*list)->Tree);
    TList removeItem = *list;
    *list = (*list)->Next;
    FreeElementList(&removeItem);
    return removeTree;
}

void FreeElementList(TList* item)
{
    if (!IsEmptyList(*item))
    {
        DestroyTree(&(*item)->Tree);
        free(*item);
        *item = NULL;
    }
}

void DestroyList(TList* list)
{
    if (!IsEmptyList(*list))
    {
        DestroyList(&(*list)->Next);
        FreeElementList(list);
    }
}
