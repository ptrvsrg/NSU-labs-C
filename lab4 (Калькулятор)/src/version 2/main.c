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

struct TStack 
{
    char Value;
    struct TStack* Next;
};

typedef struct TStack* TStack;

TStack CreateStack() 
{
    return NULL;
}

bool IsEmpty(TStack stack)
{
    return stack == NULL;
}

void Remove(TStack* stack)
{
    assert(!IsEmpty(*stack));
    TStack last = *stack;
    *stack = (*stack)->Next;
    free(last);
}

char GetTop(TStack stack)
{
    assert(!IsEmpty(stack));
    return stack->Value;
}

char Pop(TStack* stack)
{
    assert(!IsEmpty(*stack));
    char top = GetTop(*stack);
    Remove(stack);
    return top;
}

void Push(TStack* stack, char value)
{
    TStack new = malloc(sizeof(*new));
    assert(new != NULL);
    TStack last = *stack;
    new->Value = value;
    new->Next = last;
    *stack = new;
}

void DestroyStack(TStack stack) 
{
    while (!IsEmpty(stack)) 
    {
        Remove(&stack);
    }
}

////////////////////////////////  INPUT - OUTPUT  ////////////////////////////////

bool IsDigit(char value)
{
    return value >= '0' && value <= '9';
}

bool IsOperator(char value)
{
    return value == '+' || value == '-' || value == '*' || value == '/';
}

int InputNotation(char* infixNotation)
{
    size_t beginBrackets = 0;
    size_t backBrackets = 0;
    size_t indexOperatorCount = -1;
    size_t indexBeginBrackets = SIZE_NOTATION;

    for (size_t i = 0; i < SIZE_NOTATION + 1; i++)
	{
		infixNotation[i] = getchar();

        switch(infixNotation[i])
        {
            case '\n':
                if (i == 0 || beginBrackets != backBrackets || i <= indexOperatorCount + 1)
                {
                    return SYNTAX_ERROR;
                }
                else
                {
                    infixNotation[i] = '\0';
                    return SUCCESS;
                }
            case EOF:
                return SYNTAX_ERROR;
            case '(':
                ++beginBrackets;
                indexBeginBrackets = i;
                break;
            case ')':
                if(i <= indexBeginBrackets + 1 || i <= indexOperatorCount + 1)
                {
                    return SYNTAX_ERROR;
                }
                ++backBrackets;
                break;
            default:
                if(IsDigit(infixNotation[i]))
                {
                    break;
                }
                else if (IsOperator(infixNotation[i]))
                {
                    if(i == indexOperatorCount + 1)
                    {
                        return SYNTAX_ERROR;
                    }
                    indexOperatorCount = i;
                    break;
                }
                return SYNTAX_ERROR;
        }

        if(i == SIZE_NOTATION)
        {
            return SYNTAX_ERROR;
        }
	}

    return SUCCESS;
}

void SyntaxError()
{
    printf("syntax error");
}

void DivisionByZero()
{
    printf("division by zero");
}

////////////////////////////////  POSTFIX NOTATION  ////////////////////////////////

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
    TStack operatorStack = CreateStack();
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

////////////////////////////////  CALCULATOR  ////////////////////////////////

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
        if (!IsEmpty(*numberStack) && GetTop(*numberStack) == '-')
        {
            number *= -1;
            break;
        }

        number += SymbolToNumber(Pop(numberStack)) * power;
        power *= 10;
    } while (!IsEmpty(*numberStack) && GetTop(*numberStack) != '|');

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
    TStack numberStack = CreateStack();
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

////////////////////////////////  MAIN  ////////////////////////////////

int main()
{
    char infixNotation [SIZE_NOTATION + 1];
    
    if(InputNotation(infixNotation) == SYNTAX_ERROR)
    {
        SyntaxError();
        return SUCCESS;
    }

    int errorControl = SUCCESS;
    int value = Calc(infixNotation, &errorControl);

    switch(errorControl)
    {
        case SUCCESS:
            printf("%d", value);
            return SUCCESS;
        case DIVISION_BY_ZERO: 
            DivisionByZero();
            return SUCCESS;
        case SYNTAX_ERROR: 
            SyntaxError();
            return SUCCESS;
    }
}