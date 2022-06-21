#include "memory.h"

TMemory CreateMemory(int count, int size)
{
    TMemory Memory = { count, 0, NULL };

    Memory.Buffer = malloc(count * size);
    if (Memory.Buffer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    return Memory;
}

void DestroyMemory(TMemory* Memory)
{
    free(Memory->Buffer);
}
