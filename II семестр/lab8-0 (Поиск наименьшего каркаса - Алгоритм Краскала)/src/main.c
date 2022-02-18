#include <assert.h>
#include <limits.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGE_COUNT(vertexCount) vertexCount * (vertexCount - 1) / 2

static jmp_buf position;

enum
{
    SUCCESS_JUMP = 1,
    MAX_VERTEX_COUNT = 5000
};

///////////////////////////////////  EDGE TYPE  ///////////////////////////////////

typedef struct TEdge
{
    short Begin;
    short End;
    int Length;
} TEdge;

///////////////////////////////////  GRAPH TYPE  ///////////////////////////////////

typedef struct TGraph
{
    int EdgeIndex;
    int EdgeCount;
    int VertexCount;
    TEdge* Edges;
} TGraph;

TGraph CreateGraph(int vertexCount, int edgeCount)
{
    TGraph graph = { 0, edgeCount, vertexCount, NULL };

    graph.Edges = calloc(edgeCount, sizeof(*graph.Edges));
    assert(graph.Edges != NULL);

    return graph;
}

void AddEdge(TEdge edge, TGraph* graph)
{
    assert(graph->EdgeCount != graph->EdgeIndex);
    graph->Edges[graph->EdgeIndex] = edge;
    ++graph->EdgeIndex;
}

void DestroyGraph(TGraph* graph)
{
    free(graph->Edges);
}

///////////////////////////////////  ERRORS  ///////////////////////////////////

void BadNumberOfVerticesError(int vertexCount)
{
    if (vertexCount > MAX_VERTEX_COUNT)
    {
        printf("bad number of vertices");
        longjmp(position, SUCCESS_JUMP);
    }
}

void BadNumberOfEdgesError(int edgeCount, int vertexCount)
{
    if (edgeCount > MAX_EDGE_COUNT(vertexCount))
    {
        printf("bad number of edges");
        longjmp(position, SUCCESS_JUMP);
    }
}

void BadNumberOfLinesError(void)
{
    printf("bad number of lines");
    longjmp(position, SUCCESS_JUMP);
}

void BadVertexError(int vertexNum, int vertexCount, TGraph* graph)
{
    if (vertexNum <= 0 || vertexNum > vertexCount)
    {
        if (graph != NULL)
        {
            DestroyGraph(graph);
        }

        printf("bad vertex");
        longjmp(position, SUCCESS_JUMP);
    }
}

void BadLengthError(int edgeLength, TGraph* graph)
{
    if (edgeLength < 0 || edgeLength > INT_MAX)
    {
        printf("bad length");
        DestroyGraph(graph);
        longjmp(position, SUCCESS_JUMP);
    }
}

void NoSpanningTreeError(void)
{
    printf("no spanning tree");
    longjmp(position, SUCCESS_JUMP);
}

///////////////////////////////////  INPUT  ///////////////////////////////////

int InputVertexCount(void)
{
    int vertexCount = 0;
    if (scanf("%d", &vertexCount) != 1)
    {
        BadNumberOfLinesError();
    }
    BadNumberOfVerticesError(vertexCount);

    if (vertexCount == 0)
    {
        NoSpanningTreeError();
    }

    return vertexCount;
}

int InputEdgeCount(int vertexCount)
{
    int edgeCount = 0;
    if (scanf("%d", &edgeCount) != 1)
    {
        BadNumberOfLinesError();
    }
    BadNumberOfEdgesError(edgeCount, vertexCount);

    if (vertexCount > 1 && edgeCount == 0)
    {
        NoSpanningTreeError();
    }
    
    return edgeCount;
}

bool InputEdge(int vertexCount, TGraph* graph)
{
    int begin = 0;
    if (scanf("%d", &begin) != 1)
    {
        return false;
    }
    BadVertexError(begin, vertexCount, graph);

    int end = 0;
    if (scanf("%d", &end) != 1)
    {
        return false;
    }
    BadVertexError(end, vertexCount, graph);

    int length = 0;
    if (scanf("%d", &length) != 1)
    {
        return false;
    }
    BadLengthError(length, graph);

    TEdge edge = { begin, end, length };
    AddEdge(edge, graph);
    return true;
}

TGraph InputGraph(int vertexCount, int edgeCount)
{
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

///////////////////////////////////  OUTPUT  ///////////////////////////////////

void OutputGraph(TGraph graph)
{
    for (int i = 0; i < graph.EdgeIndex; ++i)
    {
        printf("%d %d\n", graph.Edges[i].Begin, graph.Edges[i].End);
    }
}

///////////////////////////////////  FUNCTION FOR QSORT  ///////////////////////////////////

int Compare(const void* a, const void* b)
{
    const TEdge* A = a;
    const TEdge* B = b;
    return A->Length - B->Length;
}

///////////////////////////////////  KRUSKAL ALGORITHM  ///////////////////////////////////

int FindEdge(bool* added, TGraph graph)
{
    for (int i = 0; i < graph.EdgeIndex; ++i)
    {
        bool begin = added[graph.Edges[i].Begin - 1];
        bool end = added[graph.Edges[i].End - 1];

        if ((!begin && end) || (begin && !end))
        {
            return i + 1;
        }
    }

    return 0;
}

void AddEdgeToSpanningTree(bool* added, TEdge edge, TGraph* spanningTree)
{
    AddEdge(edge, spanningTree);
    added[edge.Begin - 1] = true;
    added[edge.End - 1] = true;
}

bool ConnectivityCheck(int vertexCount, bool* added)
{
    for (int i = 0; i < vertexCount; ++i)
    {
        if (!added[i])
        {
            return false;
        }
    }

    return true;
}

void KruskalAlgorithm(TGraph* graph, TGraph* spanningTree)
{
    qsort(graph->Edges, graph->EdgeIndex, sizeof(TEdge), Compare);

    if (graph->VertexCount == 1)
    {
        return;
    }

    bool* added = calloc(graph->VertexCount, sizeof(*added));
    assert(added != NULL);

    int vertexNum = 1;

    do
    {
        AddEdgeToSpanningTree(added, graph->Edges[vertexNum - 1], spanningTree);
        vertexNum = FindEdge(added, *graph);
    } while(vertexNum != 0);

    if (!ConnectivityCheck(graph->VertexCount, added))
    {
        free(added);
        DestroyGraph(graph);
        DestroyGraph(spanningTree);
        NoSpanningTreeError();
    }

    free(added);
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    if (setjmp(position) == 0)
    {
        int vertexCount = InputVertexCount();
        int edgeCount = InputEdgeCount(vertexCount);
        TGraph graph = InputGraph(vertexCount, edgeCount);

        TGraph spanningTree = CreateGraph(graph.VertexCount, graph.VertexCount - 1);
        KruskalAlgorithm(&graph, &spanningTree);
        OutputGraph(spanningTree);

        DestroyGraph(&graph);
        DestroyGraph(&spanningTree);
    }

    return EXIT_SUCCESS;
}