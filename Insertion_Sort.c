#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void insertion_sort(int *arr, int length)
{
    int element;
    for (int i = 1; i < length; i++)
    {
        element = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > element)
            {
                arr[j + 1] = arr[j];
                if (j == 0)
                {
                    arr[j] = element;
                }
            }

            else
            {
                arr[j + 1] = element;
                break;
            }
        }
    }
}

int main()
{
    int *arr = (int *)malloc(50 * sizeof(int));
    srand(time(0));
    // srand(1);

    for (int i = 0; i < 50; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n--------After Sorting------\n");

    insertion_sort(arr, 50);

    for (int i = 0; i < 50; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}