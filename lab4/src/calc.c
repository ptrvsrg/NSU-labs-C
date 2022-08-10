#include "calc.h"

static int OperatorPriority(char data)
{
    switch(data)
    {
        case '(': return 0;
        case '-': return 1;
        case '+': return 1;
        case '*': return 2;
        case '/': return 2;
    }

    return -1;
}

static void CalcExpression(TStack* operatorStack, TStack* numberStack)
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
            PushStack(CreateData(first + second, '\0'), numberStack);
            return;
        case '-':
            PushStack(CreateData(first - second, '\0'), numberStack);
            return;
        case '*':
            PushStack(CreateData(first * second, '\0'), numberStack);
            return;
        case '/':
            if(second == 0)
            {
                DestroyStack(operatorStack);
                DestroyStack(numberStack);
                DivisionByZero();
            }

            PushStack(CreateData(first / second, '\0'), numberStack);
    }
}

static void CalcBeginBracket(TStack* operatorStack, TString* infix)
{
    if (IsEmptyString(*infix) || ExtractSymbol(infix) == ')')
    {
        SyntaxError();
    }

    --infix->BeginIndex;
    PushStack(CreateData(0, '('), operatorStack);
}

static void CalcEndBracket(TStack* numberStack, TStack* operatorStack)
{
    if (IsEmptyStack(*numberStack))
    {
        SyntaxError();
    }

    while (!IsEmptyStack(*operatorStack) && GetTopStack(*operatorStack).Operator != '(')
    {
        CalcExpression(operatorStack, numberStack);
    }

    if (IsEmptyStack(*operatorStack))
    {
        SyntaxError();
    }

    PopStack(operatorStack);
}

static void CalcOperator(TData data, TStack* numberStack, TStack* operatorStack)
{
    int priority1 = OperatorPriority(data.Operator);
    if (priority1 == -1)
    {
        DestroyStack(operatorStack);
        DestroyStack(numberStack);
        OtherError(__FILE__, __LINE__);
    }

    while (!IsEmptyStack(*operatorStack))
    {
        TData stackData = GetTopStack(*operatorStack);

        int priority2 = OperatorPriority(stackData.Operator);
        if (priority2 == -1)
        {
            DestroyStack(operatorStack);
            DestroyStack(numberStack);
            OtherError(__FILE__, __LINE__);
        }

        if (priority1 > priority2)
        {
            break;
        }

        CalcExpression(operatorStack, numberStack);
    }

    PushStack(data, operatorStack);
}

int Calc(void)
{
    TStack operatorStack = CreateStack();
    TStack numberStack = CreateStack();

    TString infix = CreateString();
    InputString(&infix);
    if (IsEmptyString(infix))
    {
        SyntaxError();
    }

    while (!IsEmptyString(infix))
    {
        TData data = GetData(&infix);

        if (data.Operator == '\0')
        {
            PushStack(data, &numberStack);
        }
        else if (data.Operator == '(')
        {
            CalcBeginBracket(&operatorStack, &infix);
        }
        else if (data.Operator == ')')
        {
            CalcEndBracket(&numberStack, &operatorStack);
        }
        else
        {
            CalcOperator(data, &numberStack, &operatorStack);
        }
    }

    while(!IsEmptyStack(operatorStack))
    {
        CalcExpression(&operatorStack, &numberStack);
    }

    TData result = PopStack(&numberStack);

    DestroyStack(&operatorStack);
    DestroyStack(&numberStack);

    return result.Number;
}
