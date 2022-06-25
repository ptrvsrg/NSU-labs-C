#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include "topsort.h"

int main(void)
{
    TGraph graph = InputGraph();
    TopologicalSort(&graph);
    DestroyGraph(&graph);

    return EXIT_SUCCESS;
}
