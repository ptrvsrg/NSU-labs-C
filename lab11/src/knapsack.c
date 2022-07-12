#define _CRT_SECURE_NO_WARNINGS
#include "knapsack.h"
#define POSSIBLE (char)1
#define IMPOSSIBLE (char)0

static const int* MaxInt(const int* a, const int* b)
{
    return (*a >= *b) ? a : b;
}

TTable CreateMemTable(int maxWeight, TVector subjectVector)
{
    TTable memTable = CreateTable(subjectVector.Count, maxWeight, sizeof(int));

    TSubject* subject = GetVectorValue(0, subjectVector);
    for (int j = 0; j < memTable.Column; ++j)
    {
        int nullValue = 0;
        if (subject->Weight > j + 1)
        {
            SetTableValue(&nullValue, 0, j, &memTable);
        }
        else
        {
            SetTableValue(&subject->Price, 0, j, &memTable);
        }
    }

    for (int i = 1; i < memTable.Row; ++i)
    {
        subject = GetVectorValue(i, subjectVector);
        for (int j = 0; j < memTable.Column; ++j)
        {
            if (subject->Weight > j + 1)
            {
                SetTableValue(GetTableValue(i - 1, j, memTable), i, j, &memTable);
            }
            else if (subject->Weight == j + 1)
            {
                const int* value = MaxInt(&subject->Price, GetTableValue(i - 1, j, memTable));
                SetTableValue(value, i, j, &memTable);
            } 
            else
            {
                int sum = subject->Price + *((int*)GetTableValue(i - 1, j - subject->Weight, memTable));
                const int* value = MaxInt(&sum, GetTableValue(i - 1, j, memTable));
                SetTableValue(value, i, j, &memTable);
            }
        }
    }

    return memTable;
}

void PrintMaxPrice(TTable memTable)
{
    printf("%d\n", *((int*)GetTableValue(memTable.Row - 1, memTable.Column - 1, memTable)));
}

void PrintKnapsack(TVector subjectVector, TTable memTable, int (*print)(const void*))
{
    int currentRow = memTable.Row;
    int currentColumn = memTable.Column;

    while (currentColumn != 0)
    {
        int* value1 = GetTableValue(currentRow - 1, currentColumn - 1, memTable);
        if (currentRow == 1)
        {
            if (*value1 != 0)
            {
                TSubject* subject = GetVectorValue(currentRow - 1, subjectVector);
                if (print(subject) <= 0)
                {
                    OtherError(__FILE__, __LINE__);
                }
            }

            return;
        }

        int* value2 = GetTableValue(currentRow - 2, currentColumn - 1, memTable);
        if (*value1 != *value2)
        {
            TSubject* subject = GetVectorValue(currentRow - 1, subjectVector);
            if (print(subject) <= 0)
            {
                OtherError(__FILE__, __LINE__);
            }

            currentColumn -= subject->Weight;
        }
        
        --currentRow;
    }
}