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

typedef enum TColor
{
    WHITE,
    BLACK
} TColor;

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

int GetEdgeLength(int begin, int end, TGraph* graph)
{
    return GetMatrixValue(begin - 1, end - 1, graph->VertexCount, graph->Matrix);
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

///////////////////////////////////  OUTPUT  ///////////////////////////////////

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
            printf("%llu ", pathArray[i]);
        }
    }
}

int FindPreviousVertex(int vertexNum, uint64_t* pathArray, TGraph* graph)
{
    for (int i = 0; i < graph->VertexCount; ++i)
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

void OutputShortestPathVertex(int endNum, uint64_t* pathArray, TGraph* graph)
{
    if (pathArray[endNum - 1] == UINT64_MAX)
    {
        printf("no path");
        return;
    }
    else if (CheckOverflow(endNum, graph->VertexCount, pathArray))
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

///////////////////////////////////  Dijkstra algorithm  ///////////////////////////////////

int FindNearestVertex(int vertexCount, uint64_t* pathArray, TColor* visitArray)
{
    int minNum = 0;
    uint64_t min = UINT64_MAX;

    for (int i = 0; i < vertexCount; ++i)
    {
        if (visitArray[i] == WHITE && pathArray[i] <= min)
        {
            min = pathArray[i];
            minNum = i + 1;
        }
    }

    return minNum;
}

void ChangeLength(int vertexNum, uint64_t* pathArray, TColor* visitArray, TGraph* graph)
{
    for (int i = 0; i < graph->VertexCount; ++i)
    {
        uint64_t length = GetEdgeLength(vertexNum, i + 1, graph);
        if (length > 0 && visitArray[i] == WHITE && pathArray[i] > length + pathArray[vertexNum - 1])
        {
            pathArray[i] = length + pathArray[vertexNum - 1];
        }
    }
}

void DijkstraAlgorithm(uint64_t* pathArray, TColor* visitArray, TGraph* graph)
{
    for (int i = 0; i < graph->VertexCount; ++i)
    {
        int vertexNum = FindNearestVertex(graph->VertexCount, pathArray, visitArray);
        visitArray[vertexNum - 1] = BLACK;

        ChangeLength(vertexNum, pathArray, visitArray, graph);
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

        TColor* visitArray = calloc(graph.VertexCount, sizeof(*visitArray));
        assert(visitArray != NULL);

        uint64_t* pathArray = calloc(graph.VertexCount, sizeof(*pathArray));
        assert(pathArray != NULL);
        for (int i = 0; i < graph.VertexCount; ++i)
        {
            if(i != beginNum - 1)
            {
                pathArray[i] = UINT64_MAX;
            }
        }

        DijkstraAlgorithm(pathArray, visitArray, &graph);

        OutputPathArray(vertexCount, pathArray);
        printf("\n");
        OutputShortestPathVertex(endNum, pathArray, &graph);

        free(pathArray);
        free(visitArray);
        DestroyGraph(&graph);
    }

    return EXIT_SUCCESS;
}