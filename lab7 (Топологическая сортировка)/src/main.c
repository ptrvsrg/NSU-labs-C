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

/////////////////////////////////// STACK TYPE  ///////////////////////////////////

typedef struct
{
    short Count;
    short Max;
    short* Array;
} TStack;

TStack CreateStack(short max)
{
    TStack stack = { 0, max, NULL };

    stack.Array = calloc(max, sizeof(*stack.Array));
    assert(stack.Array != NULL);

    return stack;
}

void PushStack(short value, TStack* stack)
{
    assert(stack->Count != stack->Max);
    stack->Array[stack->Count] = value;
    ++stack->Count;
}

short PopStack(TStack* stack)
{
    assert(stack->Count != 0);
    short value = stack->Array[stack->Count - 1];
    --stack->Count;
    return value;
}

void PrintStack(TStack stack)
{
    int count = stack.Count;
    for (int i = 0; i < count; ++i)
    {
        printf("%hd ", PopStack(&stack));
    }
}

void DestroyStack(TStack* stack)
{
    free(stack->Array);
    stack->Count = 0;
    stack->Max = 0;
}

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

///////////////////////////////////  DEPTH-FIRST SEARCH  ///////////////////////////////////

void DepthFirstSearch(int numVertex, TColor* status, TStack* numbering, TGraph* graph)
{
    if(status[numVertex - 1] == GREY)
    {
        free(status);
        DestroyStack(numbering);
        DestroyGraph(graph);
        ImpossibleToSortError();
    }
    else if(status[numVertex - 1] == WHITE)
    {
        status[numVertex - 1] = GREY;

        for (int i = 0; i < graph->VertexCount; ++i)
        {
            if(GetMatrixValue(numVertex - 1, i, graph->VertexCount, graph->Matrix) == '1')
            {
                DepthFirstSearch(i + 1, status, numbering, graph);
            }
        }

        PushStack(numVertex, numbering);
        status[numVertex- 1] = BLACK;
    }
}

///////////////////////////////////  TOPOLOGICAL SORT  ///////////////////////////////////

void TopologicalSort(TGraph* graph)
{
    TStack numbering = CreateStack(graph->VertexCount);

    TColor* status = calloc(graph->VertexCount, sizeof(*status));
    assert(status != NULL);

    for (int i = 0; i < graph->VertexCount; ++i)
    {
        DepthFirstSearch(i + 1, status, &numbering, graph);
    }

    PrintStack(numbering);

    free(status);
    DestroyStack(&numbering);
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
