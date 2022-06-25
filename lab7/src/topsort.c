#include "topsort.h"

typedef enum
{
    WHITE = 0,
    GREY,
    BLACK
} TColor;

static int PrintInt(const void* value)
{
    const int* intValue = value;
    return printf("%d ", *intValue);
}

static void DepthFirstSearch(int numVertex, TColor* status, TStack* numbering, TGraph* graph)
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
            if(IsEdgeExists(numVertex, i + 1, *graph))
            {
                DepthFirstSearch(i + 1, status, numbering, graph);
            }
        }

        PushStack(&numVertex, numbering);
        status[numVertex- 1] = BLACK;
    }
}

void TopologicalSort(TGraph* graph)
{
    TStack numbering = CreateStack(graph->VertexCount, sizeof(int));

    TColor* status = calloc(graph->VertexCount, sizeof(*status));
    if (status == NULL)
    {
        DestroyStack(&numbering);
        DestroyGraph(graph);
        OtherError(__FILE__, __LINE__);
    }

    for (int i = 0; i < graph->VertexCount; ++i)
    {
        DepthFirstSearch(i + 1, status, &numbering, graph);
    }

    PrintStack(numbering, PrintInt);

    free(status);
    DestroyStack(&numbering);
}
