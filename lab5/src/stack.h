#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "tree.h"

struct Tstack
{
    TTree Tree;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

TStack CreateStack(void);
bool IsEmptyStack(TStack stack);
void PushStack(TTree tree, TStack* stack);
TTree PopStack(TStack* stack);
void FreeElementStack(TStack* item);
void DestroyStack(TStack* stack);

#endif 
