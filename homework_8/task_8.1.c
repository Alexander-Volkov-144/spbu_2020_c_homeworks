#include <stdio.h>
#include "../library/dfa/dfa.h"
#include "../library/stringManipulations/stringManipulations.h"
#include <stdlib.h>

DFA* constructDfa()
{
    DFAState* initialState = createDFAState(false);
    DFA* newDFA = createDFA(initialState);

    DFAState* signInIntegerPart = createDFAState(false);
    DFAState* digitInIntegerPart = createDFAState(true);
    DFAState* dot = createDFAState(false);
    DFAState* digitInFractionalPart = createDFAState(true);
    DFAState* exponent = createDFAState(false);
    DFAState* signInExponent = createDFAState(false);
    DFAState* digitInExponent = createDFAState(true);

    addTransition(initialState, '+', signInIntegerPart);
    addTransition(initialState, '-', signInIntegerPart);
    addTransition(digitInIntegerPart, '.', dot);
    addTransition(digitInIntegerPart, 'E', exponent);
    addTransition(digitInFractionalPart, 'E', exponent);
    addTransition(exponent, '+', signInExponent);
    addTransition(exponent, '-', signInExponent);

    for (char digit = '0'; (int)digit <= (int)'9'; ++digit) {
        addTransition(signInIntegerPart, digit, digitInIntegerPart);
        addTransition(initialState, digit, digitInIntegerPart);
        addTransition(digitInIntegerPart, digit, digitInIntegerPart);
        addTransition(dot, digit, digitInFractionalPart);
        addTransition(digitInFractionalPart, digit, digitInFractionalPart);
        addTransition(signInExponent, digit, digitInExponent);
        addTransition(exponent, digit, digitInExponent);
        addTransition(digitInExponent, digit, digitInExponent);
    }
    return newDFA;
}

int main()
{
    DFA* dfa = constructDfa();
    printf("enter the expression\n");
    char* string = readString();
    if (isStringCorrect(string, dfa))
        printf("the entered string is a number\n");
    else
        printf("the entered string is not a number\n");
    free(string);
    return 0;
}