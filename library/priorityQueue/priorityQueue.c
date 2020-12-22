#include "priorityQueue.h"
#include <stdlib.h>

struct PriorityQueueElement {
    int priority;
    int value;
    struct PriorityQueueElement* next;
};

struct PriorityQueue {
    PriorityQueueElement* head;
    int size;
};

PriorityQueue* createQueue()
{
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->head = NULL;
    queue->size = 0;
    return queue;
}

PriorityQueueElement* createQueueElement(int priority, int value)
{
    PriorityQueueElement* element = (PriorityQueueElement*)malloc(sizeof(PriorityQueueElement));
    element->priority = priority;
    element->value = value;
    element->next = NULL;
    return element;
}

int queueSize(PriorityQueue* queue)
{
    return queue->size;
}

void removeElement(PriorityQueueElement* element)
{
    free(element);
}

int dequeue(PriorityQueue* queue)
{
    if (queueSize(queue) == 0) {
        return -1;
    }
    PriorityQueueElement* newHead = queue->head->next;
    queue->size -= 1;
    int value = queue->head->value;
    removeElement(queue->head);
    queue->head = newHead;
    return value;
}

void addElement(PriorityQueue* queue, PriorityQueueElement* element)
{
    if (queue->size == 0) {
        queue->head = element;
    } else {
        if (queue->head->priority < element->priority) {
            element->next = queue->head;
            queue->head = element;
        } else {
            PriorityQueueElement* currentElement = queue->head;
            while (currentElement->next != NULL && currentElement->next->priority >= element->priority) {
                currentElement = currentElement->next;
            }
            if (currentElement->next == NULL) {
                currentElement->next = element;
            } else {
                element->next = currentElement->next;
                currentElement->next = element;
            }
        }
    }
    queue->size += 1;
}

void enqueue(PriorityQueue* queue, int priority, int value)
{
    PriorityQueueElement* newElement = createQueueElement(priority, value);
    addElement(queue, newElement);
}

void removeQueue(PriorityQueue* queue)
{

    PriorityQueueElement* currentElement = queue->head;
    PriorityQueueElement* toDelete = NULL;
    while (currentElement != NULL) {
        toDelete = currentElement;
        currentElement = currentElement->next;
        free(toDelete);
    }
    free(queue);
}
