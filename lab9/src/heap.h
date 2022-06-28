#ifndef HEAP_H
#define HEAP_H

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "error.h"

typedef struct THeap
{
    int Count;
    int Max;
    int* Vertex;
    uint64_t* Key;
} THeap;

THeap CreateHeap(int max);
void InitHeap(THeap* heap);
bool IsEmptyHeap(THeap heap);
void SiftDown(int index, THeap* heap);
void SiftUp(int index, THeap* heap);
int ExtractMin(THeap* heap);
int FindVertexIndex(int vertexNum, THeap heap);
void DestroyHeap(THeap* heap);

#endif
