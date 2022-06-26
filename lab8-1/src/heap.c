#include "heap.h"

THeap CreateHeap(int max, int size)
{
    THeap heap;
    heap.Count = 0;
    heap.Max = max;
    heap.Size = size;
    heap.Vertex = NULL;
    heap.Key = NULL;

    if (max > 0)
    {
        heap.Vertex = calloc(max, sizeof(int));
        if (heap.Vertex == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }

        heap.Key = calloc(max, size);
        if (heap.Key == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return heap;
}

THeap InitHeap(int max, int size, const void* defaultValue)
{
    THeap heap = CreateHeap(max, size);

    for (int i = 0; i < max; ++i)
    {
        heap.Vertex[i] = i + 1;
        AssignHeap(heap.Size, defaultValue, GetNthKeyHeap(heap, i));
        ++heap.Count;
    }

    return heap;
}

void AssignHeap(int size, const void* src, void* dest)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

static void Swap(void* value1, void* value2, int size)
{
    for (int i = 0; i < size; ++i)
    {
        char buffer = ((char*)value1)[i];
        ((char*)value1)[i] = ((char*)value2)[i];
        ((char*)value2)[i] = buffer;
    }
}

void* GetNthKeyHeap(THeap heap, int n)
{
    if (n >= heap.Max)
    {
        DestroyHeap(&heap);
        OtherError(__FILE__, __LINE__);
    }

    return (char*)heap.Key + n * heap.Size;
}

bool IsEmptyHeap(THeap heap)
{
    return heap.Count == 0;
}

void SiftDown(int index, THeap* heap, int (*compareKey)(const void*, const void*))
{
    while(true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestChild = index;

        if (leftChild < heap->Count && 
        compareKey(GetNthKeyHeap(*heap, heap->Vertex[leftChild] - 1), GetNthKeyHeap(*heap, heap->Vertex[largestChild] - 1)) < 0)
        {
            largestChild = leftChild;
        }

        if (rightChild < heap->Count && 
        compareKey(GetNthKeyHeap(*heap, heap->Vertex[rightChild] - 1), GetNthKeyHeap(*heap, heap->Vertex[largestChild] - 1)) < 0)
        {
            largestChild = rightChild;
        }

        if (largestChild == index) 
        {
            break;
        }

        Swap(heap->Vertex + index, heap->Vertex + largestChild, sizeof(int));
        index = largestChild;
    }
}

void SiftUp(int index, THeap* heap, int (*compareKey)(const void *, const void *))
{
    while (true)
    {
        int parent = (index - 1) / 2;
        int parentVertex = heap->Vertex[parent];
        int indexVertex = heap->Vertex[index];

        if (compareKey(GetNthKeyHeap(*heap, indexVertex - 1), GetNthKeyHeap(*heap, parentVertex - 1)) >= 0)
        {
            break;
        }

        Swap(heap->Vertex + index, heap->Vertex + parent, sizeof(int));
        index = parent;
    }
}

int ExtractMin(THeap* heap, int (*compareKey)(const void*, const void*))
{
    if  (IsEmptyHeap(*heap))
    {
        OtherError(__FILE__, __LINE__);
    }
    
    int result = *(heap->Vertex);
    Swap(heap->Vertex, heap->Vertex + heap->Count - 1, sizeof(int));
    --heap->Count;
    SiftDown(0, heap, compareKey);

    return result;
}

int FindVertexIndex(int vertexNum, THeap heap)
{
    for (int i = 0; i < heap.Count; ++i)
    {
        if (heap.Vertex[i] == vertexNum)
        {
            return i;
        }
    }
    
    return -1;
}

void DestroyHeap(THeap* heap)
{
    free(heap->Vertex);
    free(heap->Key);
    *heap = CreateHeap(0, 0);
}
