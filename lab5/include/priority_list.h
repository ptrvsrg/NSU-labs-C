#ifndef PRIORITY_LIST_H
#define PRIORITY_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "tree.h"

struct Tlist
{
    int Frequency;
    TTree Tree;
    struct Tlist* Next;
};

typedef struct Tlist* TList;

TList CreateList(void);
bool IsEmptyList(TList list);
void PushList(TTree tree, int frequency,  TList* list);
TTree PopList(TList* list);
void DestroyList(TList* list);

#endif
