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
    new->capacity = capacity + 1;
    new->entry_point = 0;
    new->exit_point = 0;
    new->arr = (int *)malloc(new->capacity * sizeof(int));

    return new;
}

int enQueueFromEntry(queue *queue, int data)
{
    if ((queue->entry_point + 1) % queue->capacity != queue->exit_point)
    {
        queue->arr[queue->entry_point] = data;
        queue->entry_point = (queue->entry_point + 1) % queue->capacity;

        return 0;
    }

    else
    {
        printf("Stack is Full\n");
        return -1;
    }
}

int enQueueFromExit(queue *queue, int data)
{
    if ((queue->exit_point - 1) != queue->entry_point && (queue->exit_point + queue->capacity - 1) != queue->entry_point)
    {
        queue->exit_point--;
        if (queue->exit_point < 0)
        {
            queue->exit_point = queue->exit_point + queue->capacity;
        }
        queue->arr[queue->exit_point] = data;

        return 0;
    }

    else
    {
        printf("No Space to Enqueue from Exit\n");
        return -1;
    }
}

void printQueue(queue *queue)
{
    if (queue->entry_point != queue->exit_point)
    {
        for (int i = queue->exit_point; i != queue->entry_point; i = (i + 1) % queue->capacity)
        {
            printf("%d ", queue->arr[i]);
        }
        printf("\n");
    }

    else
    {
        printf("Queue is Empty while Printing\n");
    }
}

int deQueueFromEntry(queue *queue)
{
    if (queue->entry_point != queue->exit_point)
    {
        queue->entry_point--;
        if (queue->entry_point < 0)
        {
            queue->entry_point = queue->entry_point + queue->capacity;
        }
        int result = queue->arr[queue->entry_point];
        return result;
    }

    else
    {
        printf("Queue is Empty\n");
        return -1;
    }
}

int deQueueFromExit(queue *queue)
{
    if (queue->entry_point != queue->exit_point)
    {
        int result = queue->arr[queue->exit_point];
        queue->exit_point = (queue->exit_point + 1) % queue->capacity;
        return result;
    }

    else
    {
        printf("Queue is Empty\n");
        return -1;
    }
}

int main()
{
    queue *q = newQueue(2);
    enQueueFromEntry(q, 1);
    enQueueFromEntry(q, 2);
    deQueueFromExit(q);
    deQueueFromEntry(q);
    enQueueFromExit(q, 3);
    printQueue(q);
    return 0;
}