#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include "error.h"
#include "matrix.h"

typedef struct TGraph
{
    int VertexCount;
    TMatrix Matrix;
} TGraph;

TGraph CreateGraph(int vertexCount);
bool IsEdgeExists(int start, int end, TGraph graph);
void PushEdge(int start, int end, TGraph* graph);
void DestroyGraph(TGraph* graph);
TGraph InputGraph(void);

#endif
