#include "../library/dfa/dfa.h"
#include "../library/stringManipulations/stringManipulations.h"
#include <stdio.h>
#include <stdlib.h>

void addStatesAndTransitions(DFAState** states)
{
    DFAState* initialState = states[0] = createDFAState(false);
    DFAState* signInIntegerPart = states[1] = createDFAState(false);
    DFAState* digitInIntegerPart = states[2] = createDFAState(true);
    DFAState* dot = states[3] = createDFAState(false);
    DFAState* digitInFractionalPart = states[4] = createDFAState(true);
    DFAState* exponent = states[5] = createDFAState(false);
    DFAState* signInExponent = states[6] = createDFAState(false);
    DFAState* digitInExponent = states[7] = createDFAState(true);

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
}

bool checkString(char* string)
{
    int numberOfStates = 8;
    DFAState** states = (DFAState**)malloc(sizeof(DFAState*) * numberOfStates);
    addStatesAndTransitions(states);

    DFA* dfa = createDFA(states[0]); // states[0] - initialState

    bool isCorrect = isStringCorrect(string, dfa);

    deleteDFAStates(states, numberOfStates);
    free(states);
    removeDFA(dfa);

    return isCorrect;
}

int main()
{
    printf("enter the expression\n");
    char* string = readString();
    if (checkString(string))
        printf("the entered string is a number\n");
    else
        printf("the entered string is not a number\n");
    free(string);
    return 0;
}
