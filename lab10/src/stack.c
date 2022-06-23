#include "stack.h"

TStack CreateStack(int max, int size)
{
    TStack stack = { 0, max, size, NULL };

    stack.Array = calloc(max, size);
    if (stack.Array == NULL)
    {
        OtherError(__FILE__, __LINE__);
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

void* GetNthElementStack(TStack stack, int n)
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

    AssignStack(stack->Size, value, GetNthElementStack(*stack, stack->Count));
    ++stack->Count;
}

void* TopStack(TStack stack)
{
    if (IsEmptyStack(stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    return GetNthElementStack(stack, stack.Count - 1);
}

void* NextToTopSTack(TStack stack)
{
    if (stack.Count < 2)
    {
        OtherError(__FILE__, __LINE__);
    }

    return GetNthElementStack(stack, stack.Count - 2);
}

void* PopStack(TStack* stack)
{
    if (IsEmptyStack(*stack))
    {
        OtherError(__FILE__, __LINE__);
    }

    --stack->Count;
    return GetNthElementStack(*stack, stack->Count);
}

void DestroyStack(TStack* stack) 
{
    free(stack->Array);
    stack->Count = 0;
    stack->Array = NULL;
}

void PrintStack(TStack stack, int (*Print)(const void*))
{
    for (int i = 0; i < stack.Count; ++i)
    {
        if (Print(GetNthElementStack(stack, i)) == EOF)
        {
            OtherError(__FILE__, __LINE__);
        }
    }
}
