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

node *temp = NULL;

int isBST(node *root)
{
    if (root == NULL)
    {
        return 1;
    }

    if (!isBST(root->left))
    {
        return 0;
    }

    if (temp != NULL && temp->data >= root->data)
    {
        return 0;
    }

    temp = root;
    return isBST(root->right);
}

int main()
{
    /*
                   5
            _______|________
           |                |
           6                3
       ____|____        ____|____
      |        |       |        8
      3        9            ____|_____
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

    n1 = NULL;
    n2 = NULL;
    n3 = NULL;
    n4 = NULL;
    n5 = NULL;
    n6 = NULL;
    n7 = NULL;

    printf("%d", isBST(root));

    return 0;
}