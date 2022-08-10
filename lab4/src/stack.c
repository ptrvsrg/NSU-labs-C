#include "stack.h"

TStack CreateStack()
{
    return NULL;
}

bool IsEmptyStack(TStack stack)
{
    return stack == NULL;
}

TData GetTopStack(TStack stack)
{
    if (IsEmptyStack(stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    return stack->Data;
}

TData PopStack(TStack* stack)
{
    if (IsEmptyStack(*stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    TData value = GetTopStack(*stack);
    TStack removeElem = *stack;
    *stack = (*stack)->Next;
    free(removeElem);

    return value;
}

void PushStack(TData data, TStack* stack)
{
    TStack new = malloc(sizeof(*new));
    if (new == NULL)
    {
        DestroyStack(stack);
        OtherError(__FILE__, __LINE__);
    }

    new->Data = data;
    new->Next = *stack;
    *stack = new;
}

void DestroyStack(TStack* stack)
{
    if (!IsEmptyStack(*stack))
    {
        DestroyStack(&(*stack)->Next);
        free(*stack);
        *stack = NULL;
    }
}
