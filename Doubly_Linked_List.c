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
    node *previous;
    int data;
    node *next;
};

typedef struct m
{
    node *start;
    int size;
} doubly_linked_list;

node *newNode(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->previous = NULL;
    new->data = data;
    new->next = NULL;

    return new;
}

doubly_linked_list *newDoublyLinkedList(int data)
{
    doubly_linked_list *list = (doubly_linked_list *)malloc(sizeof(doubly_linked_list));

    list->start = newNode(data);
    list->size = 1;

    return list;
}

void printList(doubly_linked_list *list)
{

    if (list->size == 1)
    {
        printf("%d\n", list->start->data);
    }

    else
    {
        node *temp = list->start;
        for (int i = 0; i < list->size; i++)
        {
            printf("%d\n", temp->data);
            temp = temp->next;
        }
    }
}

void append(doubly_linked_list *list, int data)
{
    node *temp = list->start;
    for (int i = 0; i < (list->size - 1); i++)
    {
        temp = temp->next;
    }

    temp->next = newNode(data);
    temp->next->previous = temp;
    temp->next->next = NULL;

    list->size = list->size + 1;
}

void insert(doubly_linked_list *list, int index, int data)
{
    if (index >= list->size)
    {
        printf("Index Out of Bound Exception\n");
    }

    else if (index == 0)
    {
        node *temp = list->start;
        list->start = newNode(data);
        list->start->next = temp;
        list->start->previous = NULL;

        list->size = list->size + 1;
    }

    else
    {
        node *temp = list->start;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        node *old_address = temp->next;

        temp->next = newNode(data);
        temp->next->previous = temp;
        temp->next->next = old_address;

        list->size = list->size + 1;
    }
}

void delete1(doubly_linked_list *list, int index)
{
    if (index >= list->size)
    {
        printf("Index Out of Bound Exception\n");
    }

    else if (index == 0)
    {
        node *temp = list->start;
        list->start = list->start->next;
        if (list->size != 1)
        {
            list->start->previous = NULL;
        }
        free(temp);
        list->size = list->size - 1;
    }

    else
    {
        node *temp = list->start;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        node *deleted_node = temp->next;

        temp->next = temp->next->next;
        temp->next->previous = temp;

        list->size = list->size - 1;
        free(deleted_node);
    }
}

void remove1(doubly_linked_list *list)
{
    if( list->size == 0){
        printf("No more items left\n");
    }

    else if (list->size == 1)
    {
        delete1(list, 0);
    }

    else
    {
        node *temp = list->start;
        for (int i = 0; i < (list->size - 1); i++)
        {
            temp = temp->next;
        }

        node *deleted_node = temp->next;
        temp->next = NULL;

        list->size = list->size - 1;
        free(deleted_node);
    }
}

int main()
{
    doubly_linked_list *list = newDoublyLinkedList(5);
    append(list, 6);
    append(list, 7);
    append(list, 8);
    insert(list, 0, 81);
    insert(list, 0, 89);
    insert(list, 1, 989);

    printList(list);

    remove1(list);
    remove1(list);
    printf("After delete\n");
    printList(list);
    return 0;
}