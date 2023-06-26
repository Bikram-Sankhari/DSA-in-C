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

void post_order_traverse(node *root)
{
    if (root != NULL)
    {
        post_order_traverse(root->left);
        post_order_traverse(root->right);
        printf("%d ", root->data);
    }
}

int main()
{
    /*
                    5
             _______|________
            |                |
            6                3
        ____|____            |
       |        |            8
       3        9        ____|_____
                        |          |
                        23         25
    */
    node *root = new_binary_tree(5);

    node *n1 = new_binary_tree(6);
    node *n2 = new_binary_tree(3);
    node *n3 = new_binary_tree(9);
    node *n4 = new_binary_tree(3);
    node *n5 = new_binary_tree(8);
    node *n6 = new_binary_tree(23);
    node *n7 = new_binary_tree(25);

    root->left = n1;
    root->right = n4;

    n1->left = n2;
    n1->right = n3;

    n4->right = n5;

    n5->left = n6;
    n5->right = n7;

    post_order_traverse(root);

    return 0;
}