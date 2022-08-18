#ifndef POINT_H
#define POINT_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    int X;
    int Y;
} TPoint;

int ScanPoint(void* value);
int PrintPoint(const void*  value);
int ComparePointX(const void* a, const void* b);
int ComparePointY(const void* a, const void* b);

#endif 
