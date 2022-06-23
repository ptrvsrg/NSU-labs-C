#include "graph.h"
#include "kruskal.h"

int main(void)
{
    TGraph graph = InputGraph();
    TGraph MST = KruskalAlgorithm(&graph);
    OutputGraph(MST);

    DestroyGraph(&graph);
    DestroyGraph(&MST);

    return EXIT_SUCCESS;
}
