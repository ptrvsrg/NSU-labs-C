#include "input.h"

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

static bool IsOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')';
}

static void CheckBrackets(const char* infix)
{
    TStackPtr stack = CreateStack();

    for (int i = 0; infix[i] != '\0'; ++i)
    {
        if (infix[i] == ')')
        {
            if (!stack || i - PopStack(&stack).Number == 1)
            {
                DestroyStack(&stack);
                SyntaxError();
            }
        }
        else if (infix[i] == '(')
        {
            PushStack(&stack, CreateValue(infix[i], i));
        }
    }

    if (!IsEmptyStack(stack))
    {
        DestroyStack(&stack);
        SyntaxError();
    }
}

static void CheckSymbols(const char* infix)
{
    for (int i = 0; infix[i] != '\0'; ++i)
    {
        if (!IsOperator(infix[i]) && !IsDigit(infix[i]))
        {
            SyntaxError();
        }
    }
}

void InputInfix(char* infix, int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (fread(infix + i, sizeof(char), 1, stdin) != 1)
        {
            OtherError();
        }

        if (infix[i] == '\n')
        {
            infix[i] = '\0';
            break;
        }
    }

    if(infix[0] == '\0')
    {
        SyntaxError();
    }

    CheckSymbols(infix);
    CheckBrackets(infix);
}