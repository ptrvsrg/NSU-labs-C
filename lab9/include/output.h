#ifndef OUTPUT_H
#define OUTPUT_H

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void OutputPathArray(int count, uint64_t* path);
void OutputShortestPath(int endVertex, uint64_t* pathArray, TGraph graph);

#endif
