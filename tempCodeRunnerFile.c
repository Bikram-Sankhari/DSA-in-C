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

int balance_factor(node *root)
{
    int lh = get_height(root->left);
    int rh = get_height(root->right);

    return (lh - rh);
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

    else
    {
        return -1;
    }
}

int lengthOfLongestSubstring(char *s)
{
    int results[strlen(s)], result, results_count = 0;
    node *baad = NULL;
    char c;

    for (int i = 0; i < strlen(s); i++)
    {
        c = (int)*(s + i);
        if (search(baad, c) == -1)
        {
            result++;
            insert(&baad, c);
        }

        else
        {
            results[results_count] = result;
            results_count++;
            result = 0;
            free(baad);
            baad = NULL;
            i--;
        }
    }

    results[results_count] = result;
    results_count++;

    int max = 0;
    for (int i = 0; i < results_count; i++)
    {
        if (results[i] > max)
        {
            max = results[i];
        }
    }

    return max;
}

int main()
{
    char *name = "abcabcbb";
    int d = lengthOfLongestSubstring(name);
    printf("%d", d);
    return 0;
}
