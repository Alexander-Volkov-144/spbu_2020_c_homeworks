#include <stdbool.h>

#ifndef SPBU_2020_C_HOMEWORKS_STACK_H
#define SPBU_2020_C_HOMEWORKS_STACK_H

typedef struct StackElement {
    double storeElement;
    struct StackElement* next;
}StackElement;

typedef struct Stack Stack;


StackElement* createStackElement(double storeElement);

Stack* createStack();

void push(Stack* stack, StackElement* newElement);

StackElement* pop(Stack* stack);

bool isEmpty(Stack* stack);

void deleteStackElement(StackElement* stackElement);

void removeStack(Stack* stack);

int getSize(Stack* stack);

#endif //SPBU_2020_C_HOMEWORKS_STACK_H
