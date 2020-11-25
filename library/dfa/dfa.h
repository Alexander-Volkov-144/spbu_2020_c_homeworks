#ifndef SPBU_2020_C_HOMEWORKS_DFA_H
#define SPBU_2020_C_HOMEWORKS_DFA_H

#include "stdbool.h"

typedef struct DFAState DFAState;

typedef struct DFA DFA;

DFA* createDFA(DFAState* initialState);

DFAState* createDFAState(bool isFinal);

void addTransition(DFAState* firstState, char value, DFAState* secondState);

bool isStringCorrect(char* string, DFA* dfa);

void printDFATransitions(DFA* dfa);

#endif //SPBU_2020_C_HOMEWORKS_DFA_H
