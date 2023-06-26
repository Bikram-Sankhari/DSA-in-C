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
    char *array;
} stack;

stack *newStack(int capacity)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->array = (char *)malloc(capacity * sizeof(char));
    st->capacity = capacity;
    st->stack_pointer = -1;
    return st;
}

int push(stack *stack, char data)
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

char pop(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        char result;
        result = stack->array[stack->stack_pointer];
        stack->stack_pointer = stack->stack_pointer - 1;
        return result;
    }

    else
    {
        return -1;
    }
}

int isBalanced = 1;

void notBalanced()
{
    printf("Expression not Balaned\n");
    isBalanced = 0;
}

int main()
{
    char expression[] = "(7 - {9 + (2 * [4 + 3]) - [8 + 2 / 23]})";

    stack *s = newStack(sizeof(expression));

    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        {
            push(s, expression[i]);
        }

        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
        {
            char popped_ch = pop(s);
            if (!((popped_ch == '(' && expression[i] == ')') || (popped_ch == '{' && expression[i] == '}') || (popped_ch == '[' && expression[i] == ']')))
            {
                notBalanced();
                break;
            }
        }
    }

    if (isBalanced == 1 && s->stack_pointer == -1)
    {
        printf("Expression is Balanced\n");
    }

    else{
        notBalanced();
    }
}