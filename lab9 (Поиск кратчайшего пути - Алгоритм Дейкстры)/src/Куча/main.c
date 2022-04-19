#include <assert.h>
#include <limits.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGE_COUNT(vertexCount) vertexCount * (vertexCount - 1) / 2

static jmp_buf position;

enum
{
    SUCCESS_JUMP = 1,
    MAX_VERTEX_COUNT = 5000
};

///////////////////////////////////  ADDITIONAL FUNCTION  ///////////////////////////////////

int SumArithmeticProgression(int begin, int end, int count)
{
    return (begin + end) * count / 2;
}

void Swap(void* value1, void* value2, int size)
{
    char* buffer1 = value1;
    char* buffer2 = value2;

    for (int i = 0; i < size; ++i)
    {
        char tmp = buffer1[i];
        buffer1[i] = buffer2[i];
        buffer2[i] = tmp;
    }
}

int Min(int a, int b)
{
    return (a < b) ? a : b;
}

int Max(int a, int b)
{
    return (a < b) ? b : a;
}

///////////////////////////////////  BINARY HEAP TYPE  ///////////////////////////////////

typedef struct
{
    short Count;
    short MaxCount;
    int* Vertex;
    uint64_t* Distance;
} THeap;

THeap CreateHeap(int max)
{
    THeap heap = { 0, max, NULL, NULL };

    heap.Vertex = calloc(max, sizeof(*heap.Vertex));
    assert(heap.Vertex != NULL);

    heap.Distance = calloc(max, sizeof(*heap.Distance));
    assert(heap.Distance != NULL);

    return heap;
}

bool IsEmptyHeap(THeap heap)
{
    return heap.Count == 0;
}

void SiftDown(int index, THeap heap)
{
    if (index >= heap.Count - 2)
    {
        return;
    }
    
    while(true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestChild = index;

        int leftVertex = heap.Vertex[leftChild];
        int rightVertex = heap.Vertex[rightChild];
        int largestVertex = heap.Vertex[largestChild];

        if (leftChild < heap.Count && heap.Distance[leftVertex - 1] < heap.Distance[largestVertex - 1]) 
        {
            largestChild = leftChild;
        }

        if (rightChild < heap.Count && heap.Distance[rightVertex - 1] < heap.Distance[largestVertex - 1])
        {
            largestChild = rightChild;
        }

        if (largestChild == index) 
        {
            break;
        }

        Swap(heap.Vertex + index, heap.Vertex + largestChild, sizeof(int));
        index = largestChild;
    }
}

void SiftUp(int index, THeap heap)
{
    while (true)
    {
        int parent = (index - 1) / 2;
        int parentVertex = heap.Vertex[parent];
        int indexVertex = heap.Vertex[index];

        if (heap.Distance[indexVertex - 1] >= heap.Distance[parentVertex - 1])
        {
            break;
        }

        Swap(heap.Vertex + index, heap.Vertex + parent, sizeof(int));
        index = parent;
    }
}

THeap BuildHeap(int vertexCount)
{
    THeap heap = CreateHeap(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        heap.Vertex[i] = i + 1;
        heap.Distance[i] = UINT64_MAX;
        ++heap.Count;
    }

    return heap;
}

int ExtractMinVertex(THeap* heap)
{
    assert(heap->Count != 0);
    int result = heap->Vertex[0];
    Swap(heap->Vertex, heap->Vertex + heap->Count - 1, sizeof(int));
    --heap->Count;
    SiftDown(0, *heap);
    return result;
}

int FindVertexIndex(int vertexNum, THeap heap)
{
    for (int i = 0; i < heap.Count; ++i)
    {
        if (heap.Vertex[i] == vertexNum)
        {
            return i;
        }
    }
    
    return -1;
}

void DestroyHeap(THeap* heap)
{
    free(heap->Vertex);
    free(heap->Distance);
}

///////////////////////////////////  MATRIX TYPE  ///////////////////////////////////

int* CreateMatrix(int count)
{
    int* matrix = calloc(SumArithmeticProgression(1, count, count), sizeof(*matrix));
    assert(matrix != NULL);
    return matrix;
}

int GetMatrixIndex(int row, int column, int size)
{
    int min = Min(row, column);
    int max = Max(row, column);
    return SumArithmeticProgression(size, size - min + 1, min) + (max - min);
}

void AddMatrixValue(int row, int column, int size, int length, int* matrix)
{
    int index = GetMatrixIndex(row, column, size);
    assert(matrix[index] == 0);
    matrix[index] = length;
}

