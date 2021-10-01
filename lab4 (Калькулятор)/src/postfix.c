#include "calc.h"

int OperatorPriority(char value)
{
    switch(value)
    {
        case '(': return 0;
        case '-': return 1;
        case '+': return 1; 
        case '*': return 2;     
        case '/': return 2;
        default: assert(false);
    }
    return FAILURE;
}

void GetPostfixNotation(const char* infixNotation, char* postfixNotation) 
{
    TStack operatorStack;
    CreateStack(&operatorStack);
    size_t index = 0;

    while(infixNotation[index] != '\0')
    {
        if(IsDigit(infixNotation[index]))
        {
            do
            {
                *postfixNotation = infixNotation[index];
                ++postfixNotation;
                ++index;
            } while (IsDigit(infixNotation[index]));
            
            *postfixNotation = '|';
            ++postfixNotation;
        }
        else
        {
            if(infixNotation[index] == '(')
            {
                Push(&operatorStack, infixNotation[index]);
            }
            else if(infixNotation[index] == ')')
            {
                while(GetTop(operatorStack) != '(')
                {
                    *postfixNotation = Pop(&operatorStack);
                    ++postfixNotation;
                }

                Remove(&operatorStack);
            }
            else
            {
                while(!IsEmpty(operatorStack) && OperatorPriority(GetTop(operatorStack)) >= OperatorPriority(infixNotation[index]))
                {
                    *postfixNotation = Pop(&operatorStack);
                    ++postfixNotation;
                }

                Push(&operatorStack, infixNotation[index]);
            }

            ++index;
        }
    }

    while(!IsEmpty(operatorStack))
    {
        *postfixNotation = Pop(&operatorStack);
        ++postfixNotation;
    }

    *postfixNotation = '\0';

    DestroyStack(operatorStack);
}