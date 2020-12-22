#ifndef SPBU_2020_C_HOMEWORKS_PRIORITYQUEUE_H
#define SPBU_2020_C_HOMEWORKS_PRIORITYQUEUE_H

typedef struct PriorityQueueElement PriorityQueueElement;

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* createQueue();

void removeQueue(PriorityQueue* queue);

int dequeue(PriorityQueue* queue);

void enqueue(PriorityQueue* queue, int priority, int value);


#endif //SPBU_2020_C_HOMEWORKS_PRIORITYQUEUE_H
