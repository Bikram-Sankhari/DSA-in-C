#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void count_sort(int *arr, int length)
{
    int max = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    int *count = (int *)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < length; i++)
    {
        count[arr[i]]++;
    }

    int *sorted_array = (int *)malloc(length * sizeof(int));
    int sorted_array_count = 0;
    for (int i = 0; i <= max; i++)
    {
        while (count[i] != 0)
        {
            sorted_array[sorted_array_count] = i;
            sorted_array_count++;
            count[i]--;
        }
    }

    for (int i = 0; i < length; i++)
    {
        arr[i] = sorted_array[i];
    }

    free(count);
    free(sorted_array);
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

    count_sort(arr, LENGTH);

    for (int i = 0; i < LENGTH; i++)

    {
        printf("%d ", arr[i]);
    }
    return 0;
}