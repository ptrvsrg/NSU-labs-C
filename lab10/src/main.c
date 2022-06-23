#define _CRT_SECURE_NO_WARNINGS
#include "andrew.h"
#include "error.h"
#include "vector.h"

#define MAX_POINT_COUNT (int)100000

int main(void)
{
    int count = 0;
    if (scanf("%d", &count) == EOF)
    {
        BadNumberOfLinesError();
    }

    if (count < 0 || count > MAX_POINT_COUNT)
    {
        BadNumberOfPointsError();
    }

    TVector vector = InputVector(count, sizeof(TPoint), ScanPoint);
    AndrewAlgorithm(vector);
    DestroyVector(&vector);

    return EXIT_SUCCESS;
}
