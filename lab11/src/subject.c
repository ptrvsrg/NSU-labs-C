#define _CRT_SECURE_NO_WARNINGS
#include "subject.h"

TSubject CreateSubject(int price, int weight)
{
    TSubject subject = { 
        .Weight = weight,
        .Price = price
        };
        
    return subject;
}

int ScanSubject(void* value)
{
    TSubject* subject = (TSubject*)value;
    int status = scanf("%d%d", &subject->Weight, &subject->Price);

    if (subject->Weight < 0 || subject->Price < 0)
    {
        return 0;
    }

    return (status == 2) ? 1 :
    (status == EOF) ? EOF : 0;
}

int PrintSubject(const void* value)
{
    TSubject* subject = (TSubject*)value;
    int status = printf("%d %d\n", subject->Weight, subject->Price);

    if (subject->Weight < 0 || subject->Price < 0)
    {
        return 0;
    }

    return status;
}
