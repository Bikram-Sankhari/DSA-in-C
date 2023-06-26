#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct m
{
    int capacity;
    int entry_point, exit_point;
    int *arr;
} circularQueue;

circularQueue *newcircularQueue(int capacity)
{
    circularQueue *new = (circularQueue *)malloc(sizeof(circularQueue));
    new->capacity = capacity + 1;
    new->entry_point = 0;
    new->exit_point = 0;
    new->arr = (int *)malloc(capacity * sizeof(int));

    return new;
}

int enQueue(circularQueue *circularQueue, int data)
{
    if ((circularQueue->entry_point + 1) % circularQueue->capacity != circularQueue->exit_point)
    {
        circularQueue->arr[circularQueue->entry_point] = data;
        circularQueue->entry_point = (circularQueue->entry_point + 1) % circularQueue->capacity;

        return 0;
    }

    else
    {
        printf("circularQueue is Full\n");
        return -1;
    }
}

void printCircularQueue(circularQueue *circularQueue)
{
    if (circularQueue->entry_point != circularQueue->exit_point)
    {
        for (int i = circularQueue->exit_point; i != circularQueue->entry_point; i = (i + 1) % circularQueue->capacity)
        {
            printf("%d ", circularQueue->arr[i]);
        }
        printf("\n");
    }

    else
    {
        printf("CircularQueue is Empty\n");
    }
}

int deQueue(circularQueue *circularQueue)
{
    if (circularQueue->entry_point != circularQueue->exit_point)
    {
        int result = circularQueue->arr[circularQueue->exit_point];
        circularQueue->exit_point = (circularQueue->exit_point + 1) % circularQueue->capacity;
        return result;
    }

    else
    {
        printf("circularQueue is Empty\n");
        return -1;
    }
}

int peek(circularQueue *circularQueue, int index)
{
    if (index >= 0 && index < circularQueue->capacity)
    {
        printf("%d\n", circularQueue->arr[index - 1]);
        return circularQueue->arr[index - 1];
    }

    else
    {
        return -1;
    }
}

int main()
{
    circularQueue *q = newcircularQueue(5);

    enQueue(q, 0);
    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);
    enQueue(q, 4);
    deQueue(q);
    enQueue(q, 5);

    printCircularQueue(q);
    return 0;
}