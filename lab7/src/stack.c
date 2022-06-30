#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

TStack CreateStack(int max)
{
    TStack stack = { 0, max, NULL };

    if (max > 0)
    {
        stack.Array = calloc(max, sizeof(int));
        if (stack.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return stack;
}

static bool IsEmptyStack(TStack stack)
{
    return stack.Count == 0;
}

static bool StackOverflow(TStack stack)
{
    return stack.Count == stack.Max;
}

void PushStack(int value, TStack* stack)
{
    if (StackOverflow(*stack))
    {
        DestroyStack(stack);
        OtherError(__FILE__, __LINE__);
    }

    stack->Array[stack->Count] = value;
    ++stack->Count;
}

static int PopStack(TStack* stack)
{
    if (IsEmptyStack(*stack))
    {
        DestroyStack(stack);
        OtherError(__FILE__, __LINE__);
    }

    --stack->Count;
    return stack->Array[stack->Count];
}

void DestroyStack(TStack* stack) 
{
    free(stack->Array);
    *stack = CreateStack(0);
}

void PrintStack(TStack stack)
{
    while (!IsEmptyStack(stack))
    {
        printf("%d ", PopStack(&stack));
    }
}
