#include "../library/list/list.h"
#include <stdio.h>

List* createListWithPositions(int numberOfPeople)
{
    List* positions = createList();
    for (int i = 0; i < numberOfPeople; ++i) {
        ListElement* elementForThisPosition = createListElement(i + 1);
        insert(elementForThisPosition, i, positions);
    }
    return positions;
}

ListElement* searchNext(List* positions, ListElement* retiringPosition, int periodicityOfDropout)
{
    while (periodicityOfDropout > 0) {
        if (!isNextElementExist(retiringPosition))
            retiringPosition = head(positions);
        else
            retiringPosition = nextElement(retiringPosition);
        if (returnElementValue(retiringPosition) > 0) {
            --periodicityOfDropout;
        }
    }
    return retiringPosition;
}

int searchForWinPosition(List* positions, int numberOfPeople, int periodicityOfDropout)
{
    ListElement* retiringPosition = tail(positions);
    while (numberOfPeople > 1) {
        retiringPosition = searchNext(positions, retiringPosition, periodicityOfDropout);
        changeElementValue(retiringPosition, returnElementValue(retiringPosition) * -1);
        --numberOfPeople;
    }
    return returnElementValue(searchNext(positions, retiringPosition, periodicityOfDropout));
}

int main()
{
    int periodicityOfDropout = 0, numberOfPeople = 0;
    printf("enter the number of people\n");
    scanf("%d", &numberOfPeople);
    printf("enter m (every m-th person dies)\n");
    scanf("%d", &periodicityOfDropout);
    List* positions = createListWithPositions(numberOfPeople);
    printf("winning position: %d", searchForWinPosition(positions, numberOfPeople, periodicityOfDropout));
    deleteList(positions);
    return 0;
}
