#include "stackd.h"
#include <stdlib.h>

struct StackElement {
    double storeElement;
    struct StackElement* next;
};

struct Stack {
    struct StackElement* top;
    int stackSize;
};

StackElement* createStackElement(double storeElement)
{
    StackElement* element = (StackElement*)malloc(sizeof(StackElement));
    element->storeElement = storeElement;
    element->next = NULL;
    return element;
}

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->stackSize = 0;
    return stack;
}

void push(Stack* stack, StackElement* newElement)
{
    newElement->next = stack->top;
    stack->top = newElement;
    ++stack->stackSize;
}

bool isEmpty(Stack* stack)
{
    return stack->stackSize == 0;
}

StackElement* pop(Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    StackElement* temp = stack->top;
    stack->top = temp->next;
    temp->next = NULL;
    --stack->stackSize;
    return temp;
}

void deleteStackElement(StackElement* stackElement)
{
    free(stackElement);
}

void removeStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        deleteStackElement(pop(stack));
    }
    free(stack);
}

int getSize(Stack* stack)
{
    return stack->stackSize;
}

double getStoreElement(StackElement* element)
{
    return element->storeElement;
}