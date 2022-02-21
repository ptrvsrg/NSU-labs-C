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

int SumArithmeticProgression(int begin, int end, int count)
{
    return (begin + end) * count / 2;
}

///////////////////////////////////  BINARY HEAP TYPE  ///////////////////////////////////

typedef struct
{
    short Count;
    short MaxCount;
    unsigned int* Distance;
    int* Vertices;
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

    heap.Vertices = calloc(max, sizeof(*heap.Vertices));
    assert(heap.Vertices != NULL);

    heap.Distance = calloc(max, sizeof(*heap.Distance));
    assert(heap.Distance != NULL);

    return heap;
}

THeap BuildHeap(int vertexCount)
{
    THeap heap = CreateHeap(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        heap.Vertices[i] = i + 1;
        heap.Distance[i] = UINT_MAX;
        ++heap.Count;
    }

    return heap;
}

bool IsEmptyHeap(THeap heap)
{
    return heap.Count == 0;
}

void SiftUp(int index, THeap* heap)
{
    int vertex = heap->Vertices[index];
    int parentVertex = heap->Vertices[(index - 1) / 2];

    while (heap->Distance[vertex - 1] < heap->Distance[parentVertex - 1])
    {
        Swap(&heap->Vertices[index], &heap->Vertices[(index - 1) / 2]);
        index = (index - 1) / 2;
        vertex = heap->Vertices[index];
        parentVertex = heap->Vertices[(index - 1) / 2];
    }
}

void SiftDown(int index, THeap* heap)
{
    while (2 * index + 1 < heap->Count)
    {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int leftVertex = heap->Vertices[leftIndex];
        int rightVertex = heap->Vertices[rightIndex];

        int newIndex = (rightIndex < heap->Count && heap->Distance[rightVertex - 1] < heap->Distance[leftVertex - 1]) ? rightIndex : leftIndex;

        int indexVertex = heap->Vertices[index];
        int newIndexVertex = heap->Vertices[newIndex];

        if (heap->Distance[indexVertex - 1] <= heap->Distance[newIndexVertex - 1])
        {
            return;
        }

        Swap(&heap->Vertices[index], &heap->Vertices[newIndex]);

        index = newIndex;
    }
}

int PopHeap(THeap* heap)
{
    assert(heap->Count != 0);
    int min = heap->Vertices[0];
    heap->Vertices[0] = heap->Vertices[heap->Count - 1];
    --heap->Count;
    SiftDown(0, heap);
    return min;
}

int FindVertex(int vertex, THeap heap)
{
    for (int i = 0; i < heap.Count; ++i)
    {
        if (heap.Vertices[i] == vertex)
        {
            return i;
        }
    }
    
    return -1;
}

void DecreaseDistance(int vertexNum, int newLength, THeap* heap)
{
    assert(vertexNum <= heap->MaxCount);
    heap->Distance[vertexNum - 1] = newLength;
    int index = FindVertex(vertexNum, *heap);
    assert(index != -1);
    SiftUp(index, heap);
}

void DestroyHeap(THeap* heap)
{
    free(heap->Vertices);
    free(heap->Distance);
}

///////////////////////////////////  MATRIX TYPE  ///////////////////////////////////

int* CreateMatrix(int count)
{
    int* matrix = calloc(SumArithmeticProgression(1, count, count), sizeof(*matrix));
    assert(matrix != NULL);
    return matrix;
}

void AddMatrixValue(int row, int column, int size, int length, int* matrix)
{
    int min = (row >= column) ? column : row;
    int max = (row < column) ? column : row;

    assert(matrix[SumArithmeticProgression(size, size - min + 1, min) + (max - min)] == 0);
    matrix[SumArithmeticProgression(size, size - min + 1, min) + (max - min)] = length;
}

int GetMatrixValue(int row, int column, int size, int* matrix)
{
    int min = (row >= column) ? column : row;
    int max = (row < column) ? column : row;

    return matrix[SumArithmeticProgression(size, size - min + 1, min) + (max - min)];
}

void DestroyMatrix(int* matrix)
{
    free(matrix);
}

///////////////////////////////////  GRAPH TYPE  ///////////////////////////////////

typedef struct 
{
    int VertexCount;
    int* AdjMatrix;
} TGraph;

TGraph CreateGraph(int vertexCount)
{
    TGraph graph = { vertexCount, NULL };
    graph.AdjMatrix = CreateMatrix(vertexCount);
    return graph;
}

void PushEdge(int begin, int end, int length, TGraph* graph)
{
    AddMatrixValue(begin - 1, end - 1, graph->VertexCount, length, graph->AdjMatrix);
}

int GetEdgeLength(int begin, int end, TGraph* graph)
{
    return GetMatrixValue(begin - 1, end - 1, graph->VertexCount, graph->AdjMatrix);
}

void DestroyGraph(TGraph* graph)
{
    DestroyMatrix(graph->AdjMatrix);
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

    PushEdge(begin, end, length, graph);
    return true;
}

TGraph InputGraph(int vertexCount, int edgeCount)
{
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

///////////////////////////////////  OUTPUT  ///////////////////////////////////

void OutputGraph(int vertexCount, int* parent)
{
    for (int i = 1; i < vertexCount; ++i)
    {
        int min = (parent[i] >= i + 1) ? i + 1 : parent[i];
        int max = (parent[i] < i + 1) ? i + 1 : parent[i];
        printf("%d %d\n", min, max);
    }
}

///////////////////////////////////  PRIM ALGORITHM  ///////////////////////////////////

bool ConnectivityCheck(int vertexCount, int* parents)
{
    for (int i = 1; i < vertexCount; ++i)
    {
        if (parents[i] == 0)
        {
            return false;
        }
    }

    return true;
}

int* PrimAlgorithm(TGraph* graph)
{
    int* parents = calloc(graph->VertexCount, sizeof(*parents));
    assert(parents != NULL);

    bool* deleted = calloc(graph->VertexCount, sizeof(*deleted));
    assert(deleted != NULL);

    THeap heap = BuildHeap(graph->VertexCount);
    heap.Distance[0] = 0;

    while (!IsEmptyHeap(heap))
    {
        int dadVertex = PopHeap(&heap);
        deleted[dadVertex - 1] = true;

        for (int i = 0; i < graph->VertexCount; ++i)
        {
            int length = GetEdgeLength(i + 1, dadVertex, graph);

            if (length != 0 && !deleted[i] && (unsigned int)length < heap.Distance[i])
            {
                DecreaseDistance(i + 1, length, &heap);
                parents[i] = dadVertex;
            }
        }        
    }

    free(deleted);
    DestroyHeap(&heap);

    if (!ConnectivityCheck(graph->VertexCount, parents))
    {
        free(parents);
        DestroyGraph(graph);
        NoSpanningTreeError();
    }

    return parents;
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    if (setjmp(position) == 0)
    {
        int vertexCount = InputVertexCount();
        int edgeCount = InputEdgeCount(vertexCount);
        TGraph graph = InputGraph(vertexCount, edgeCount);

        int* parents = PrimAlgorithm(&graph);
        OutputGraph(vertexCount, parents);

        DestroyGraph(&graph);
        free(parents);
    }

    return EXIT_SUCCESS;
}