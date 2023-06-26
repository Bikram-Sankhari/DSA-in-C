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
} circular_linked_list;

node *newNode(int data)
{

    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    return new;
}

circular_linked_list *newCircularLinkedList(int data)
{
    circular_linked_list *new = (circular_linked_list *)malloc(sizeof(circular_linked_list));
    new->start = newNode(data);
    new->start->next = new->start;

    return new;
}

void append(circular_linked_list *list, int data)
{
    node *temp = list->start;

    do
    {
        temp = temp->next;
    } while (temp->next != list->start);

    temp->next = newNode(data);
    temp->next->next = list->start;
}

void printList(circular_linked_list *list)
{
    node *temp = list->start;

    do
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    } while (temp != list->start);
}

void insert(circular_linked_list *list, int index, int data)
{
    node *temp = list->start;

    if (index == 0)
    {
        node *old_start = list->start;
        list->start = newNode(data);
        list->start->next = temp;

        do
        {
            temp = temp->next;
        } while (temp->next != old_start);

        temp->next = list->start;
    }

    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        node *last_address = temp->next;
        temp->next = newNode(data);
        temp->next->next = last_address;
    }
}

void delete(circular_linked_list *list, int index)
{
    node *temp = list->start;
    node *deleted_node;

    if (index == 0)
    {
        deleted_node = list->start;
        list->start = list->start->next;

        do
        {
            temp = temp->next;
        } while (temp->next != deleted_node);

        temp->next = list->start;
        free(deleted_node);
    }

    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        deleted_node = temp->next;
        temp->next = temp->next->next;

        free(deleted_node);
    }
}

void remove1(circular_linked_list *list){
    node *temp = list->start;

    do{
        temp = temp->next;
    }while(temp->next->next != list->start);

    free(temp->next);
    temp->next = list->start;
}

int main()
{
    circular_linked_list *list = newCircularLinkedList(5);
    append(list, 6);
    append(list, 9);
    insert(list, 1, 8);
    insert(list, 1, 18);
    insert(list, 0, 3);

    printf("Before deleteion\n");
    printList(list);

    // delete (list, 1);
    // delete (list, 0);
    remove1(list);
    printf("After deletion\n");
    printList(list);
    return 0;
}