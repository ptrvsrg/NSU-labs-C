#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TCircularList
{
    int BeginIndex;
    int Count;
    int Max;
    char* Array;
} TCircularList;

TCircularList CreateCircularList(int max);
void InputTemplate(int count, TCircularList* circularList);
void InputCircularList(int count, TCircularList* circularList);
bool ShiftCircularList(TCircularList* circularList, int shift);
void DestroyCircularList(TCircularList* circularList);

#endif
