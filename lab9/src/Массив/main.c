#include <assert.h>
#include <limits.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

///////////////////////////////////  MATRIX TYPE  ///////////////////////////////////

int* CreateMatrix(int count)
{
    int* matrix = calloc(SumArithmeticProgression(1, count, count), sizeof(*matrix));
    assert(matrix != NULL);
    return matrix;
}

int GetMatrixIndex(int row, int column, int size)
{
    int min = (row >= column) ? column : row;
    int max = (row < column) ? column : row;

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

typedef struct TGraph TGraph;
struct TGraph
{
    int VertexCount;
    int* Matrix;
};

TGraph CreateGraph(int vertexCount)
{
    TGraph graph = { vertexCount, NULL };
    graph.Matrix = CreateMatrix(vertexCount);
    return graph;
}

void PushEdge(int begin, int end, int length, TGraph* graph)
{
    AddMatrixValue(begin - 1, end - 1, graph->VertexCount, length, graph->Matrix);
}

int GetEdgeLength(int begin, int end, TGraph graph)
{
    return GetMatrixValue(begin - 1, end - 1, graph.VertexCount, graph.Matrix);
}

void DestroyGraph(TGraph* graph)
{
    DestroyMatrix(graph->Matrix);
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

int FindNearestVertex(int vertexCount, uint64_t* pathArray, bool* visited)
{
    int minNum = 0;
    uint64_t min = UINT64_MAX;

    for (int i = 0; i < vertexCount; ++i)
    {
        if (!visited[i] && pathArray[i] <= min)
        {
            min = pathArray[i];
            minNum = i + 1;
        }
    }

    return minNum;
}

void ChangeLength(int vertexNum, uint64_t* pathArray, bool* visited, TGraph graph)
{
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        uint64_t length = GetEdgeLength(vertexNum, i + 1, graph);
        if (length > 0 && !visited[i] && pathArray[i] > length + pathArray[vertexNum - 1])
        {
            pathArray[i] = length + pathArray[vertexNum - 1];
        }
    }
}

uint64_t* DijkstraAlgorithm(int beginNum, TGraph graph)
{
    bool* visited = calloc(graph.VertexCount, sizeof(*visited));
    assert(visited != NULL);

    uint64_t* pathArray = calloc(graph.VertexCount, sizeof(*pathArray));
    assert(pathArray != NULL);
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        if(i != beginNum - 1)
        {
            pathArray[i] = UINT64_MAX;
        }
    }

    for (int i = 0; i < graph.VertexCount; ++i)
    {
        int vertexNum = FindNearestVertex(graph.VertexCount, pathArray, visited);
        visited[vertexNum - 1] = true;

        ChangeLength(vertexNum, pathArray, visited, graph);
    }

    free(visited);
    return pathArray;
}

///////////////////////////////////  ANSWER OUTPUT  ///////////////////////////////////

void OutputPathArray(int vertexCount, uint64_t* pathArray)
{
    for (int i = 0; i < vertexCount; ++i)
    {
        if (pathArray[i] == UINT64_MAX)
        {
            printf("oo ");
        }
        else if (pathArray[i] > INT_MAX)
        {
            printf("INT_MAX+ ");
        }
        else
        {
            printf("%d ", (int)pathArray[i]);
        }
    }
}

int FindPreviousVertex(int vertexNum, uint64_t* pathArray, TGraph graph)
{
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        uint64_t length = GetEdgeLength(vertexNum, i + 1, graph);
        if (length > 0 && pathArray[vertexNum - 1] == length + pathArray[i])
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
            if(count == 2)
            {
                return true;
            }
        }
    }

    return false;
}

void OutputShortestPath(int endNum, uint64_t* pathArray, TGraph graph)
{
    if (pathArray[endNum - 1] == UINT64_MAX)
    {
        printf("no path");
        return;
    }
    else if (CheckOverflow(endNum, graph.VertexCount, pathArray))
    {
        printf("overflow");
        return;
    }

    printf("%d ", endNum);

    while (pathArray[endNum - 1] != 0)
    {
        endNum = FindPreviousVertex(endNum, pathArray, graph);
        assert(endNum != 0);

        printf("%d ", endNum);
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

        uint64_t* pathArray = DijkstraAlgorithm(beginNum, graph);

        OutputPathArray(vertexCount, pathArray);
        printf("\n");
        OutputShortestPath(endNum, pathArray, graph);

        free(pathArray);
        DestroyGraph(&graph);
    }

    return EXIT_SUCCESS;
}