#ifndef SPBU_2020_C_HOMEWORKS_DFA_H
#define SPBU_2020_C_HOMEWORKS_DFA_H

#include "stdbool.h"

typedef struct DFAState DFAState;

typedef struct DFA DFA;

DFA* createDFA(DFAState* initialState);

void removeDFA(DFA* dfa);

DFAState* createDFAState(bool isFinal);

void removeDFAState(DFAState* dfaState);

void addTransition(DFAState* firstState, char value, DFAState* secondState);

bool isStringCorrect(char* string, DFA* dfa);

#endif //SPBU_2020_C_HOMEWORKS_DFA_H
