#include "prim.h"

static int CompareUInt(const unsigned int* a, const unsigned int* b)
{
    return (*a > *b) ? 1 : (*a == *b) ? 0 : -1;
}

TGraph PrimAlgorithm(TGraph* graph)
{
    TGraph MST = CreateGraph(graph->VertexCount);

    int* parents = calloc(graph->VertexCount, sizeof(*parents));
    if (parents == NULL)
    {
        OtherError(__FILE__, __LINE__);
    }

    bool* extracted = calloc(graph->VertexCount, sizeof(*extracted));
    if (extracted == NULL)
    {
        OtherError(__FILE__, __LINE__);
    }

    unsigned int defaultValue = UINT_MAX;
    unsigned int nullValue = 0;

    THeap heap = InitHeap(graph->VertexCount, sizeof(unsigned int), &defaultValue);
    AssignHeap(sizeof(unsigned int), &nullValue, heap.Key);

    int vertex = ExtractMin(&heap, CompareUInt);
    extracted[vertex - 1] = true;
    
    while (!IsEmptyHeap(heap))
    {
        for (int i = 0; i < graph->VertexCount; ++i)
        {
            if (extracted[i])
            {
                continue;
            }

            unsigned int length = GetLengthGraph(i + 1, vertex, *graph);
            if (length == 0)
            {
                continue;
            } 

            if (CompareUInt(&length, GetNthKeyHeap(heap, i)) < 0)
            {
                parents[i] = vertex;
                AssignHeap(sizeof(unsigned int), &length, GetNthKeyHeap(heap, i));

                int index = FindVertexIndex(i + 1, heap);
                if (index == -1)
                {
                    free(parents);
                    free(extracted);
                    DestroyHeap(&heap);
                    DestroyGraph(&MST);
                    DestroyGraph(graph);
                    OtherError(__FILE__, __LINE__);
                }

                SiftUp(index, &heap, CompareUInt);
            }
        } 

        vertex = ExtractMin(&heap, CompareUInt);
        extracted[vertex - 1] = true;   

        if (parents[vertex - 1] == 0)
        {
            free(parents);
            free(extracted);
            DestroyHeap(&heap);
            DestroyGraph(&MST);
            DestroyGraph(graph);
            NoSpanningTreeError();
        }

        PushEdge(vertex, parents[vertex - 1], 1, &MST);
    }
    
    free(parents);
    free(extracted);
    DestroyHeap(&heap);

    return MST;
}