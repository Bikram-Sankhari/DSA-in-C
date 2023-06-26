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
    int data, height;
    node *left;
    node *right;
};

node *new_node(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;

    return new;
}

int get_height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return root->height;
}

void update_height(node *root)
{
    if (root != NULL)
    {
        int lh = get_height(root->left);
        int rh = get_height(root->right);

        if (lh <= rh)
        {
            root->height = rh + 1;
        }

        else
        {
            root->height = lh + 1;
        }
    }
}

int balance_factor(node *root)
{
    if (root != NULL)
    {
        int lh = get_height(root->left);
        int rh = get_height(root->right);

        return (lh - rh);
    }
    return 0;
}

node *rotate_left(node *root)
{
    node *result = root->right;
    node *temp = root->right->left;
    root->right->left = root;
    root->right = temp;
    update_height(root);
    update_height(result);

    return result;
}

node *rotate_right(node *root)
{
    node *result = root->left;
    node *temp = root->left->right;
    root->left->right = root;
    root->left = temp;
    update_height(root);
    update_height(result);

    return result;
}

node *apply_rotation(node *root)
{
    int bf = balance_factor(root);

    if (bf < -1)
    {
        if (balance_factor(root->right) == 1)
        {
            root->right = rotate_right(root->right);
        }
        return rotate_left(root);
    }

    if (bf > 1)
    {
        if (balance_factor(root->left) == -1)
        {
            root->left = rotate_left(root->left);
        }
        return rotate_right(root);
    }

    return root;
}

node *insert_internal(node *root, int data)
{
    if (root == NULL)
    {
        node *new = new_node(data);
        return new;
    }

    if (root->data == data)
    {
        printf("Duplicate Elemenet\n");
    }

    if (root->data > data)
    {
        root->left = insert_internal(root->left, data);
    }

    else if (root->data < data)
    {
        root->right = insert_internal(root->right, data);
    }

    update_height(root);
    return apply_rotation(root);
}

void insert(node **root, int data)
{
    *root = insert_internal(*root, data);
}

node *delete_internal(node *root, int key)
{
    if (root == NULL)
    {
        printf("Key Doesn't exists in Tree\n");
    }

    if (root->data > key)
    {
        root->left = delete_internal(root->left, key);
    }

    else if (root->data < key)
    {
        root->right = delete_internal(root->right, key);
    }

    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }

        node *temp = root->left;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }

        root->data = temp->data;
        root->left = delete_internal(root->left, temp->data);
    }

    update_height(root);
    return apply_rotation(root);
}

void delete(node **root, int key)
{
    *root = delete_internal(*root, key);
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
                            40
                 ____________|____________
                |                         |
                20                       70
             ___|___             _________|_________
            |       |           |                   |
            10      30          50                  80
         ___|____           ____|_____         _____|______
        |                  |          |                    |
        5                  45         60                   90

    */
    node *root = new_node(10);
    insert(&root, 20);
    insert(&root, 30);
    // insert(&root, 40);
    // insert(&root, 45);
    // insert(&root, 50);
    // insert(&root, 60);
    // insert(&root, 70);
    // insert(&root, 80);
    // insert(&root, 90);
    insert(&root, 5);

    in_order_traverse(root);
    printf("\n%d", root->data);
    printf("\n-----------------------------------After Deletion----------------------------\n");
    delete (&root, 30);
    in_order_traverse(root);
    printf("\n%d", root->data);

    return 0;
}