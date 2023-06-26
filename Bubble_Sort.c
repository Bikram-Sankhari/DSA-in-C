#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void swap(int *i)
{
    int temp = *i;
    *i = *(i + 1);
    *(i + 1) = temp;
}

void *bubble_sort(int *arr, int length)
{
    int sorted = 1;

    for (int i = 0; i < (length - 1); i++)
    {
        for (int j = 0; j < (length - 2 - i); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr + j);
                sorted = 0;
            }
        }

        if (sorted == 1)
        {
            return NULL;
        }
        sorted = 1;
    }
}

int main()
{
    int *arr = (int *)malloc(5 * sizeof(int));
    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n--------After Sorting------\n");

    bubble_sort(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}