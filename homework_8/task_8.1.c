#include <stdio.h>
#include "../library/dfa/dfa.h"

DFA* constructDfa(){
    DFAState* initialState = createDFAState(false);
    DFA* newDFA = createDFA(initialState);

    DFAState* signInIntegerPart = createDFAState(false);
    DFAState* digitInIntegerPart = createDFAState(true);
    DFAState* digitInFractionalPart = createDFAState(true);
    DFAState* exponent = createDFAState(false);
    DFAState* signInExponent = createDFAState(false);
    DFAState* digitInExponent = createDFAState(true);

    addTransition(initialState, '+', signInIntegerPart);
    addTransition(initialState, '-', signInIntegerPart);
    addTransition(digitInIntegerPart, '.', digitInFractionalPart);
    addTransition(digitInFractionalPart, 'E', exponent);
    addTransition(exponent, '+', signInExponent);
    addTransition(exponent, '-', signInExponent);

    for(char digit = '0'; digit <= '9'; ++digit){
        addTransition(initialState, digit, digitInIntegerPart);
        addTransition(signInIntegerPart, digit, digitInIntegerPart);
        addTransition(digitInIntegerPart, digit, digitInIntegerPart);
        addTransition(digitInFractionalPart, digit, digitInFractionalPart);
        addTransition(signInExponent, digit, digitInExponent);
        addTransition(digitInExponent, digit, digitInExponent);
    }
    return newDFA;
}

int main()
{
    //DFA* dfa = constructDfa();
    char* string = NULL;
    printf("enter the expression\n");
    return 0;
}