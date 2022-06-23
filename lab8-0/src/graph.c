#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#define MAX_VERTEX_COUNT (int)5000

static int MaxEdgeCount(int vertexCount) 
{
    return vertexCount * (vertexCount - 1) / 2;
}

TGraph CreateGraph(int vertexCount, int edgeCount)
{
    TGraph graph = { 0, edgeCount, vertexCount, NULL };

    if (edgeCount > 0)
    {
        graph.Edges = calloc(edgeCount, sizeof(*graph.Edges));
        if (graph.Edges == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return graph;
}

static bool IsEmptyGraph(TGraph graph)
{
    return graph.Edges == NULL;
}

void PushEdge(TEdge edge, TGraph* graph)
{
    if (graph->EdgeIndex >= graph->EdgeCount)
    {
        DestroyGraph(graph);
        OtherError(__FILE__, __LINE__);
    }

    graph->Edges[graph->EdgeIndex] = edge;
    ++graph->EdgeIndex;
}

void DestroyGraph(TGraph* graph)
{
    free(graph->Edges);
    graph->Edges = NULL;
    graph->EdgeCount = 0;
    graph->EdgeIndex = 0;
    graph->VertexCount = 0;
}

static int InputVertexCount(void)
{
    int vertexCount = 0;
    if(scanf("%d", &vertexCount) == EOF)
    {
        BadNumberOfLinesError();
    }

    if (vertexCount < 0 || vertexCount > MAX_VERTEX_COUNT)
    {
        BadNumberOfVerticesError();
    }

    return vertexCount;
}

static int InputEdgeCount(int vertexCount)
{
    int edgeCount = 0;
    if(scanf("%d", &edgeCount) == EOF)
    {
        BadNumberOfLinesError();
    }

    if (edgeCount < 0 || edgeCount > MaxEdgeCount(vertexCount))
    {
        BadNumberOfEdgesError();
    }

    return edgeCount;
}

static bool InputEdge(int vertexCount, TGraph* graph)
{
    int start = 0;
    if(scanf("%d", &start) == EOF)
    {
        return false;
    }
    if (start <= 0 || start > vertexCount)
    {
        DestroyGraph(graph);
        BadVertexError();
    }

    int end = 0;
    if(scanf("%d", &end) == EOF)
    {
        return false;
    }
    if (end <= 0 || end > vertexCount)
    {
        DestroyGraph(graph);
        BadVertexError();
    }

    int length = 0;
    if(scanf("%d", &length) == EOF)
    {
        return false;
    }
    if (length < 0)
    {
        DestroyGraph(graph);
        BadLengthError();
    }

    TEdge edge = { start, end, length };
    PushEdge(edge, graph);
    return true;
}

TGraph InputGraph(void)
{
    int vertexCount = InputVertexCount();

    int edgeCount = InputEdgeCount(vertexCount);

    TGraph graph = CreateGraph(vertexCount, edgeCount);

    int edgeNum = 0;
    while (InputEdge(vertexCount, &graph))
    {
        ++edgeNum;
    }

    if (edgeNum != edgeCount)
    {
        DestroyGraph(&graph);
        BadNumberOfLinesError();
    }

    return graph;
}

void OutputGraph(TGraph graph)
{
    for (int i = 0; i < graph.EdgeIndex; ++i)
    {
        printf("%d %d\n", graph.Edges[i].Begin, graph.Edges[i].End);
    }
}

int CompareEdge(const void* a, const void* b)
{
    const TEdge* A = a;
    const TEdge* B = b;
    return A->Length - B->Length;
}
