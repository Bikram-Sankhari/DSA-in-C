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
    node *left;
    node *right;
};

node *new_binary_tree(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

int insert(node *root, int data)
{
    if (root->data == data)
    {
        printf("Duplicate Data\n");
        return -1;
    }

    else if (root->data < data)
    {
        if (root->right == NULL)
        {
            root->right = new_binary_tree(data);
            return 1;
        }

        else
        {
            insert(root->right, data);
        }
    }

    else
    {
        if (root->left == NULL)
        {
            root->left = new_binary_tree(data);
            return 1;
        }

        else
        {
            insert(root->left, data);
        }
    }
}

void in_order_traverse(node *root)
{
    if (root != NULL)
    {
        in_order_traverse(root->left);
        printf("%d ", root->data);
        in_order_traverse(root->right);
    }
}

int main()
{
    /*
                   50
            _______|________
           |                |
           25              90
       ____|____        ____|____
      |        |       |       130
      20       30           ____|_____
                           |          |
                          100        150
   */
    node *root = new_binary_tree(50);

    node *n1 = new_binary_tree(25);
    node *n2 = new_binary_tree(20);
    node *n3 = new_binary_tree(30);
    node *n4 = new_binary_tree(90);
    node *n5 = new_binary_tree(130);
    node *n6 = new_binary_tree(100);
    node *n7 = new_binary_tree(150);

    root->left = n1;
    root->right = n4;

    n1->left = n2;
    n1->right = n3;

    n4->right = n5;

    n5->left = n6;
    n5->right = n7;

    insert(root, 45);

    in_order_traverse(root);
    printf("\n");
    return 0;
}