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
    node *head;
    int size;
} circular_linked_list;

typedef struct h
{
    int capacity;
    node *entry_point, *exit_point;
    circular_linked_list *list;
} circular_queue;

node *newNode(int data)
{

    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    return new;
}

circular_linked_list *newCircularLinkedList()
{
    circular_linked_list *new = (circular_linked_list *)malloc(sizeof(circular_linked_list));
    new->head = NULL;
    new->size = 0;

    return new;
}

circular_queue *newCircularQueue(int capacity)
{
    circular_queue *new = (circular_queue *)malloc(sizeof(circular_queue));
    new->capacity = capacity + 1;
    new->list = newCircularLinkedList();
    new->list->head = newNode(0);
    new->entry_point = new->list->head;
    new->exit_point = new->list->head;

    return new;
}

int enQueue(circular_queue *queue, int data)
{
    if (queue->list->size < queue->capacity - 1)
    {
        if (queue->entry_point->next != queue->exit_point)
        {
            queue->entry_point->data = data;
            queue->entry_point->next = newNode(data);
            queue->entry_point = queue->entry_point->next;

            if (queue->list->size == queue->capacity - 2)
            {
                queue->entry_point->next = queue->list->head;
            }

            queue->list->size++;
            return 0;
        }

        else
        {
            printf("Circular Queue is Full\n");
            return -1;
        }
    }

    else
    {
        if (queue->entry_point->next != queue->exit_point)
        {
            queue->entry_point->data = data;
            queue->entry_point = queue->entry_point->next;

            return 0;
        }

        else
        {
            printf("Circular Queue is Full\n");
            return -1;
        }
    }
}

void printCircularQueue(circular_queue *queue)
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
        printf("Queue is Empty while Printing\n");
    }
}

int deQueue(circular_queue *queue)
{
    if (queue->entry_point != queue->exit_point)
    {
        int result = queue->exit_point->data;
        queue->exit_point = queue->exit_point->next;

        printf("Dequeued value - %d\n", result);
        return result;
    }

    else
    {
        printf("Queue is Empty while Dequeuing\n");
        return -1;
    }
}

int peek(circular_queue *queue, int index)
{
    if (queue->entry_point != queue->exit_point)
    {
        if (index <= 0)
        {
            printf("Invalid Index\n");
            return -1;
        }

        node *temp = queue->exit_point;
        int after_entry = 0;

        for (int i = 0; i < index - 1; i++)
        {
            if (temp == queue->entry_point)
            {
                after_entry = 1;
                break;
            }
            temp = temp->next;
        }

        if (after_entry == 1)
        {
            printf("Invalid Index\n");
            return -1;
        }

        printf("Peeked value - %d\n", temp->data);
        return temp->data;
    }

    else
    {
        printf("Queue is Empty while Peeking\n");
        return -1;
    }
}

int main()
{
    circular_queue *q = newCircularQueue(2);

    enQueue(q, 2);
    enQueue(q, 3);

    deQueue(q);
    enQueue(q, 4);
    
    deQueue(q);
    enQueue(q, 5);

    peek(q, 2);
    // printCircularQueue(q);

    return 0;
}