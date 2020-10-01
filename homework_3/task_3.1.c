#include "../library/list/list.h"
#include <stdio.h>

int main()
{
    List* numbers = createList();
    ListElement* number1 = createListElement(1); // создается элемент1
    ListElement* number2 = createListElement(2); // создается элемент2
    ListElement* number3 = createListElement(3); // создается элемент3
    ListElement* number4 = createListElement(4); // создается элемент4
    insert(number1, 1, numbers); // элемент1 добавляется в список
    insert(number2, 2, numbers); // элемент1 добавляется в список
    insert(number3, 3, numbers); // элемент1 добавляется в список
    printList(numbers); // печатается весь список
    printf("the value of the first element:%d\n", head(numbers)->value);
    printf("the value of the element at position 2: %d\n", retrieve(numbers, 2)->value);
    printf("the value of the last element: %d\n", tail(numbers)->value);
    printf("position of element with value 2: %d\n", locate(number2, numbers));
    printf("position of element with value 4: %d\n", locate(number4, numbers));
    delete(numbers, 1);
    printList(numbers); // печатается весь список
    delete(numbers, 2);
    printList(numbers); // печатается весь список
    insert(number4, 2, numbers); // на позицию 2 добавляется элемент
    printList(numbers); // печатается весь список
    printf("position of element with value 4: %d\n", locate(number4, numbers));
    deleteList(numbers); // удаляется список
    return 0;
}