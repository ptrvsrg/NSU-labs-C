#include "stack.h"

TStack CreateStack(int max, int size)
{
    TStack stack = { 0, max, size, NULL };

    if (max > 0)
    {
        stack.Array = calloc(max, size);
        if (stack.Array == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }
    }

    return stack;
}

bool IsEmptyStack(TStack stack)
{
    return stack.Count == 0;
}

static bool StackOverflow(TStack stack)
{
    return stack.Count == stack.Max;
}

void AssignStack(int size, const void* src, void* dest)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void* GetNthStack(TStack stack, int n)
{
    if (n >= stack.Max)
    {
        OtherError(__FILE__, __LINE__);
    }

    return (char*)stack.Array + n * stack.Size;
}

void PushStack(void* value, TStack* stack)
{
    if (StackOverflow(*stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    AssignStack(stack->Size, value, GetNthStack(*stack, stack->Count));
    ++stack->Count;
}

void* TopStack(TStack stack)
{
    if (IsEmptyStack(stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    return GetNthStack(stack, stack.Count - 1);
}

void* NextToTopSTack(TStack stack)
{
    if (stack.Count < 2)
    {
        OtherError(__FILE__, __LINE__);
    }

    return GetNthStack(stack, stack.Count - 2);
}

void* PopStack(TStack* stack)
{
    if (IsEmptyStack(*stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    --stack->Count;
    return GetNthStack(*stack, stack->Count);
}

void DestroyStack(TStack* stack) 
{
    if (!IsEmptyStack(*stack))
    {
        free(stack->Array);
    }
    
    stack->Array = NULL;
    stack->Count = 0;
    stack->Max = 0;
    stack->Size = 0;
}

void PrintStack(TStack stack, int (*Print)(const void*))
{
    while (!IsEmptyStack(stack))
    {
        if (Print(PopStack(&stack)) == EOF)
        {
            OtherError(__FILE__, __LINE__);
        }
    }
}
