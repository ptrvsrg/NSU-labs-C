#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TStack
{
    int Count;
    int Max;
    int * Array;
} TStack;

TStack CreateStack(int max);
void PushStack(int value, TStack* stack);
void DestroyStack(TStack* stack);
void PrintStack(TStack stack);

#endif 
