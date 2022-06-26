#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"

typedef struct THeap
{
    int Count;
    int Max;
    int Size;
    int* Vertex;
    void* Key;
} THeap;

THeap CreateHeap(int max, int size);
THeap InitHeap(int max, int size, const void* defaultValue);
void AssignHeap(int size, const void* src, void* dest);
void* GetNthKeyHeap(THeap heap, int n);
bool IsEmptyHeap(THeap heap);
void SiftDown(int index, THeap* heap, int (*compareKey)(const void*, const void*));
void SiftUp(int index, THeap* heap, int (*compareKey)(const void *, const void *));
int ExtractMin(THeap* heap, int (*compareKey)(const void*, const void*));
int FindVertexIndex(int vertexNum, THeap heap);
void DestroyHeap(THeap* heap);

#endif
