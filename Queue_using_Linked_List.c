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
    if (queue->entry_point != queue->exit_point)
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

int enQueue(queue *queue, int data)
{
    if (queue->list->size < queue->capacity)
    {
        queue->entry_point->next = newNode(0);
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

int deQueue(queue *queue)
{
    if (queue->entry_point != queue->exit_point)
    {
        int result = queue->exit_point->data;
        queue->exit_point = queue->exit_point->next;

        return result;
    }

    else
    {
        printf("Queue is Empty while DeQueing\n");
        return -1;
    }
}

int peek(queue *queue, int index)
{
    node *target = queue->list->start;
    int after_exit = 0, after_entry = 0;

    if (queue->exit_point != queue->entry_point)
    {
        for (int i = 0; i < index - 1; i++)
        {
            if (target == queue->exit_point)
            {
                after_exit = 1;
            }

            if (target == queue->entry_point)
            {
                after_entry = 1;
                break;
            }
            target = target->next;
        }

        if (target == queue->exit_point)
        {
            after_exit = 1;
        }

        if (target == queue->entry_point)
        {
            after_entry = 1;
        }

        if (after_exit == 1 && after_entry != 1)
        {
            printf("%d\n", target->data);
            return target->data;
        }

        else
        {
            printf("Invalid Index\n");
            return -1;
        }
    }

    else
    {
        printf("Queue is Empty while Peeking\n");
        return -1;
    }
}

int main()
{
    queue *q = newQueue(4);

    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);
    enQueue(q, 4);
    deQueue(q);
    // printQueue(q);
    deQueue(q);

    peek(q, 8);

    // deQueue(q);
    // deQueue(q);

    return 0;
}