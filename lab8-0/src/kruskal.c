#include "kruskal.h"

TGraph KruskalAlgorithm(TGraph* graph)
{
    qsort(graph->Edges, graph->EdgeIndex, sizeof(TEdge), CompareEdge);

    TGraph MST = CreateGraph(graph->VertexCount, graph->VertexCount - 1);
    TDSU dsu = CreateDSU(graph->VertexCount);

    for (int i = 0; i < graph->EdgeIndex; ++i)
    {
        int set1 = FindSet(graph->Edges[i].Begin, &dsu);
        int set2 = FindSet(graph->Edges[i].End, &dsu);

        if (set1 != set2)
        {
            PushEdge(graph->Edges[i], &MST);
            MergeSet(set1, set2, &dsu);
        }
    }

    DestroyDSU(&dsu);

    if (MST.EdgeIndex != MST.VertexCount - 1)
    {
        DestroyGraph(graph);
        DestroyGraph(&MST);
        NoSpanningTreeError();
    }

    return MST;
}