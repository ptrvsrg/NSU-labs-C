#include "prim.h"

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

    THeap heap = CreateHeap(graph->VertexCount);
    InitHeap(&heap);
    heap.Key[0] = 0;

    int vertex = ExtractMin(&heap);
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

            if (length < heap.Key[i])
            {
                parents[i] = vertex;
                heap.Key[i] = length;

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

                SiftUp(index, &heap);
            }
        } 

        vertex = ExtractMin(&heap);
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
