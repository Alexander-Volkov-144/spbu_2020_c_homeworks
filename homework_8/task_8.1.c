#include <stdio.h>
#include <stdlib.h>

#include "../library/dfa/dfa.h"

int main()
{
    DFAState* failState = createDFAState(0, false);
    DFAState* initialState = createDFAState(1, false);
    DFA* newDFA = createDFA(initialState);

    DFAState* firstState = createDFAState(2, false);
    DFAState* secondState = createDFAState(3, false);
    DFAState* thirdState = createDFAState(4, true);

    addTransition(initialState, 'a', firstState);
    addTransition(initialState, 'b', initialState);

    addTransition(firstState, 'a', firstState);
    addTransition(firstState, 'b', secondState);

    addTransition(secondState, 'a', firstState);
    addTransition(secondState, 'b', thirdState);

    addTransition(thirdState, 'a', firstState);
    addTransition(thirdState, 'b', initialState);

    printf("%d\n", isStringCorrect("a", newDFA) ? 1 : 0);
    printf("%d\n", isStringCorrect("0123a", newDFA) ? 1 : 0);
    printf("%d\n", isStringCorrect("abacaba", newDFA) ? 1 : 0);

    printf("%d\n", isStringCorrect("abb", newDFA) ? 1 : 0);
    printf("%d\n", isStringCorrect("ababb", newDFA) ? 1 : 0);
    printf("%d\n", isStringCorrect("abababb", newDFA) ? 1 : 0);

    return 0;
}