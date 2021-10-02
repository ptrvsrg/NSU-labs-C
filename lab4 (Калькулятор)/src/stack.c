#include "calc.h"

void CreateStack(TStack* stack) 
{
    stack->position = 0;
}

void Remove(TStack* stack)
{
    assert(stack->position != 0);
    --stack->position;
}

char GetTop(TStack* stack)
{
    assert(stack->position != 0);
    return stack->Values[stack->position - 1];
}

char Pop(TStack* stack)
{
    assert(stack->position != 0);
    char top = GetTop(stack);
    Remove(stack);
    return top;
}

void Push(TStack* stack, char value)
{
    stack->Values[stack->position] = value;
    ++stack->position;
}

bool IsEmpty(TStack stack)
{
    return stack.position == 0;
}

void DestroyStack(TStack stack) 
{
    while (!IsEmpty(stack)) 
    {
        Remove(&stack);
    }
}
