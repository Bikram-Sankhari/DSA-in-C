#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int partition(int *arr, int length)
{
    int i = 1, j = length - 1;
    int temp;

    while (i < j)
    {
        while ((arr[i] <= arr[0]) && (i < length))
        {
            i++;
        }

        while ((arr[j] > arr[0]) && (j > 0))
        {
            j--;
        }

        if (i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    if (arr[j] <= arr[0])
    {
        temp = arr[j];
        arr[j] = arr[0];
        arr[0] = temp;
    }
    return j;
}

void quick_sort(int *arr, int length)
{
    if (length > 1)
    {
        int partition_index;

        partition_index = partition(arr, length);

        quick_sort(arr, partition_index);
        quick_sort((arr + partition_index + 1), (length - partition_index - 1));
    }
}

int main()
{
    int length = 50;
    int *arr = (int *)malloc(length * sizeof(int));
    srand(time(0));

    for (int i = 0; i < length; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n--------After Sorting------\n");

    quick_sort(arr, length);

    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}