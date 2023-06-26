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

node *pre(node *root, int *depth)
{
    root = root->left;
    *depth = 0;

    while (root->right != NULL)
    {
        root = root->right;
        *depth = *depth + 1;
    }

    return root;
}

node *post(node *root, int *depth)
{
    root = root->right;
    *depth = 0;

    while (root->left != NULL)
    {
        root = root->left;
        *depth = *depth + 1;
    }

    return root;
}

node *delete(node *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data > data)
    {
        root->left = delete (root->left, data);
    }

    else if (root->data < data)
    {
        root->right = delete (root->right, data);
    }

    else
    {
        node *temp;

        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        node *prev, *postr;
        int pre_length, post_length;

        prev = pre(root, &pre_length);
        postr = post(root, &post_length);

        if (pre_length > post_length)
        {
            root->data = postr->data;
            root->right = delete (root->right, postr->data);
        }

        else if (pre_length < post_length)
        {
            root->data = prev->data;
            root->left = delete (root->left, prev->data);
        }

        else
        {
            root->data = prev->data;
            root->left = delete (root->left, prev->data);
        }
    }

    return root;
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

    n1 = NULL;
    n2 = NULL;
    n3 = NULL;
    n4 = NULL;
    n5 = NULL;
    n6 = NULL;
    n7 = NULL;

    in_order_traverse(root);
    printf("\n--------After Deletion-----------\n");
    delete (root, 50);
    in_order_traverse(root);
    printf("\n%d", root->data);
    return 0;
}