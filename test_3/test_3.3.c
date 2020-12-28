#include "../library/dfa/dfa.h"
#include "../library/stringManipulations/stringManipulations.h"
#include <stdio.h>
#include <stdlib.h>

void addStatesAndTransitions(DFAState** states)
{
    DFAState* initialState = states[0] = createDFAState(false);
    DFAState* firstPart = states[1] = createDFAState(false);
    DFAState* atSign = states[2] = createDFAState(false);
    DFAState* otherCharacters = states[3] = createDFAState(false);
    DFAState* dots = states[4] = createDFAState(false);
    DFAState* possibleLastCharacters = states[5] = createDFAState(true);
    for (int i = 0; i < 26; ++i) {
        addTransition(initialState, (char)('A' + i), firstPart);
        addTransition(firstPart, (char)('A' + i), firstPart);
        addTransition(atSign, (char)('A' + i), possibleLastCharacters);
        addTransition(possibleLastCharacters, (char)('A' + i), possibleLastCharacters);
        addTransition(dots, (char)('A' + i), possibleLastCharacters);
    }
    for (int i = 0; i < 10; ++i) {
        addTransition(initialState, (char)('0' + i), firstPart);
        addTransition(firstPart, (char)('0' + i), firstPart);
        addTransition(atSign, (char)('0' + i), otherCharacters);
        addTransition(possibleLastCharacters, (char)('0' + i), otherCharacters);
        addTransition(otherCharacters, (char)('0' + i), otherCharacters);
        addTransition(dots, (char)('0' + i), otherCharacters);
    }

    addTransition(initialState, '.', firstPart);
    addTransition(firstPart, '.', firstPart);
    addTransition(possibleLastCharacters, '.', dots);
    addTransition(otherCharacters, '.', dots);

    addTransition(initialState, '%', firstPart);
    addTransition(firstPart, '%', firstPart);

    addTransition(initialState, '_', firstPart);
    addTransition(firstPart, '_', firstPart);

    addTransition(initialState, '+', firstPart);
    addTransition(firstPart, '+', firstPart);

    addTransition(initialState, '-', firstPart);
    addTransition(firstPart, '-', firstPart);
    addTransition(atSign, '-', otherCharacters);
    addTransition(otherCharacters, '-', otherCharacters);
    addTransition(dots, '-', otherCharacters);
    addTransition(possibleLastCharacters, '-', otherCharacters);

    addTransition(firstPart, '@', atSign);
}

bool checkString(char* string)
{
    int numberOfStates = 6;
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
    printf("enter string\n");
    char* string = readString();
    if (checkString(string))
        printf("the entered string is correct\n");
    else
        printf("the entered string isn't correct\n");
    free(string);
    return 0;
}
