#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "matrix.h"

typedef struct TGraph
{
    int VertexCount;
    TMatrix Matrix;
} TGraph;

TGraph CreateGraph(int count);
void PushEdge(int begin, int end, int length, TGraph* graph);
int GetLengthGraph(int begin, int end, TGraph graph);
void PrintGraph(TGraph graph);
void DestroyGraph(TGraph* graph);
TGraph InputGraph(int* beginVertex, int* endVertex);

#endif
