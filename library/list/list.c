#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
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
    ListElement* temporary = list->head;
    while (temporary->next != NULL) {
        temporary = temporary->next;
    }
    return temporary;
}

ListElement* head(List* list)
{
    return list->head;
}

bool insert(ListElement* element, int position, List* list)
{
    if (position == 1) {
        element->next = list->head;
        list->head = element;
        return true;
    }
    ListElement* current = list->head;
    for (int i = 1; i < position - 1; ++i) {
        if (current->next == NULL)
            return false;
        current = current->next;
    }
    element->next = current->next;
    current->next = element;
    return true;
}

int locate(ListElement* element, List* list)
{
    ListElement* current = list->head;
    int position = 1;
    while (current != NULL) {
        if (current->value == element->value)
            return position;
        current = current->next;
        ++position;
    }
    return -1; // в списке нет элемента с таким значением
}

ListElement* retrieve(List* list, int position)
{
    ListElement* element = list->head;
    for (int i = 0; i != position - 1 && element != NULL; i++) {
        element = element->next;
    }
    return element;
}

bool delete(List* list, int position)
{
    ListElement* temporary = NULL;
    if (position == 1) {
        temporary = list->head;
        list->head = temporary->next;
        free(temporary);
        return true;
    }
    ListElement* previous = retrieve(list, position - 1);
    temporary = previous->next;
    previous->next = temporary->next;
    free(temporary);
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