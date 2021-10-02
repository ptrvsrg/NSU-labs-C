#include "calc.h"

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
