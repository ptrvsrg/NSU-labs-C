#ifndef SUBJECT_H
#define SUBJECT_H

#include "error.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TSubject
{
    int Price;
    int Weight;
} TSubject;

TSubject CreateSubject(int price, int weight);
int ScanSubject(TSubject* subject);
int PrintSubject(const TSubject* subject);

#endif