int GetMatrixValue(int row, int column, int size, int* matrix)
{
    int index = GetMatrixIndex(row, column, size);
    return matrix[index];
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

int GetEdgeLength(int begin, int end, TGraph graph)
{
    return GetMatrixValue(begin - 1, end - 1, graph.VertexCount, graph.AdjMatrix);
}

void DestroyGraph(TGraph* graph)
{
    DestroyMatrix(graph->AdjMatrix);
}

///////////////////////////////////  ERRORS  ///////////////////////////////////

void BadNumberOfVerticesError(int vertexCount)
{
    if(vertexCount > MAX_VERTEX_COUNT)
    {
        printf("bad number of vertices");
        longjmp(position, SUCCESS_JUMP);
    }
}

void BadNumberOfEdgesError(int edgeCount, int vertexCount)
{
    if(edgeCount > SumArithmeticProgression(1, vertexCount, vertexCount))
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
        if(graph != NULL)
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
        DestroyGraph(graph);
        printf("bad length");
        longjmp(position, SUCCESS_JUMP);
    }
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

int InputVertexNumber(int vertexCount)
{
    int vertexNum = 0;
    if (scanf("%d", &vertexNum) != 1)
    {
        BadNumberOfLinesError();
    }
    BadVertexError(vertexNum, vertexCount, NULL);

    return vertexNum;
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

///////////////////////////////////  DIJKSTRA ALGORITHM  ///////////////////////////////////

uint64_t* DijkstraAlgorithm(int beginVertex, TGraph graph)
{
    bool* extracted = calloc(graph.VertexCount, sizeof(*extracted));
    assert(extracted != NULL);

    uint64_t* paths = calloc(graph.VertexCount, sizeof(*paths));
    assert(paths != NULL);

    for (int i = 0; i < graph.VertexCount; ++i)
    {
        if (i != beginVertex - 1)
        {
            paths[i] = UINT64_MAX;
        }
    }

    THeap heap = BuildHeap(graph.VertexCount);
    heap.Distance[beginVertex - 1] = 0;
    SiftUp(beginVertex - 1, heap);

    int vertex = ExtractMinVertex(&heap);
    extracted[vertex - 1] = true;
    
    while (!IsEmptyHeap(heap))
    {
        for (int i = 0; i < graph.VertexCount; ++i)
        {
            if (extracted[i])
            {
                continue;
            }

            unsigned int length = GetEdgeLength(i + 1, vertex, graph);
            if (length == 0)
            {
                continue;
            } 

            if (heap.Distance[vertex - 1] + length < heap.Distance[i])
            {
                heap.Distance[i] = heap.Distance[vertex - 1] + length;
                paths[i] = heap.Distance[vertex - 1] + length;

                int index = FindVertexIndex(i + 1, heap);
                assert(index != -1);
                SiftUp(index, heap);
            }
        } 

        vertex = ExtractMinVertex(&heap);
        extracted[vertex - 1] = true;
    }

    free(extracted);
    DestroyHeap(&heap);

    return paths;
}

///////////////////////////////////  ANSWER OUTPUT  ///////////////////////////////////

void OutputPathArray(int count, uint64_t* path)
{
    for (int i = 0; i < count; ++i)
    {
        if (path[i] == UINT64_MAX)
        {
            printf("oo ");
        }
        else if (path[i] > INT_MAX)
        {
            printf("INT_MAX+ ");
        }
        else
        {
            printf("%d ", (int)path[i]);
        }
    }
}

int FindPreviousVertex(int vertexNum, uint64_t* pathArray, TGraph graph)
{
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        unsigned int length = GetEdgeLength(vertexNum, i + 1, graph);
        if (length != 0 && pathArray[vertexNum - 1] == length + pathArray[i])
        {
            return i + 1;
        }
    }

    return 0;
}

bool CheckOverflow(int vertexNum, int size, uint64_t* pathArray)
{
    if (pathArray[vertexNum - 1] <= INT_MAX)
    {
        return false;
    }

    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (i != vertexNum - 1 && pathArray[i] != UINT64_MAX && pathArray[i] >= INT_MAX)
        {
            ++count;
            if (count == 2)
            {
                return true;
            }
        }
    }

    return false;
}

void OutputShortestPath(int endVertex, uint64_t* pathArray, TGraph graph)
{
    if (pathArray[endVertex - 1] == UINT64_MAX)
    {
        printf("no path");
        return;
    }
    else if (CheckOverflow(endVertex, graph.VertexCount, pathArray))
    {
        printf("overflow");
        return;
    }

    printf("%d ", endVertex);

    while (pathArray[endVertex - 1] != 0)
    {
        endVertex = FindPreviousVertex(endVertex, pathArray, graph);
        assert(endVertex != 0);

        printf("%d ", endVertex);
    }
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    if(setjmp(position) == 0)
    {
        int vertexCount = InputVertexCount();
        int beginNum = InputVertexNumber(vertexCount);
        int endNum = InputVertexNumber(vertexCount);
        int edgeCount = InputEdgeCount(vertexCount);
        TGraph graph = InputGraph(vertexCount, edgeCount);

        uint64_t* paths = DijkstraAlgorithm(beginNum, graph);

        OutputPathArray(vertexCount, paths);
        printf("\n");
        OutputShortestPath(endNum, paths, graph);

        free(paths);
        DestroyGraph(&graph);
    }

    return EXIT_SUCCESS;
}