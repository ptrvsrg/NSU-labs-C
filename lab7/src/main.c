#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include "stack.h"
#include "topsort.h"

static int PrintInt(const void* value)
{
    const int* intValue = value;
    return printf("%d ", *intValue);
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
