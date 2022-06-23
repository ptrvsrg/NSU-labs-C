#define _CRT_SECURE_NO_WARNINGS
#include "point.h"

int ScanPoint(void* value)
{
    TPoint* point = (TPoint*)value;
    int control = scanf("%d %d", &point->X, &point->Y);
    return (control == 2) ? 1 : EOF;
}

int PrintPoint(const void*  value)
{
    TPoint* point = (TPoint*)value;
    return printf("%d %d\n", point->X, point->Y);
}

int ComparePointX(const void* a, const void* b)
{
    const TPoint* A = a;
    const TPoint* B = b;

    long long difference = (long long)A->X - B->X;

    return (difference > 0) ? 1 : (difference == 0) ? 0 : -1;
}

int ComparePointY(const void* a, const void* b)
{
    const TPoint* A = a;
    const TPoint* B = b;

    long long difference = (long long)A->Y - B->Y;

    return (difference > 0) ? 1 : (difference == 0) ? 0 : -1;
}
