#include "../library/list/list.h"
#include <stdio.h>

int main()
{
    List* numbers = createList();

    // проверка работы функций на пустом списке
    head(numbers);
    tail(numbers);
    retrieve(numbers, 1);
    delete(numbers, 1);
    printf("\n");

    ListElement* number1 = createListElement(1); // создается элемент1
    ListElement* number2 = createListElement(2); // создается элемент2
    ListElement* number3 = createListElement(3); // создается элемент3
    ListElement* number4 = createListElement(4); // создается элемент4

    insert(number1, 0, numbers); // элемент1 добавляется в список
    printf("list size = %d\n", listSize(numbers)); // печатается размер списка
    printList(numbers); // печатается весь список
    printf("\n");

    // проверка работы функций на списке из 1 элемента
    printf("the value of the first element:%d\n", head(numbers)->value);
    printf("the value of the element at position 0: %d\n", retrieve(numbers, 0)->value);
    printf("the value of the last element: %d\n", tail(numbers)->value);
    printf("\n");

    insert(number2, 1, numbers); // элемент2 добавляется в список
    insert(number3, 2, numbers); // элемент3 добавляется в список
    printf("list size = %d\n", listSize(numbers)); // печатается размер списка
    printList(numbers); // печатается весь список
    printf("\n");

    insert(number4, 4, numbers); // попытка добавления элемента на неподходящую позицию
    printf("list size = %d\n", listSize(numbers)); // печатается размер списка
    printList(numbers); // печатается весь список
    printf("\n");

    insert(number4, 1, numbers); // добавления элемента4 в список на позицию 1
    printList(numbers); // печатается весь список
    printf("\n");

    // проверка работы функций
    printf("the value of the first element: %d\n", head(numbers)->value);
    printf("the value of the element at position 2: %d\n", retrieve(numbers, 2)->value);
    printf("the value of the last element: %d\n", tail(numbers)->value);
    printf("\n");

    printf("position of element with value 4: %d\n", locate(4, numbers));
    printf("position of element with value 5: %d\n", locate(5, numbers));
    printf("\n");

    delete (numbers, 2); // удаляется элемент на позиции 2
    printList(numbers); // печатается весь список

    deleteList(numbers); // удаляется список
    return 0;
}