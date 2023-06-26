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

int search(node *root, int data)
{
    if (root != NULL)
    {
        if (root->data < data)
        {
            return search(root->right, data);
        }

        else if (root->data > data)
        {
            return search(root->left, data);
        }

        else
        {
            return 1;
        }
    }

    else{
        return -1;
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

    printf("%d\n", search(root, 150));

    return 0;
}