#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "stack.h"

typedef struct
{
    char Operator;
    int Number;
} TValue;

struct TStack 
{
    TValue Value;
    struct TStack* Next;
};

typedef struct TStack* TStackPtr;

TValue CreateValue(char op, int number);
TStackPtr CreateStack(void);
bool IsEmptyStack(TStackPtr stack);
TValue GetTopStack(TStackPtr stack);
TValue PopStack(TStackPtr* stack);
void PushStack(TStackPtr* stack, TValue value);
void DestroyStack(TStackPtr* stack);

#endif