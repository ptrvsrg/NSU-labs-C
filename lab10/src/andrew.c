#include "andrew.h"

static int ComparePointLower(const void* a, const void* b)
{
    const TPoint* A = a;
    const TPoint* B = b;

    int difference = ComparePointX(A, B);
    if (difference == 0)
    {
        difference = ComparePointY(A, B);
    }

    return (difference > 0) ? 1 : (difference == 0) ? 0 : -1;
}

static int ComparePointUpper(const void* a, const void* b)
{
    const TPoint* A = a;
    const TPoint* B = b;

    int difference = ComparePointX(B, A);
    if (difference == 0)
    {
        difference = ComparePointY(B, A);
    }

    return (difference > 0) ? 1 : (difference == 0) ? 0 : -1;
}

static TPoint FindMin(TVector vector)
{
    TPoint min = { INT_MAX, INT_MAX };

    for (int i = 0; i < vector.Count; ++i)
    {
        if (ComparePointX(GetNthElementVector(vector, i), &min) == -1 || (ComparePointX(GetNthElementVector(vector, i), &min) == 0 && ComparePointY(GetNthElementVector(vector, i), &min) == -1))
        {
            min = *((TPoint*)GetNthElementVector(vector, i));
        } 
    }

    return min;
}

static TPoint FindMax(TVector vector)
{
    TPoint max = { INT_MIN, INT_MIN };

    for (int i = 0; i < vector.Count; ++i)
    {
        if (ComparePointX(&max, GetNthElementVector(vector, i)) == -1 || (ComparePointX(&max, GetNthElementVector(vector, i)) == 0 && ComparePointY(&max, GetNthElementVector(vector, i)) == -1))
        {
            max = *((TPoint*)GetNthElementVector(vector, i));
        }  
    }

    return max;
}

static long double VectorMultiplication(TPoint a, TPoint b, TPoint c)
{
    long double dx1 = (long double)b.X - a.X;
    long double dx2 = (long double)c.X - a.X;
    long double dy1 = (long double)b.Y - a.Y;
    long double dy2 = (long double)c.Y - a.Y;

    return (dx1 * dy2) - (dy1 * dx2);
}

static TVector CreateLowerVector(TVector vector, TPoint min, TPoint max)
{
    TVector set = CreateVector(vector.Count, vector.Size);

    int index = 0;
    for (int i = 0; i < vector.Count; ++i)
    {
        long double mult = VectorMultiplication(min, max, *((TPoint*)GetNthElementVector(vector, i)));
        if (mult < 0)
        {
            AssignVector(vector.Size, GetNthElementVector(vector, i), GetNthElementVector(set, index));
            ++index;
        }
    }

    AssignVector(vector.Size, &min, GetNthElementVector(set, index));
    AssignVector(vector.Size, &max, GetNthElementVector(set, index + 1));
    set.Count = index + 2;
    
    return set;
}

static TVector CreateUpperVector(TVector vector, TPoint min, TPoint max)
{
    TVector set = CreateVector(vector.Count, vector.Size);

    int index = 0;
    for (int i = 0; i < vector.Count; ++i)
    {
        long double mult = VectorMultiplication(min, max, *((TPoint*)GetNthElementVector(vector, i)));
        if (mult > 0)
        {
            AssignVector(vector.Size, GetNthElementVector(vector, i), GetNthElementVector(set, index));
            ++index;
        }
    }

    AssignVector(vector.Size, &min, GetNthElementVector(set, index));
    AssignVector(vector.Size, &max, GetNthElementVector(set, index + 1));
    set.Count = index + 2;
    
    return set;
}

static bool RotationCheck(TPoint a, TPoint b, TPoint c)
{
    return VectorMultiplication(a, b, c) > 0;
}

static TStack GrahamAlgorithm(TVector vector, int (*compare)(const void*, const void*))
{
    TStack stack = CreateStack(vector.Count, vector.Size);

    if (vector.Count == 0)
    {
        return stack;
    }
    else if (vector.Count == 1)
    {
        PushStack(vector.Array, &stack);
        return stack;
    }
    
    qsort(vector.Array, vector.Count, vector.Size, compare);

    PushStack(GetNthElementVector(vector, 0), &stack);
    PushStack(GetNthElementVector(vector, 1), &stack);

    for (int i = 2; i < vector.Count; ++i)
    {
        while (stack.Count > 1 && !RotationCheck(*((TPoint*)TopStack(stack)), *((TPoint*)GetNthElementVector(vector, i)), *((TPoint*)NextToTopSTack(stack))))
        {
            PopStack(&stack);
        }
        
        PushStack(GetNthElementVector(vector, i), &stack);
    }
    
    return stack;
}

void AndrewAlgorithm(TVector vector)
{
    if (vector.Count == 0)
    {
        return;
    }
    
    if (vector.Count == 1)
    {
        if (PrintPoint(vector.Array) == EOF)
        {
            OtherError(__FILE__, __LINE__);
        }
        return;
    }

    TPoint min = FindMin(vector);
    TPoint max = FindMax(vector);

    TVector lowerVector = CreateLowerVector(vector, min, max);
    TStack lowerStack = GrahamAlgorithm(lowerVector, ComparePointLower);
    DestroyVector(&lowerVector);
    PopStack(&lowerStack);
    PrintStack(lowerStack, PrintPoint);
    DestroyStack(&lowerStack);

    TVector upperVector = CreateUpperVector(vector, min, max);
    TStack upperStack = GrahamAlgorithm(upperVector, ComparePointUpper);
    DestroyVector(&upperVector);
    PopStack(&upperStack);
    PrintStack(upperStack, PrintPoint);
    DestroyStack(&upperStack);
}
