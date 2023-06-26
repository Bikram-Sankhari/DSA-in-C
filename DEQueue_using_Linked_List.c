#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct n node;
struct n
{
    int data;
    node *next;
    node *previous;
};

typedef struct m
{
    node *start;
    int size;
} linkedList;

typedef struct p
{
    int capacity;
    node *entry_point, *exit_point;
    linkedList *list;
} queue;

node *newNode(int data)
{
    node *start;
    start = (node *)malloc(sizeof(node));
    start->data = data;
    start->next = NULL;
    start->previous = NULL;

    return start;
}

linkedList *newLinkedList()
{
    linkedList *new = (linkedList *)malloc(sizeof(linkedList));
    new->start = newNode(0);
    new->size = 0;
    return new;
}

void printQueue(queue *queue)
{
    if (queue->list->size > 0)
    {
        for (node *temp = queue->exit_point; temp != queue->entry_point; temp = temp->next)
        {
            printf("%d ", temp->data);
        }
        printf("\n");
    }

    else
    {
        printf("Queue is Empty\n");
    }
}

queue *newQueue(int capacity)
{
    queue *new = (queue *)malloc(sizeof(queue));
    new->capacity = capacity;
    new->list = newLinkedList();
    new->entry_point = new->list->start;
    new->exit_point = new->list->start;

    return new;
}

int enQueueFromEntry(queue *queue, int data)
{
    if (queue->list->size < queue->capacity)
    {
        queue->entry_point->next = newNode(0);
        queue->entry_point->next->previous = queue->entry_point;
        queue->entry_point->data = data;
        queue->list->size++;
        queue->entry_point = queue->entry_point->next;

        return 0;
    }

    else
    {
        printf("Queue is Full\n");
        return -1;
    }
}

int enQueueFromExit(queue *queue, int data)
{
    if (queue->exit_point != queue->list->start)
    {
        queue->exit_point = queue->exit_point->previous;
        queue->exit_point->data = data;
        queue->list->size++;

        return 0;
    }

    else
    {
        printf("No Space at Exit\n");
        return -1;
    }
}

int deQueueFromExit(queue *queue)
{
    if (queue->list->size > 0)
    {
        int result = queue->exit_point->data;
        queue->exit_point = queue->exit_point->next;
        queue->list->size--;

        return result;
    }

    else
    {
        printf("Queue is Empty while DeQueing\n");
        return -1;
    }
}

int deQueueFromEntry(queue *queue)
{
    if (queue->list->size > 0)
    {
        queue->entry_point = queue->entry_point->previous;
        queue->list->size--;

        return queue->entry_point->data;
    }

    else
    {
        printf("Queue is Empty while DeQueing\n");
        return -1;
    }
}

int main()
{
    queue *q = newQueue(3);
    enQueueFromEntry(q, 1);
    enQueueFromEntry(q, 2);
    deQueueFromExit(q);
    deQueueFromEntry(q);
    enQueueFromExit(q, 3);

    printQueue(q);

    return 0;
}