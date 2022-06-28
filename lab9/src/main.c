#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "graph.h"
#include "output.h"

int main(void)
{
    int beginVertex = 0;
    int endVertex = 0;
    TGraph graph = InputGraph(&beginVertex, &endVertex);

    uint64_t* paths = DijkstraAlgorithm(beginVertex, graph);

    OutputPathArray(graph.VertexCount, paths);
    printf("\n");
    OutputShortestPath(endVertex, paths, graph);

    free(paths);
    DestroyGraph(&graph);

    return EXIT_SUCCESS;
}
