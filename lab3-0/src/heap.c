#define _CRT_SECURE_NO_WARNINGS
#include "heap.h"

static THeap CreateHeap(int max)
{
    THeap heap;
    heap.Count = 0;
    heap.Max = max;
    heap.Key = NULL;

    if (max > 0)
    {
        heap.Key = malloc(max * sizeof(int));
        if (heap.Key == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return heap;
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

static bool IsEmptyHeap(THeap heap)
{
    return heap.Count == 0;
}

static bool HeapOverflow(THeap heap)
{
    return heap.Count >= heap.Max;
}

static void SiftDown(int index, THeap* heap)
{
    while(true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestChild = index;

        if (leftChild < heap->Count && heap->Key[leftChild] < heap->Key[largestChild])
        {
            largestChild = leftChild;
        }

        if (rightChild < heap->Count && heap->Key[rightChild] < heap->Key[largestChild])
        {
            largestChild = rightChild;
        }

        if (largestChild == index) 
        {
            break;
        }

        Swap(heap->Key + index, heap->Key + largestChild, sizeof(int));
        index = largestChild;
    }
}

static void SiftUp(int index, THeap* heap)
{
    while (true)
    {
        int parent = (index - 1) / 2;

        if (heap->Key[index] >= heap->Key[parent])
        {
            break;
        }

        Swap(heap->Key + index, heap->Key + parent, sizeof(int));
        index = parent;
    }
}

static int ExtractMin(THeap* heap)
{
    if (IsEmptyHeap(*heap))
    {
        OtherError(__FILE__, __LINE__);
    }
    
    int result = *(heap->Key);
    Swap(heap->Key, heap->Key + heap->Count - 1, sizeof(int));
    --heap->Count;
    SiftDown(0, heap);

    return result;
}

static void PushHeap(int value, THeap* heap)
{
    if (HeapOverflow(*heap))
    {
        OtherError(__FILE__, __LINE__);
    }

    ++heap->Count;
    heap->Key[heap->Count - 1] = value;
    SiftUp(heap->Count - 1, heap);
}

static int InputHeapCount(void)
{
    int count = 0;
    if (scanf("%d", &count) == EOF)
    {
        OtherError(__FILE__, __LINE__);
    }

    return count;
}

THeap InputHeap(void)
{
    int max = InputHeapCount();
    THeap heap = CreateHeap(max);

    for (int i = 0; i < max; ++i)
    {
        int value = 0;
        if (scanf("%d", &value) == EOF)
        {
            DestroyHeap(&heap);
            OtherError(__FILE__, __LINE__);
        }

        PushHeap(value, &heap);
    }

    return heap;
} 

void OutputHeap(THeap heap)
{
    int count = heap.Count;
    for (int i = 0; i < count; ++i)
    {
        printf("%d ", ExtractMin(&heap));
    }
}

void DestroyHeap(THeap* heap)
{
    free(heap->Key);
    *heap = CreateHeap(0);
}
