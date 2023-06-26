#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void selection_sort(int *arr, int length)
{
    int element, p;
    for (int i = 0; i < length - 1; i++)
    {
        element = arr[i];
        p = i;
        for (int j = i; j < length; j++)
        {
            if (arr[j] < element)
            {
                element = arr[j];
                p = j;
            }
        }
        arr[p] = arr[i];
        arr[i] = element;
    }
}

int main()
{
    int *arr = (int *)malloc(5 * sizeof(int));
    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        arr[i] = rand() % 10;
        printf("%d ", arr[i]);
    }
    printf("\n--------After Sorting------\n");

    selection_sort(arr, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}