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

node *newNode(int data)
{
    node *start;
    start = (node *)malloc(sizeof(node));
    start->data = data;
    start->next = NULL;

    return start;
}

linkedList newLinkedList(int data)
{
    linkedList new;
    new.start = newNode(data);
    new.size = 1;
    return new;
}

int append(linkedList *list, int data)
{
    node *temp;
    temp = list->start;

    while (1)
    {
        if (temp->next == NULL)
        {
            temp->next = newNode(data);
            list->size = list->size + 1;
            return 0;
        }
        temp = temp->next;
    }

    return -1;
}

void printList(linkedList list, int index)
{
    node *temp;
    temp = list.start;

    if (index >= list.size)
    {
        printf("Index Out of Bound Exception");
    }

    else
    {
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        printf("%d\n", temp->data);
    }
}

int insert(linkedList *list, int index, int element)
{
    if (index >= list->size)
    {
        printf("Index is greater than the present size of the Linked List");
    }

    else if (index == 0)
    {
        node *temp = list->start;

        list->start = newNode(element);
        list->start->next = temp;
    }

    else
    {
        node *temp = list->start;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        node *last_address = temp->next;

        temp->next = newNode(element);
        temp = temp->next;
        temp->next = last_address;
        list->size = list->size + 1;
    }
}

int delete(linkedList *list, int index)
{
    if (index >= list->size)
    {
        printf("Index is greater than the present size of the Linked List");
    }

    else if(index == 0){
        node *last_address = list->start;

        list->start = list->start->next;
        free(last_address);
        list->size = list->size - 1;
    }

    else
    {
        node *temp = list->start;

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        node *last_address = temp->next;
        
        temp->next = temp->next->next;

        free(last_address);
        list->size = list->size - 1;
    }
}

int main()
{
    linkedList l1 = newLinkedList(9);

    append(&l1, 5);
    append(&l1, 8);
    append(&l1, 10);
    append(&l1, 21);

    insert(&l1, 0, 38);
    insert(&l1, 0, 23);

    // printf("Before Deletion\n");
    // for (int i = 0; i < l1.size; i++)
    // {
    //     printList(l1, i);
    // }

    // delete (&l1, 0);

    // printf("After Deletion\n");
    // for (int i = 0; i < l1.size; i++)
    // {
    //     printList(l1, i);
    // }

    printf("%d\n", l1.start);
    printf("%d\n", *(l1.start));
    printf("%d\n", l1.start->data);
    return 0;
}