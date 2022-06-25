#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TEdge
{
    int Begin;
    int End;
    int Length;
} TEdge;

typedef struct TGraph
{
    int EdgeIndex;
    int EdgeCount;
    int VertexCount;
    TEdge* Edges;
} TGraph;

TGraph CreateGraph(int vertexCount, int edgeCount);
void PushEdge(TEdge edge, TGraph* graph);
void DestroyGraph(TGraph* graph);
TGraph InputGraph(void);
void OutputGraph(TGraph graph);
int CompareEdge(const void* a, const void* b);

#endif
