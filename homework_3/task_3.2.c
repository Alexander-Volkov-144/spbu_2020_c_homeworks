#include "../library/list/list.h"
#include <stdio.h>

List* createListWithPositions(int n)
{
    List* positions = createList();
    for (int i = 0; i < n; ++i) {
        ListElement* temporary = createListElement(i + 1);
        insert(temporary, i, positions);
    }
    return positions;
}

ListElement* searchNext(List* list, ListElement* current, int m)
{
    while (m > 0) {
        if (current->next == NULL)
            current = list->head;
        else
            current = current->next;
        if (current->value > 0) {
            --m;
        }
    }
    return current;
}

int searchForWinPosition(List* positions, int n, int m)
{
    ListElement* current = tail(positions);
    while (n > 1) {
        current = searchNext(positions, current, m);
        current->value *= -1;
        --n;
    }
    return searchNext(positions, current, m)->value;
}

int main()
{
    int m = 0, n = 0;
    printf("enter the number of people\n");
    scanf("%d", &n);
    printf("enter m (every m-th person dies)\n");
    scanf("%d", &m);
    List* positions = createListWithPositions(n);
    printf("winning position: %d", searchForWinPosition(positions, n, m));
    deleteList(positions);
    return 0;
}