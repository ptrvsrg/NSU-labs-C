#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "error.h"
#include "subject.h"
#include "table.h"
#include "vector.h"
#include <stdio.h>

TTable CreateMemTable(int maxWeight, TVector subjectVector);
void PrintMaxPrice(TTable memTable);
void PrintKnapsack(TVector subjectVector, TTable memTable, int (*print)(const void*));

#endif
