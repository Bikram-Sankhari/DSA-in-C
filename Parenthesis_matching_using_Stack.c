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
        return -1;
    }
}

void peek(stack *stack, int index)
{
    if (stack->stack_pointer >= 0 && index <= stack->stack_pointer)
    {
        printf("%d\n", stack->array[index]);
    }

    else
    {
        printf("Invalid Index\n");
    }
}

int main()
{
    char expression[] = "7-((((8(3*9)+11+12))-8)";

    stack *s = newStack(sizeof(expression));
    int underflow;
    int right_par[sizeof(expression)], right_par_count = 0;

    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '(')
        {
            push(s, i);
        }

        else if (expression[i] == ')')
        {
            underflow = pop(s);

            if (underflow == -1)
            {
                right_par[right_par_count] = i;
                right_par_count++;
            }
        }
    }

    if (underflow == -1)
    {
        printf("Parenthesis Unbalanced Expression for parenthesises at ");
        for (int i = 0; i < right_par_count; i++)
        {
            printf("%d ", right_par[i]);
        }
        printf("\n");
    }

    else if (s->stack_pointer == -1)
    {
        printf("Parenthesis Balanced Expression\n");
    }

    else
    {
        printf("Parenthesis Unbalanced Expression for parenthesises at ");
        printStack(s);
    }
    return 0;
}