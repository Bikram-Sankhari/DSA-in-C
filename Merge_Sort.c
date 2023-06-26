#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void merge(int *a, int a_length, int *b, int b_length)
{
    int *c = (int *)malloc((a_length + b_length) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < a_length && j < b_length)
    {
        if (a[i] < b[j])
        {
            c[k] = a[i];
            i++;
            k++;
        }

        else
        {
            c[k] = b[j];
            j++;
            k++;
        }
    }

    if (i == a_length)
    {
        for (j; j < b_length; j++)
        {
            c[k] = b[j];
            k++;
        }
    }

    else
    {
        for (i; i < a_length; i++)
        {
            c[k] = a[i];
            k++;
        }
    }

    for (int i = 0; i < k; i++)
    {
        a[i] = c[i];
    }

    free(c);
}

void merge_sort(int *arr, int length)
{
    if (length > 1)
    {
        merge_sort(arr, length / 2);
        merge_sort((arr + length / 2), (length - length / 2));
        merge(arr, length / 2, (arr + length / 2), (length - length / 2));
    }
}

int main()
{
    int LENGTH = 50;
    int RANGE = 100;
    int *arr = (int *)malloc(LENGTH * sizeof(int));
    srand(time(0));

    for (int i = 0; i < LENGTH; i++)
    {
        arr[i] = rand() % RANGE;
        printf("%d ", arr[i]);
    }
    printf("\n--------After Sorting------\n");

    merge_sort(arr, LENGTH);

    for (int i = 0; i < LENGTH; i++)

    {
        printf("%d ", arr[i]);
    }
    return 0;
}