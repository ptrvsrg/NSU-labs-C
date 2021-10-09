#include "calc.h"

int Fabs(int value)
{
    return (value >= 0) ? value : -value;
}

int SymbolToNumber(char symbol)
{
    return symbol - '0';
}

char NumberToSymbol(int digit)
{
    return digit + '0';
}

int GetNumberToString(TStack* numberStack)
{
    Remove(numberStack);

    int number = 0;
    int power = 1;

    do
    {
        if (!IsEmpty(*numberStack) && GetTop(numberStack) == '-')
        {
            number *= -1;
            break;
        }

        number += SymbolToNumber(Pop(numberStack)) * power;
        power *= 10;
    } while (!IsEmpty(*numberStack) && GetTop(numberStack) != '|');

    return number;  
}

void GetStringToNumber(int value, TStack* numberStack)
{
    if(value != Fabs(value))
    {
        value *= -1;
        Push(numberStack, '-');
    }

    int power = 1;

    while(value > power * 10)
    {
        power *= 10;
    }

    while (power != 0)
    {
        Push(numberStack, NumberToSymbol(value / power));
        value %= power;
        power /= 10;
    }

    Push(numberStack, '|');
}

int GetExpressionValue(char operator, int first, int second, int* errorControl)
{
    switch(operator)
    {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            if(second == 0)
            {
                *errorControl = DIVISION_BY_ZERO;
                return 0;
            }
            return first / second;
        default: assert(false);
    }
    return FAILURE;
}

int Calc(const char* infixNotation, int* errorControl)
{
    TStack numberStack; 
    CreateStack(&numberStack);
    char postfixNotation[SIZE_NOTATION * 2];

    GetPostfixNotation(infixNotation, postfixNotation);

    size_t index = 0;

    while(postfixNotation[index] != '\0')
    {
        if(IsDigit(postfixNotation[index]))
        {
            do
            {
                Push(&numberStack, postfixNotation[index]);
                ++index;
            } while (postfixNotation[index] != '|');

            Push(&numberStack, postfixNotation[index]);
        }
        else
        {
            int a = GetNumberToString(&numberStack);
            int b = GetNumberToString(&numberStack);
            int c = GetExpressionValue(postfixNotation[index], b, a, errorControl);

            if(*errorControl != SUCCESS)
            {
                return 0;
            }

            GetStringToNumber(c, &numberStack);
        }

        ++index;
    }

    int answer = GetNumberToString(&numberStack);
    DestroyStack(numberStack);

    return answer;
}
