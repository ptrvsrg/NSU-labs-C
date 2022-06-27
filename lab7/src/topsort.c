#include "topsort.h"

typedef enum
{
    WHITE = 0,
    GREY,
    BLACK
} TColor;

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

        PushStack(numVertex, numbering);
        status[numVertex- 1] = BLACK;
    }
}

TStack TopologicalSort(TGraph* graph)
{
    TStack numbering = CreateStack(graph->VertexCount);

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

    free(status);

    return numbering;
}
