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
} queue;

queue *newQueue(int capacity)
{
    queue *new = (queue *)malloc(sizeof(queue));
    new->capacity = capacity;
    new->entry_point = 0;
    new->exit_point = 0;
    new->arr = (int *)malloc(capacity * sizeof(int));

    return new;
}

int enQueue(queue *queue, int data)
{
    if (queue->entry_point <= queue->capacity - 1)
    {
        queue->arr[queue->entry_point] = data;
        queue->entry_point++;

        return 0;
    }

    else
    {
        printf("Stack is Full\n");
        return -1;
    }
}

void printQueue(queue *queue)
{
    if (queue->entry_point > queue->exit_point)
    {
        for (int i = queue->exit_point; i < queue->entry_point; i++)
        {
            printf("%d ", queue->arr[i]);
        }
        printf("\n");
    }

    else
    {
        printf("Queue is Empty\n");
    }
}

int deQueue(queue *queue)
{
    if (queue->entry_point > queue->exit_point)
    {
        int result = queue->arr[queue->exit_point];
        queue->exit_point++;
        return result;
    }

    else
    {
        printf("Queue is Empty\n");
        return -1;
    }
}

int peek(queue *queue, int index)
{
    if (index >= queue->exit_point && index < queue->entry_point)
    {
        printf("%d\n", queue->arr[index - 1]);
        return queue->arr[index - 1];
    }

    else
    {
        return -1;
    }
}

int main()
{
    queue *q = newQueue(5);
    enQueue(q, 2);
    enQueue(q, 4);
    enQueue(q, 6);
    enQueue(q, 68);
    enQueue(q, 60);

    deQueue(q);
    enQueue(q, 60);
    enQueue(q, 60);
    deQueue(q);
    printQueue(q);
    return 0;
}