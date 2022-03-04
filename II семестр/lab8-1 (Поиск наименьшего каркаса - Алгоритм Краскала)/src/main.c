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

int CompareEdge(const void* a, const void* b)
{
    const TEdge* A = a;
    const TEdge* B = b;
    return A->Length - B->Length;
}

///////////////////////////////////  DISJOINT SET UNION  ///////////////////////////////////

typedef struct TDSU
{
    short* Parent;
    short* Depth;
} TDSU;

TDSU CreateDSU(int vertexCount)
{
    TDSU dsu = { NULL, NULL };

    dsu.Parent = malloc(vertexCount * sizeof(*dsu.Parent));
    assert(dsu.Parent != NULL);

    for (int i = 0; i < vertexCount; ++i)
    {
        dsu.Parent[i] = i + 1;
    }

    dsu.Depth = calloc(vertexCount, sizeof(*dsu.Depth));
    assert(dsu.Depth != NULL);

    return dsu;
}

short FindSet(int vertexNum, TDSU* dsu)
{
    if (dsu->Parent[vertexNum - 1] != vertexNum)
    {
        dsu->Parent[vertexNum - 1] = FindSet(dsu->Parent[vertexNum - 1], dsu);
    }

    return dsu->Parent[vertexNum - 1];
}

void MergeSet(int vertexNum1, int vertexNum2, TDSU* dsu)
{
    int set1 = FindSet(vertexNum1, dsu);
    int set2 = FindSet(vertexNum2, dsu);

    if (set1 == set2)
    {
        return;
    }

    if (dsu->Depth[set1 - 1] < dsu->Depth[set2 - 1])
    {
        dsu->Parent[set1 - 1] = set2;
    }
    else
    {
        dsu->Parent[set2 - 1] = set1;

        if (dsu->Depth[set1 - 1] == dsu->Depth[set2 - 1])
        {
            ++dsu->Depth[set1 - 1];
        }
    }
}

void DestroyDSU(TDSU* dsu)
{
    free(dsu->Parent);
    free(dsu->Depth);
}

///////////////////////////////////  KRUSKAL ALGORITHM  ///////////////////////////////////

void KruskalAlgorithm(TGraph* graph, TGraph* MST)
{
    qsort(graph->Edges, graph->EdgeIndex, sizeof(TEdge), CompareEdge);

    TDSU dsu = CreateDSU(graph->VertexCount);

    for (int i = 0; i < graph->EdgeIndex; ++i)
    {
        int set1 = FindSet(graph->Edges[i].Begin, &dsu);
        int set2 = FindSet(graph->Edges[i].End, &dsu);

        if (set1 != set2)
        {
            AddEdge(graph->Edges[i], MST);
            MergeSet(set1, set2, &dsu);
        }
    }

    DestroyDSU(&dsu);

    if (MST->EdgeIndex != MST->VertexCount - 1)
    {
        DestroyGraph(graph);
        DestroyGraph(MST);
        NoSpanningTreeError();
    }
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    if (setjmp(position) == 0)
    {
        int vertexCount = InputVertexCount();
        int edgeCount = InputEdgeCount(vertexCount);
        TGraph graph = InputGraph(vertexCount, edgeCount);

        TGraph MST = CreateGraph(graph.VertexCount, graph.VertexCount - 1);
        KruskalAlgorithm(&graph, &MST);
        OutputGraph(MST);

        DestroyGraph(&graph);
        DestroyGraph(&MST);
    }

    return EXIT_SUCCESS;
}