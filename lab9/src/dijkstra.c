#include "dijkstra.h"

uint64_t* DijkstraAlgorithm(int beginVertex, TGraph graph)
{
    bool* extracted = calloc(graph.VertexCount, sizeof(*extracted));
    if (extracted == NULL)
    {
        OtherError(__FILE__, __LINE__);
    }

    uint64_t* paths = calloc(graph.VertexCount, sizeof(*paths));
    if (paths == NULL)
    {
        OtherError(__FILE__, __LINE__);
    }

    for (int i = 0; i < graph.VertexCount; ++i)
    {
        if (i != beginVertex - 1)
        {
            paths[i] = UINT64_MAX;
        }
    }

    THeap heap = CreateHeap(graph.VertexCount);
    InitHeap(&heap);
    heap.Key[beginVertex - 1] = 0;
    SiftUp(beginVertex - 1, &heap);

    int vertex = ExtractMin(&heap);
    extracted[vertex - 1] = true;
    
    while (!IsEmptyHeap(heap))
    {
        for (int i = 0; i < graph.VertexCount; ++i)
        {
            if (extracted[i])
            {
                continue;
            }

            unsigned int length = GetLengthGraph(i + 1, vertex, graph);
            if (length == 0)
            {
                continue;
            } 

            if (heap.Key[vertex - 1] + length < heap.Key[i])
            {
                heap.Key[i] = heap.Key[vertex - 1] + length;
                paths[i] = heap.Key[vertex - 1] + length;

                int index = FindVertexIndex(i + 1, heap);
                if (index == -1)
                {
                    free(paths);
                    free(extracted);
                    DestroyHeap(&heap);
                    DestroyGraph(&graph);
                    OtherError(__FILE__, __LINE__);
                }

                SiftUp(index, &heap);
            }
        } 

        vertex = ExtractMin(&heap);
        extracted[vertex - 1] = true;
    }

    free(extracted);
    DestroyHeap(&heap);

    return paths;
}
