#include "stack.h"

TStack CreateStack(void)
{
    return NULL;
}

bool IsEmptyStack(TStack stack)
{
    return stack == NULL;
}

void PushStack(TTree tree, TStack* stack)
{
    TStack new = malloc(sizeof(*stack));
    if (new == NULL)
    {
        DestroyStack(stack);
        ExitWithError(__FILE__, __LINE__);
    }

    new->Tree = tree;
    new->Next = *stack;
    *stack = new;
}

TTree PopStack(TStack* stack)
{
    if (IsEmptyStack(*stack))
    {
        ExitWithError(__FILE__, __LINE__);
    }

    TTree removeTree = CloneTree((*stack)->Tree);
    TStack removeItem = *stack;
    *stack = (*stack)->Next;
    FreeElementStack(&removeItem);
    return removeTree;
}

void FreeElementStack(TStack* item)
{
    if (!IsEmptyStack(*item))
    {
        DestroyTree(&(*item)->Tree);
        free(*item);
        *item = NULL;
    }
}

void DestroyStack(TStack* stack)
{
    if (!IsEmptyStack(*stack))
    {
        DestroyStack(&(*stack)->Next);
        FreeElementStack(stack);
    }
}

