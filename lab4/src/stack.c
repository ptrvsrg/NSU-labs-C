#include "stack.h"

////////////////////////////////  VALUE TYPE  ////////////////////////////////

TValue CreateValue(char op, int number)
{
    TValue new;
    new.Number = number;
    new.Operator = op;
    return new;
}

////////////////////////////////  STACK TYPE  ////////////////////////////////

TStackPtr CreateStack() 
{
    return NULL;
}

bool IsEmptyStack(TStackPtr stack)
{
    return stack == NULL;
}

TValue GetTopStack(TStackPtr stack)
{
    if (IsEmptyStack(stack))
    {
        OtherError();
    }
    
    return stack->Value;
}

TValue PopStack(TStackPtr* stack)
{
    if (IsEmptyStack(*stack))
    {
        OtherError();
    }

    TValue value = GetTopStack(*stack);
    TStackPtr removeElem = *stack;
    *stack = (*stack)->Next;
    free(removeElem);

    return value;
}

void PushStack(TStackPtr* stack, TValue value)
{
    TStackPtr new = malloc(sizeof(*new));
    if (new == NULL)
    {
        DestroyStack(stack);
        OtherError();
    }

    new->Value = value;
    new->Next = *stack;
    *stack = new;
}

void DestroyStack(TStackPtr* stack) 
{
    if (!IsEmptyStack(*stack)) 
    {
        DestroyStack(&(*stack)->Next);
        free(*stack);
        *stack = NULL;
    }
}