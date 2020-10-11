#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    struct ListElement* next;
};

struct List {
    ListElement* head;
    int size;
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

ListElement* createListElement(int value)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    element->value = value;
    element->next = NULL;
    return element;
}

ListElement* tail(List* list)
{
    if (listSize(list) == 0) {
        printf("error, the list is empty\n");
        return NULL;
    }
    ListElement* supposedTailElement = list->head;
    while (supposedTailElement->next != NULL) {
        supposedTailElement = supposedTailElement->next;
    }
    return supposedTailElement;
}

ListElement* head(List* list)
{
    if (listSize(list) == 0) {
        printf("error, the list is empty\n");
        return NULL;
    }
    return list->head;
}

bool insert(ListElement* element, int position, List* list)
{
    if (position > listSize(list) || position < 0)
        return false;
    if (position == 0) {
        element->next = list->head;
        list->head = element;
        list->size++;
        return true;
    }
    ListElement* currentElement = list->head;
    for (int i = 0; i < position - 1; ++i) {
        currentElement = currentElement->next;
    }
    element->next = currentElement->next;
    currentElement->next = element;
    list->size++;
    return true;
}

int locateByValue(int elementValue, List* list) // для значения
{
    ListElement* currentElement = list->head;
    int position = 0;
    while (currentElement != NULL) {
        if (currentElement->value == elementValue)
            return position;
        currentElement = currentElement->next;
        ++position;
    }
    return -1; // в списке нет элемента с таким значением
}

int locate(ListElement* value, List* list) // для элемента
{
    ListElement* current = list->head;
    int position = 0;
    while (current != NULL) {
        if (current->value == value->value)
            return position;
        current = current->next;
        ++position;
    }
    return -1; // в списке нет элемента с таким значением
}

ListElement* retrieve(List* list, int position)
{
    if (position >= listSize(list) || position < 0)
        return NULL;
    ListElement* elementAtThisPosition = list->head;
    for (int i = 0; i != position && elementAtThisPosition != NULL; i++) {
        elementAtThisPosition = elementAtThisPosition->next;
    }
    return elementAtThisPosition;
}

bool delete (List* list, int position)
{
    if (position >= listSize(list) || position < 0)
        return false;
    ListElement* toDelete = NULL;
    if (position == 0) {
        toDelete = list->head;
        list->head = toDelete->next;
        free(toDelete);
        list->size--;
        return true;
    }
    ListElement* previous = retrieve(list, position - 1);
    toDelete = previous->next;
    previous->next = toDelete->next;
    free(toDelete);
    list->size--;
    return true;
}

void printList(List* list)
{
    printf("START -> ");
    ListElement* toPrint = list->head;
    while (toPrint != NULL) {
        printf("%d -> ", toPrint->value);
        toPrint = toPrint->next;
    }
    printf("END\n");
}

bool deleteList(List* list)
{
    ListElement* currentElement = list->head;
    ListElement* toDelete = NULL;
    while (currentElement != NULL) {
        toDelete = currentElement;
        currentElement = currentElement->next;
        free(toDelete);
    }
    free(list);
    return true;
}

int returnElementValue(ListElement* element)
{
    if (element == NULL) {
        printf("error, item doesnt exist\n");
        return 0;
    }
    return element->value;
}

int listSize(List* list)
{
    return list->size;
}
