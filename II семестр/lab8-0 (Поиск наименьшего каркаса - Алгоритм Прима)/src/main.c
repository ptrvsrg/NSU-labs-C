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

///////////////////////////////////  BINARY HEAP TYPE  ///////////////////////////////////

typedef struct
{
    short Count;
    short Max;
    int* DistanceToMST;
    int* Array;
} THeap;

void Swap(int* value1, int* value2)
{
	int buffer = *value1;
	*value1 = *value2;
	*value2 = buffer;
}

THeap CreateHeap(int max)
{
    THeap heap = { 0, max, NULL, NULL };

    heap.Array = calloc(max, sizeof(*heap.Array));
    assert(heap.Array != NULL);

    heap.DistanceToMST = calloc(max, sizeof(*heap.DistanceToMST));
    assert(heap.DistanceToMST != NULL);

    return heap;
}

void SiftDown(int index, THeap* heap)
{
    while (2 * index + 1 < heap->Count)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        int newIndex = (right < heap->Count && heap->DistanceToMST[heap->Array[right] - 1] < heap->DistanceToMST[heap->Array[left] - 1]) ? right : left;

        if (heap->Array[index] <= heap->Array[newIndex])
        {
            break;
        }

        Swap(&heap->Array[index], &heap->Array[newIndex]);

        index = newIndex;
    }
}

void SiftUp(int index, THeap* heap)
{
    while (heap->Array[index] < heap->Array[(index - 1) / 2])
    {
        Swap(&heap->Array[index], &heap->Array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int PopHeap(THeap* heap)
{
    assert(heap->Count != 0);
    int min = heap->Array[0];
    heap->Array[0] = heap->Array[heap->Count - 1];
    --heap->Count;
    SiftDown(0, heap);
    return min;
}

void PushHeap(int value, THeap* heap)
{
    assert(heap->Max != heap->Count);
    ++heap->Count;
    heap->Array[heap->Count - 1] = value;
    SiftUp(heap->Count - 1, heap);
}

void DestroyHeap(THeap* heap)
{
    free(heap->Array);
}

///////////////////////////////////  EDGE TYPE  ///////////////////////////////////

typedef struct
{
    short Begin;
    short End;
    int Length;
} TEdge;

///////////////////////////////////  GRAPH TYPE  ///////////////////////////////////

typedef struct
{
    int EdgeCount;
    int EdgeMax;
    int VertexCount;
    TEdge* Edges;
} TGraph;

TGraph CreateGraph(int vertexCount, int edgeMax)
{
    TGraph graph = { 0, edgeMax, vertexCount, NULL };

    graph.Edges = calloc(edgeMax, sizeof(*graph.Edges));
    assert(graph.Edges != NULL);

    return graph;
}

void AddEdge(TEdge edge, TGraph* graph)
{
    assert(graph->EdgeCount != graph->EdgeMax);
    graph->Edges[graph->EdgeCount] = edge;
    ++graph->EdgeCount;
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
    PushGraph(edge, graph);
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
    for (int i = 0; i < graph.EdgeCount; ++i)
    {
        printf("%d %d\n", graph.Edges[i].Begin, graph.Edges[i].End);
    }
}

///////////////////////////////////  PRIM ALGORITHM  ///////////////////////////////////

void PrimAlgorithm(TGraph* graph, TGraph* spanningTree)
{
    int* distanceToSpanningTree = calloc(graph->VertexCount, sizeof(*distanceToSpanningTree));
    assert(distanceToSpanningTree != NULL);

    for (int i = 0; i < graph->VertexCount; ++i)
    {
        distanceToSpanningTree[i] = INT_MAX;
    }

    
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    assert(freopen("in.txt", "r", stdin) != NULL);
    assert(freopen("out.txt", "w", stdout) != NULL);

    if (setjmp(position) == 0)
    {
        int vertexCount = InputVertexCount();
        int edgeCount = InputEdgeCount(vertexCount);
        TGraph graph = InputGraph(vertexCount, edgeCount);

        TGraph spanningTree = CreateGraph(graph.VertexCount, graph.VertexCount - 1);
        PrimAlgorithm(&graph, &spanningTree);
        OutputGraph(&spanningTree);

        DestroyGraph(&graph);
        DestroyGraph(&spanningTree);
    }

    fclose(stdin);
    fclose(stdout);

    return EXIT_SUCCESS;
}