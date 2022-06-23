#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#define MAX_VERTEX_COUNT (int)2000

static int MaxEdgeCount(int vertexCount)
{
    return vertexCount * (vertexCount - 1) / 2;
}

TGraph CreateGraph(int vertexCount)
{
    TMatrix matrix = { vertexCount, NULL };
    TGraph graph = { vertexCount, matrix };
    graph.Matrix = CreateMatrix(vertexCount);
    return graph;
}

bool IsEdgeExists(int start, int end, TGraph graph)
{
    return GetMatrixValue(start - 1, end - 1, graph.Matrix);
}

void PushEdge(int start, int end, TGraph* graph)
{
    AddMatrixValue(start - 1, end - 1, &graph->Matrix);
}

void DestroyGraph(TGraph* graph)
{
    DestroyMatrix(&graph->Matrix);
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

    PushEdge(start, end, graph);
    return true;
}

TGraph InputGraph(void)
{
    int vertexCount = InputVertexCount();

    int edgeCount = InputEdgeCount(vertexCount);

    TGraph graph = CreateGraph(vertexCount);

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
