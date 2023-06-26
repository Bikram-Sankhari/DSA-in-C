#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int m = 5;

typedef struct n node;
struct n
{
    int data;
    node *next;
};

typedef struct m
{
    node *head;
} linkedList;

typedef struct j
{
    int capacity;
    int stack_pointer;
    linkedList *list;
} stack;

node *newNode(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    return new;
}

linkedList *newLinkedList()
{
    linkedList *new = (linkedList *)malloc(sizeof(linkedList));
    new->head = NULL;

    return new;
}

stack *newStack(int capacity)
{
    stack *new = (stack *)malloc(sizeof(stack));
    new->capacity = capacity;
    new->stack_pointer = -1;
    new->list = newLinkedList();

    return new;
}

int push(stack *stack, int data)
{
    if (stack->stack_pointer < stack->capacity - 1)
    {
        node *temp = stack->list->head;

        stack->list->head = newNode(data);
        stack->list->head->next = temp;

        stack->stack_pointer++;
        m++;
        return 0;
    }

    else
    {
        printf("Stack is Full\n");
        return -1;
    }
}

int pop(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        int data = stack->list->head->data;
        node *deleted_node = stack->list->head;
        stack->list->head = stack->list->head->next;

        stack->stack_pointer--;
        free(deleted_node);

        return data;
    }

    else
    {
        printf("Stack is Empty\n");
        return -1;
    }
}

int peek(stack *stack, int index)
{
    if (index - 1 <= stack->stack_pointer && index > 0)
    {
        node *temp = stack->list->head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        printf("%d\n", temp->data);
        return temp->data;
    }

    else
    {
        printf("Invalid Index\n");
        return -1;
    }
}

void printStack(stack *stack)
{
    node *temp = stack->list->head;
    for (int i = stack->stack_pointer; i >= 0; i--)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    stack *s = newStack(10);

    push(s, 6);
    push(s, 8);
    push(s, 18);
    push(s, 23);
    push(s, 78);
    push(s, 19);
    push(s, 7);

    pop(s);
    peek(s, 6);
    printStack(s);
    printf("m is %d\n", m);
    return 0;
}