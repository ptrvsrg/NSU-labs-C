#include "calc.h"

int main()
{
    char infixNotation[SIZE_NOTATION + 1];

    if (InputNotation(infixNotation) == SYNTAX_ERROR)
    {
        SyntaxError();
        return SUCCESS;
    }

    int errorControl = SUCCESS;
    int value = Calc(infixNotation, &errorControl);

    switch (errorControl)
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