#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

typedef struct TMemory
{
    int Count;
    int Index;
    void* Buffer;
} TMemory;

TMemory CreateMemory(int count, int size);
void DestroyMemory(TMemory* Memory);

#endif
