#ifndef CALC
#define CALC
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    SIZE_NOTATION = 1000,
    SUCCESS = 0,
    FAILURE = -1,
    SYNTAX_ERROR = -2,
    DIVISION_BY_ZERO = -3
};

////////////////////////////////  STACK  ////////////////////////////////

typedef struct TStack 
{
    char Values[2 * SIZE_NOTATION];
    size_t position;
} TStack;

void CreateStack(TStack* stack);// 

void Remove(TStack* stack);

char GetTop(TStack* stack);

char Pop(TStack* stack);

void Push(TStack* stack, char value);

bool IsEmpty(TStack stack);

void DestroyStack(TStack stack);

////////////////////////////////  INPUT - OUTPUT  ////////////////////////////////

bool IsDigit(char value);

int InputNotation(char* infixNotation);

void SyntaxError();

void DivisionByZero();

////////////////////////////////  POSTFIX NOTATION  ////////////////////////////////

int OperatorPriority(char value);

void GetPostfixNotation(const char* infixNotation, char* postfixNotation);

////////////////////////////////  CALCULATOR  ////////////////////////////////

int Fabs(int value);

int SymbolToNumber(char symbol);

char NumberToSymbol(int digit);

int GetNumberToString(TStack* numberStack);

void GetStringToNumber(int value, TStack* numberStack);

int GetExpressionValue(char operator, int first, int second, int* errorControl);

int Calc(const char* infixNotation, int* errorControl);

#endif
