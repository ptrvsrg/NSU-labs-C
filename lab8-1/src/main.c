#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include "prim.h"

int main(void)
{
    TGraph graph = InputGraph();

    TGraph MST = PrimAlgorithm(&graph);
    PrintGraph(MST);

    DestroyGraph(&graph);
    DestroyGraph(&MST);

    return EXIT_SUCCESS;
}
