#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List* createList()
{
    List* list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

ListElement* createListElement(int value)
{
    ListElement* element = (ListElement*) malloc(sizeof(ListElement));
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
    ListElement* temporary = list->head;
    while (temporary->next != NULL) {
        temporary = temporary->next;
    }
    return temporary;
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
    ListElement* current = list->head;
    for (int i = 0; i < position - 1; ++i) {
        current = current->next;
    }
    element->next = current->next;
    current->next = element;
    list->size++;
    return true;
}

int locate(int elementValue, List* list)
{
    ListElement* current = list->head;
    int position = 0;
    while (current != NULL) {
        if (current->value == elementValue)
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
    ListElement* element = list->head;
    for (int i = 0; i != position && element != NULL; i++) {
        element = element->next;
    }
    return element;
}

bool delete(List* list, int position)
{
    if (position >= listSize(list) || position < 0)
        return false;
    ListElement* temporary = NULL;
    if (position == 0) {
        temporary = list->head;
        list->head = temporary->next;
        free(temporary);
        list->size--;
        return true;
    }
    ListElement* previous = retrieve(list, position - 1);
    temporary = previous->next;
    previous->next = temporary->next;
    free(temporary);
    list->size--;
    return true;
}

void printList(List* list)
{
    printf("START -> ");
    ListElement* tmp = list->head;
    while (tmp != NULL) {
        printf("%d -> ", tmp->value);
        tmp = tmp->next;
    }
    printf("END\n");
}

bool deleteList(List* list)
{
    ListElement* current = list->head;
    ListElement* temporary = NULL;
    while (current != NULL) {
        temporary = current;
        current = current->next;
        free(temporary);
    }
    free(list);
    return true;
}

int listSize(List* list)
{
    return list->size;
}
