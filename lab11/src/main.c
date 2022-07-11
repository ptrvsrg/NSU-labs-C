#define _CRT_SECURE_NO_WARNINGS
#include "knapsack.h"
#include "subject.h"
#include "vector.h"
#include <stdlib.h>

int main(void) 
{
    int subjectCount = 0;
    if (scanf("%d", &subjectCount) != 1)
    {
        return EXIT_FAILURE;
    }
    
    int maxWeight = 0;
    if (scanf("%d", &maxWeight) != 1)
    {
        return EXIT_FAILURE;
    }

    TVector subjectVector = ScanReverseVector(sizeof(TSubject), subjectCount, ScanSubject);

    TTable memTable = CreateMemTable(maxWeight, subjectVector);

    PrintMaxPrice(memTable);
    PrintKnapsack(subjectVector, memTable, PrintSubject);

    DestroyTable(&memTable);
    DestroyVector(&subjectVector);

    return EXIT_SUCCESS;
}
