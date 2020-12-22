#include "../library/priorityQueue/priorityQueue.h"
#include <stdio.h>

int main()
{
    PriorityQueue* queue = createQueue();
    enqueue(queue, 2, 4);
    enqueue(queue, 5, 1);
    enqueue(queue, 3, 3);
    enqueue(queue, 1, 5);
    enqueue(queue, 4, 2);
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    removeQueue(queue);
    return 0;
}
