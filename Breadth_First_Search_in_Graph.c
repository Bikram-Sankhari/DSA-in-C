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

int has_something(queue *q)
{
    if (q->entry_point > q->exit_point)
    {
        return 1;
    }

    return 0;
}

int main()
{
    queue *to_explore = newQueue(8);
    int node = 2;
    int visited[8] = {0};

    int graph[8][8] = {
      // 0  1  2  3  4  5  6  7
        {0, 1, 1, 1, 0, 0, 0, 0}, // 0
        {1, 0, 0, 0, 0, 0, 0, 0}, // 1
        {1, 0, 0, 1, 0, 0, 0, 0}, // 2
        {1, 0, 2, 0, 1, 1, 0, 0}, // 3
        {0, 0, 0, 1, 0, 0, 0, 0}, // 4
        {0, 0, 0, 1, 0, 0, 1, 1}, // 5
        {0, 0, 0, 0, 0, 1, 0, 0}, // 6
        {0, 0, 0, 0, 0, 1, 0, 0}  // 7
    };

    printf("%d ", node);
    enQueue(to_explore, node);
    visited[node] = 1;

    while (has_something(to_explore))
    {
        node = deQueue(to_explore);
        for (int m = 0; m < 8; m++)
        {
            if (graph[node][m] == 1 && visited[m] == 0)
            {
                printf("%d ", m);
                visited[m] = 1;
                enQueue(to_explore, m);
            }
        }
    }
    return 0;
}