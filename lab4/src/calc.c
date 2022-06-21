#include "calc.h"

static int OperatorPriority(char value)
{
    switch(value)
    {
        case '(': return 0;
        case '-': return 1;
        case '+': return 1; 
        case '*': return 2;     
        case '/': return 2;
    }

    return -1;
}

static void CalcExpression(TStackPtr* operatorStack, TStackPtr* numberStack)
{
    if (IsEmptyStack(*operatorStack) || IsEmptyStack(*numberStack) || IsEmptyStack((*numberStack)->Next))
    {
        DestroyStack(operatorStack);
        DestroyStack(numberStack);
        SyntaxError();
    }

    char operator = PopStack(operatorStack).Operator;
    int second = PopStack(numberStack).Number;
    int first = PopStack(numberStack).Number;

    switch(operator)
    {
        case '+': 
            PushStack(numberStack, CreateValue('\0', first + second));
            return;
        case '-': 
            PushStack(numberStack, CreateValue('\0', first - second));
            return;
        case '*': 
            PushStack(numberStack, CreateValue('\0', first * second));
            return;
        case '/':
            if(second == 0)
            {
                DestroyStack(operatorStack);
                DestroyStack(numberStack);
                DivisionByZero();
            }
            
            PushStack(numberStack, CreateValue('\0', first / second));
    }
}

static void CalcDigit(const char* infix, int* index, TStackPtr* numberStack)
{
    int number = atoi(infix + (*index));

    do
    {
        ++(*index);
    } while (IsDigit(infix[(*index)]));

    PushStack(numberStack, CreateValue('\0', number));
}

static void CalcEndBracket(TStackPtr* numberStack, TStackPtr* operatorStack)
{
    while(GetTopStack(*operatorStack).Operator != '(')
    {
        CalcExpression(operatorStack, numberStack);
    }

    PopStack(operatorStack);
}

static void CalcOperator(const char* infix, int index, TStackPtr* numberStack, TStackPtr* operatorStack)
{
    int priority1 = OperatorPriority(infix[index]);
    if (priority1 == -1)
    {
        DestroyStack(operatorStack);
        DestroyStack(numberStack);
        OtherError();
    }

    while (!IsEmptyStack(*operatorStack))
    {
        TValue value = GetTopStack(*operatorStack);

        int priority2 = OperatorPriority(value.Operator);
        if (priority2 == -1)
        {
            DestroyStack(operatorStack);
            DestroyStack(numberStack);
            OtherError();
        }

        if (priority1 > priority2)
        {
            break;
        }

        CalcExpression(operatorStack, numberStack);
    }

    PushStack(operatorStack, CreateValue(infix[index], INT_MIN));
}

int Calc(const char* infix) 
{
    TStackPtr operatorStack = CreateStack();
    TStackPtr numberStack = CreateStack();

    int index = 0;

    while (infix[index] != '\0')
    {
        if (IsDigit(infix[index]))
        {
            CalcDigit(infix, &index, &numberStack);
        }
        else if (infix[index] == '(')
        {
            PushStack(&operatorStack, CreateValue(infix[index], INT_MIN));
            ++index;
        }
        else if (infix[index] == ')')
        {
            CalcEndBracket(&numberStack, &operatorStack);
            ++index;
        }
        else
        {
            CalcOperator(infix, index, &numberStack, &operatorStack);
            ++index;
        }
    }

    while(!IsEmptyStack(operatorStack))
    {
        CalcExpression(&operatorStack, &numberStack);
    }

    TValue value = PopStack(&numberStack);
    
    DestroyStack(&operatorStack);
    DestroyStack(&numberStack);

    return value.Number;
}
