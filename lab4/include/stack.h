#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include "data.h"
#include "error.h"
#include "stack.h"

typedef struct TStack
{
    TData Data;
    struct TStack* Next;
} *TStack;

TStack CreateStack(void);
bool IsEmptyStack(TStack stack);
TData GetTopStack(TStack stack);
TData PopStack(TStack* stack);
void PushStack(TData data, TStack* stack);
void DestroyStack(TStack* stack);

#endif
