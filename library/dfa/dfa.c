#include "dfa.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transition {
    char symbol;
    DFAState* transitionState;
} Transition;

struct DFAState {
    bool isFinal;
    int transitionsSize;
    int transitionAllocationSize;
    Transition** transitions;
};

struct DFA {
    DFAState* initialState;
    DFAState* failState;
};

Transition* createTransition(char symbol, DFAState* transitionState)
{
    Transition* transition = (Transition*)malloc(sizeof(Transition));
    transition->symbol = symbol;
    transition->transitionState = transitionState;

    return transition;
}

DFA* createDFA(DFAState* initialState)
{
    DFA* dfa = (DFA*)malloc(sizeof(DFA));
    dfa->initialState = initialState;
    dfa->failState = createDFAState(false);

    return dfa;
}

DFAState* createDFAState(bool isFinal)
{
    DFAState* dfaState = (DFAState*)malloc(sizeof(DFAState));
    dfaState->isFinal = isFinal;
    dfaState->transitionsSize = 0;
    dfaState->transitionAllocationSize = 1;
    dfaState->transitions = (Transition**)calloc(1, sizeof(Transition*));
    return dfaState;
}

void removeDFA(DFA* dfa)
{
    removeDFAState(dfa->failState);
    free(dfa);
}

void reallocTransition(DFAState* dfaState)
{
    dfaState->transitions = realloc(dfaState->transitions, dfaState->transitionAllocationSize * 2 * sizeof(Transition*));
    memset(dfaState->transitions + dfaState->transitionAllocationSize, 0, dfaState->transitionAllocationSize * sizeof(Transition*));
    dfaState->transitionAllocationSize *= 2;
}

void removeDFAState(DFAState* dfaState)
{
    for (int i = 0; i < dfaState->transitionsSize; ++i) {
        free(dfaState->transitions[i]);
    }
    free(dfaState->transitions);
    free(dfaState);
}

void addTransition(DFAState* firstState, char value, DFAState* secondState)
{
    Transition* newTransition = createTransition(value, secondState);
    if (firstState->transitionAllocationSize == firstState->transitionsSize) {
        reallocTransition(firstState);
    }
    firstState->transitions[firstState->transitionsSize] = newTransition;
    firstState->transitionsSize++;
}

bool isStringCorrect(char* string, DFA* dfa)
{
    DFAState* currentDfaState = dfa->initialState;
    for (int i = 0; i < strlen(string); ++i) {
        bool isSymbolFound = false;
        for (int j = 0; j < currentDfaState->transitionsSize; ++j) {
            if (currentDfaState->transitions[j]->symbol == string[i]) {
                currentDfaState = currentDfaState->transitions[j]->transitionState;
                isSymbolFound = true;
                break;
            }
        }
        if (!isSymbolFound)
            currentDfaState = dfa->failState;
    }

    return currentDfaState->isFinal;
}
