#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include "stack.h"
#include "topsort.h"

int main(void)
{
    TGraph graph = InputGraph();
    
    TStack numbering = TopologicalSort(&graph);
    PrintStack(numbering);

    DestroyStack(&numbering);
    DestroyGraph(&graph);

    return EXIT_SUCCESS;
}
