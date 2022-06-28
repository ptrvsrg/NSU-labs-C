#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include "error.h"
#include "heap.h"
#include "graph.h"

uint64_t* DijkstraAlgorithm(int beginVertex, TGraph graph);

#endif
