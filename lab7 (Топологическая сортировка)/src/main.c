#include <assert.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGE_COUNT(vertexCount)  vertexCount*(vertexCount-1)/2

static jmp_buf position;

enum
{
    SUCCESS_JUMP = 1,
    CHAR_SIZE = 8,
    MAX_VERTEX_COUNT = 2000
};

typedef enum TColor
{
    WHITE = 0,
    GREY,
    BLACK
} TColor;

/////////////////////////////////// MATRIX FUNCTION  ///////////////////////////////////

char* CreateMatrix(int count)
{
    int matrixSize = count * count / CHAR_SIZE;
    matrixSize += (count * count % CHAR_SIZE == 0) ? 0 : 1;

    char* matrix = calloc(matrixSize, sizeof(*matrix));
    assert(matrix != NULL);

    return matrix;
}

void AddMatrixValue(int row, int column, int size,  char* matrix)
{
    int index = (row * size + column) / CHAR_SIZE;
    unsigned char mask = 128 >> (row * size + column) % CHAR_SIZE;
    matrix[index] |= mask;
}

char GetMatrixValue(int row, int column, int size,  char* matrix)
{
    int index = (row * size + column) / CHAR_SIZE;
    unsigned char mask = 128 >> (row * size + column) % CHAR_SIZE;
    mask &= matrix[index];
    return (mask == 0) ? '0' : '1';
}

void DestroyMatrix(char* matrix)
{
    free(matrix);
}

///////////////////////////////////  GRAPH TYPE  ///////////////////////////////////

typedef struct TGraph TGraph;
struct TGraph
{
    short VertexCount;
    char* Matrix;
};

TGraph CreateGraph(int vertexCount)
{
    TGraph graph = { vertexCount, NULL };
    graph.Matrix = CreateMatrix(vertexCount);
    return graph;
}

void PushEdge(int start, int end, TGraph graph)
{
    AddMatrixValue(start - 1, end - 1, graph.VertexCount, graph.Matrix);
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
    if(edgeCount > MAX_EDGE_COUNT(vertexCount))
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

void BadVertexError(int vertexNum, int vertexCount, TGraph graph)
{
    if(vertexNum <= 0 || vertexNum > vertexCount)
    {
        DestroyGraph(&graph);
        printf("bad vertex");
        longjmp(position, SUCCESS_JUMP);
    }
}

void ImpossibleToSortError(void)
{
    printf("impossible to sort");
    longjmp(position, SUCCESS_JUMP);
}

///////////////////////////////////  INPUT / OUTPUT  ///////////////////////////////////

void InputVertexCount(int* vertexCount)
{
    if(scanf("%d", vertexCount) != 1)
    {
        BadNumberOfLinesError();
    }
    BadNumberOfVerticesError(*vertexCount);
}

void InputEdgeCount(int* edgeCount, int vertexCount)
{
    if(scanf("%d", edgeCount) != 1)
    {
        BadNumberOfLinesError();
    }
    BadNumberOfEdgesError(*edgeCount, vertexCount);
}

bool InputEdge(int vertexCount, TGraph graph)
{
    int start = 0;
    if(scanf("%d", &start) != 1)
    {
        return false;
    }
    BadVertexError(start, vertexCount, graph);

    int end = 0;
    if(scanf("%d", &end) != 1)
    {
        return false;
    }
    BadVertexError(end, vertexCount, graph);

    PushEdge(start, end, graph);
    return true;
}

TGraph InputGraph(void)
{
    int vertexCount = 0;
    InputVertexCount(&vertexCount);

    int edgeCount = 0;
    InputEdgeCount(&edgeCount, vertexCount);

    TGraph graph = CreateGraph(vertexCount);

    int edgeNum = 0;
    while(InputEdge(vertexCount, graph))
    {
        ++edgeNum;
    }

    if(edgeNum != edgeCount)
    {
        DestroyGraph(&graph);
        BadNumberOfLinesError();
    }

    return graph;
}

void OutputNumbering(int size, short* numbering)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%hd ", numbering[size - 1 - i]);
    }
}

///////////////////////////////////  DEPTH-FIRST SEARCH  ///////////////////////////////////

bool  DepthFirstSearch(int numVertex, TColor* status, short* numbering, TGraph* graph)
{
    if(status[numVertex - 1] == GREY)
    {
        return false;
    }
    else if(status[numVertex - 1] == BLACK)
    {
        return true;
    }

    status[numVertex - 1] = GREY;

    for (int i = 0; i < graph->VertexCount; ++i)
    {
        if(GetMatrixValue(numVertex - 1, i, graph->VertexCount, graph->Matrix) == '1')
        {
            if(!DepthFirstSearch(i + 1, status, numbering, graph))
            {
                return false;
            }
        }
    }

    static int index = 0;
    numbering[index] = numVertex;
    ++index;
    status[numVertex- 1] = BLACK;

    return true;
}

///////////////////////////////////  TOPOLOGICAL SORT  ///////////////////////////////////

void TopologicalSort(TGraph* graph)
{
    short* numbering = calloc(graph->VertexCount, sizeof(*numbering));
    assert(numbering != NULL);

    TColor* status = calloc(graph->VertexCount, sizeof(*status));
    assert(status != NULL);

    bool control = true;

    for (int i = 0; i < graph->VertexCount; ++i)
    {
        if(!DepthFirstSearch(i + 1, status, numbering, graph))
        {
            control = false;
            break;
        }
    }

    if(control)
    {
        OutputNumbering(graph->VertexCount, numbering);
    }

    free(numbering);
    free(status);

    if(!control)
    {
        DestroyGraph(graph);
        ImpossibleToSortError();
    }
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    assert(freopen("in.txt", "r", stdin) != NULL);
    assert(freopen("out.txt", "w", stdout) != NULL);

    if(setjmp(position) == 0)
    {
        TGraph graph = InputGraph();
        TopologicalSort(&graph);
        DestroyGraph(&graph);
    }

    fclose(stdin);
    fclose(stdout);

    return EXIT_SUCCESS;
}
