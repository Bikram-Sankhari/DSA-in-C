#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct m
{
    char operator;
    int presedence;
} node;

typedef struct n
{
    int capacity;
    int stack_pointer;
    node *array;
} stack;

stack *newStack(int capacity)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->array = (node *)malloc(capacity * sizeof(node));
    st->capacity = capacity;
    st->stack_pointer = -1;
    return st;
}

int push(stack *stack, char operator)
{
    if (stack->stack_pointer < (stack->capacity - 1))
    {
        stack->stack_pointer = stack->stack_pointer + 1;
        stack->array[stack->stack_pointer].operator= operator;
        if (operator== '+' || operator== '-')
        {
            stack->array[stack->stack_pointer].presedence = 1;
        }

        else if (operator== '*' || operator== '/')
        {
            stack->array[stack->stack_pointer].presedence = 2;
        }

        return 0;
    }

    else
    {
        printf("Stack Overflow\n");
        return -1;
    }
}

node pop(stack *stack)
{
    node result;
    if (stack->stack_pointer >= 0)
    {
        result.operator= stack->array[stack->stack_pointer].operator;
        result.presedence = stack->array[stack->stack_pointer].presedence;
        stack->stack_pointer = stack->stack_pointer - 1;

        return result;
    }

    else
    {
        printf("Empty Stack\n");
        return result;
    }
}

int isEmpty(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        return 0;
    }

    return 1;
}

node peekTop(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        return stack->array[stack->stack_pointer];
    }

    else
    {
        printf("Invalid Index\n");
    }
}

void printStack(stack *stack)
{
    if (stack->stack_pointer >= 0)
    {
        for (int i = 0; i <= stack->stack_pointer; i++)
        {
            printf("%c ", stack->array[i].operator);
        }
        printf("\n");
    }

    else
    {
        printf("Empty Stack\n");
    }
}

typedef struct k
{
    char *character_pointer;
    int letter_count;
} last_expression;

int stacks_count = 0;
int postfix_expression_count = 0;
stack **stacks;
last_expression *postfix_expression;

//--------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

char *infix_to_postfix(char *expression)
{
    if (postfix_expression_count != 0)
    {
        stacks = realloc(stacks, (stacks_count + 1) * sizeof(stack));
        postfix_expression = realloc(postfix_expression, (postfix_expression_count + 1) * sizeof(last_expression));
    }

    else
    {
        stacks = (stack **)malloc((stacks_count + 1) * sizeof(stack));
        postfix_expression = (last_expression *)malloc((postfix_expression_count + 1) * sizeof(last_expression));
    }

    *(stacks + stacks_count) = newStack(100);

    (postfix_expression + postfix_expression_count)->letter_count = 0;

    (postfix_expression + postfix_expression_count)->character_pointer = (char *)malloc(100 * sizeof(char));

    int current_presedence;

    // Start Traversal from the specified pointer
    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-')
        {

            if (expression[i] == '*' || expression[i] == '/')
            {
                current_presedence = 2;
            }

            else
            {
                current_presedence = 1;
            }

            while (1)
            {
                if (isEmpty(*(stacks + stacks_count)))
                {
                    push(*(stacks + stacks_count), expression[i]);
                    break;
                }

                else if (peekTop(*(stacks + stacks_count)).presedence < current_presedence)
                {
                    push(*(stacks + stacks_count), expression[i]);
                    break;
                }

                else
                {
                    (postfix_expression + postfix_expression_count)->character_pointer[(postfix_expression + postfix_expression_count)->letter_count] = pop(*(stacks + stacks_count)).operator;
                    (postfix_expression + postfix_expression_count)->letter_count = (postfix_expression + postfix_expression_count)->letter_count + 1;
                    
                }
            }
        }

        else if (expression[i] == '(')
        {
            stacks_count++;
            postfix_expression_count++;

            int j = i;
            stack *tempStack = newStack(100);
            push(tempStack, expression[i]);
            i++;

            while (!isEmpty(tempStack))
            {
                if (expression[i] == '(')
                {
                    push(tempStack, expression[i]);
                }

                else if (expression[i] == ')')
                {
                    pop(tempStack);
                }

                i++;
            }
            free(tempStack);
            i--;

            infix_to_postfix(expression + j + 1);
        }

        else if (expression[i] == ')')
        {
            break;
        }

        else

        {
            (postfix_expression + postfix_expression_count)->character_pointer[(postfix_expression + postfix_expression_count)->letter_count] = expression[i];
            (postfix_expression + postfix_expression_count)->letter_count = (postfix_expression + postfix_expression_count)->letter_count + 1;
        }
    }

    while (!isEmpty(*(stacks + stacks_count)))
    {
        (postfix_expression + postfix_expression_count)->character_pointer[(postfix_expression + postfix_expression_count)->letter_count] = pop(*(stacks + stacks_count)).operator;
        (postfix_expression + postfix_expression_count)->letter_count = (postfix_expression + postfix_expression_count)->letter_count + 1;
    }

    (postfix_expression + postfix_expression_count)->character_pointer[(postfix_expression + postfix_expression_count)->letter_count] = '\0';
    (postfix_expression + postfix_expression_count)->letter_count = (postfix_expression + postfix_expression_count)->letter_count + 1;

    if (postfix_expression_count != 0)
    {
        for (int i = 0; i < (postfix_expression + postfix_expression_count)->letter_count - 1; i++)
        {

            (postfix_expression + postfix_expression_count - 1)->character_pointer[(postfix_expression + postfix_expression_count - 1)->letter_count] = (postfix_expression + postfix_expression_count)->character_pointer[i];
            (postfix_expression + postfix_expression_count - 1)->letter_count = (postfix_expression + postfix_expression_count - 1)->letter_count + 1;

        }
        postfix_expression_count--;
    }

    free(*(stacks + stacks_count));
    stacks_count--;
    return postfix_expression->character_pointer;
}

int main()
{
    char *expression = "(7 * ( (3 - 2 * 7 / 8) + (10 / 5) ) - 9)";
    char *result = infix_to_postfix(expression);

    puts(result);

    return 0;
}