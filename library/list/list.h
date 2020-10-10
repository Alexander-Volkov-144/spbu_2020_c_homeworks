#include <stdbool.h>

#ifndef SPBU_2020_C_HOMEWORKS_LIST_H
#define SPBU_2020_C_HOMEWORKS_LIST_H

typedef struct ListElement{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct List{
    ListElement* head;
    int size;
} List;

List* createList();

ListElement* createListElement(int value);

ListElement* tail(List* list);

ListElement* head(List* list);

bool insert(ListElement* element, int position, List* list);

int locate(int elementValue, List* list);

ListElement* retrieve(List* list, int position);

bool delete (List* list, int position);

void printList(List* list);

bool deleteList(List* list);

int listSize(List* list);

#endif //SPBU_2020_C_HOMEWORKS_LIST_H
