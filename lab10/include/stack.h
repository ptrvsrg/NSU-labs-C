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
    int Size;
    void* Array;
} TStack;

TStack CreateStack(int max, int size);
bool IsEmptyStack(TStack stack);
void AssignStack(int size, const void* src, void* dest);
void* GetNthStack(TStack stack, int n);
void PushStack(void* value, TStack* stack);
void* TopStack(TStack stack);
void* NextToTopSTack(TStack stack);
void* PopStack(TStack* stack);
void DestroyStack(TStack* stack);
void PrintStack(TStack stack, int (*Print)(const void*));

#endif 
