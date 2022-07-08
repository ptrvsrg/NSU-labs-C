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
    TStack new = malloc(sizeof(*new));
    if (new == NULL)
    {
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

    TTree removeTree = (*stack)->Tree;
    TStack removeItem = *stack;
    *stack = (*stack)->Next;
    free(removeItem);
    return removeTree;
}

void DestroyStack(TStack* stack)
{
    if (!IsEmptyStack(*stack))
    {
        DestroyStack(&(*stack)->Next);
        DestroyTree(&(*stack)->Tree);
        free(*stack);
        *stack = NULL;
    }
}

