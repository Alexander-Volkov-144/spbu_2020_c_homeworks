#include <stdbool.h>

#ifndef SPBU_2020_C_HOMEWORKS_LIST_H
#define SPBU_2020_C_HOMEWORKS_LIST_H

typedef struct ListElement ListElement;

typedef struct List List;

List* createList();

ListElement* createListElement(int value);

ListElement* tail(List* list);

ListElement* head(List* list);

bool insert(ListElement* element, int position, List* list);

int locateByValue(int elementValue, List* list);

int locate(ListElement* value, List* list);

ListElement* retrieve(List* list, int position);

bool delete (List* list, int position);

void printList(List* list);

bool deleteList(List* list);

int listSize(List* list);

int returnElementValue(ListElement* element);

#endif //SPBU_2020_C_HOMEWORKS_LIST_H
