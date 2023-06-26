#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct n
{
    int capacity;
    int stack_pointer;
    int *array;
} stack;

stack *newStack(int capacity)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->array = (int *)malloc(capacity * sizeof(int));
    st->capacity = capacity;
    st->stack_pointer = -1;
    return st;
}

int push(stack *stack, int data)
{
    if (stack->stack_pointer < (stack->capacity - 1))
    {
        stack->stack_pointer = stack->stack_pointer + 1;
        stack->array[stack->stack_pointer] = data;
        return 0;
    }

    else
    {
        printf("Stack Overflow\n");
        return -1;
    }
}

void printStack(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        for (int i = 0; i <= stack->stack_pointer; i++)
        {
            printf("%d ", stack->array[i]);
        }
        printf("\n");
    }

    else
    {
        printf("Empty Stack\n");
    }
}

int pop(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        int result;
        result = stack->array[stack->stack_pointer];
        stack->stack_pointer = stack->stack_pointer - 1;
        return result;
    }

    else
    {
        printf("Empty Stack\n");
        return NULL;
    }
}

void peek(stack *stack, int index)
{
    if (stack->stack_pointer >= 0 && index <= stack->stack_pointer)
    {
        printf("%d\n", stack->array[index]);
    }

    else{
        printf("Invalid Index\n");
    }
}

int main()
{
    stack *s = newStack(5);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);

    pop(s);

    peek(s, 2);
    printStack(s);

    return 0;
}