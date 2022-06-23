#ifndef TOPSORT_H
#define TOPSORT_H

#include <stdio.h>
#include "error.h"
#include "graph.h"
#include "matrix.h"
#include "stack.h"

TStack TopologicalSort(TGraph* graph);

#endif
