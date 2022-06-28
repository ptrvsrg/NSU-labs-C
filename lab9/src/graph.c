#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#define MAX_VERTEX_COUNT (int)5000

TGraph CreateGraph(int count)
{
    TMatrix matrix = CreateMatrix(count);
    TGraph graph = { count, matrix };
    return graph;
}

void PushEdge(int begin, int end, int length, TGraph* graph)
{
    PushMatrix(begin - 1, end - 1, length, &(graph->Matrix));
}

int GetLengthGraph(int begin, int end, TGraph graph)
{
    return GetValueMatrix(begin - 1, end - 1, graph.Matrix);
}

void PrintGraph(TGraph graph)
{
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (GetLengthGraph(i + 1, j + 1, graph) != 0)
            {
                printf("%d %d\n", j + 1, i + 1);
            }
        }
    }
}

void DestroyGraph(TGraph* graph)
{
    DestroyMatrix(&(graph->Matrix));
    *graph = CreateGraph(0);
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

static int MaxEdgeCount(int vertexCount)
{
    return vertexCount * (vertexCount - 1) / 2;
}

static int InputEdgeCount(int vertexCount)
{
    int edgeCount = 0;
    if (scanf("%d", &edgeCount) == EOF)
    {
        BadNumberOfLinesError();
    }

    if (edgeCount < 0 || edgeCount > MaxEdgeCount(vertexCount))
    {
        BadNumberOfEdgesError();
    }

    return edgeCount;
}

static int InputVertexNumber(int vertexCount)
{
    int vertexNum = 0;
    if (scanf("%d", &vertexNum) == EOF)
    {
        BadNumberOfLinesError();
    }
    if (vertexNum <= 0 || vertexNum > vertexCount)
    {
        BadVertexError();
    }

    return vertexNum;
}

static bool InputEdge(int vertexCount, TGraph* graph)
{
    int start = 0;
    if (scanf("%d", &start) == EOF)
    {
        return false;
    }
    if (start <= 0 || start > vertexCount)
    {
        DestroyGraph(graph);
        BadVertexError();
    }

    int end = 0;
    if (scanf("%d", &end) == EOF)
    {
        return false;
    }
    if (end <= 0 || end > vertexCount)
    {
        DestroyGraph(graph);
        BadVertexError();
    }

    int length = 0;
    if (scanf("%d", &length) == EOF)
    {
        return false;
    }
    if (length < 0)
    {
        DestroyGraph(graph);
        BadLengthError();
    }

    PushEdge(start, end, length, graph);
    return true;
}

TGraph InputGraph(int* beginVertex, int* endVertex)
{
    int vertexCount = InputVertexCount();

    *beginVertex = InputVertexNumber(vertexCount);
    *endVertex = InputVertexNumber(vertexCount);

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
