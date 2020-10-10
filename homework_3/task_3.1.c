#include "../library/list/list.h"
#include <stdio.h>

int main()
{
    List* numbers = createList();

    ListElement* number1 = createListElement(1); // создается элемент1

    insert(number1, 0, numbers); // элемент1 добавляется в список

    printList(numbers); // печатается весь список

    deleteList(numbers); // удаляется список
    return 0;
}