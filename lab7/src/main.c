#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include "stack.h"
#include "topsort.h"

static int PrintInt(const int* value)
{
    return printf("%d ", *value);
}

int main(void)
{
    TGraph graph = InputGraph();
    TStack numbering = TopologicalSort(&graph);
    PrintStack(numbering, PrintInt);
    DestroyGraph(&graph);
    DestroyStack(&numbering);

    return EXIT_SUCCESS;
}
