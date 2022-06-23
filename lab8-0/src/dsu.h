#ifndef DSU_H
#define DSU_H

#include <stdlib.h>
#include "error.h"

typedef struct TDSU
{
    int* Parent;
    int* Depth;
} TDSU;

TDSU CreateDSU(int vertexCount);
int FindSet(int vertexNum, TDSU* dsu);
void MergeSet(int vertexNum1, int vertexNum2, TDSU* dsu);
void DestroyDSU(TDSU* dsu);

#endif