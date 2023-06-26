#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int linear_search(int *array, int size, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == element)
        {
            printf("Element found in linear_search at index %d\n", i);
            return 0;
        }
    }

    printf("Element not found in linear search");
    return -1;
}

int binary_search(int *array, int size, int element)
{
    int end = size - 1, start = 0, mid;

    while (1)
    {
        if (array[start] == element)
        {
            printf("Element found in binary_search at index %d\n", start);
            return 0;
        }

        else if (array[end] == element)
        {
            printf("Element found in binary_search at index %d\n", end);
            return 0;
        }

        else
        {
            mid = (start + end) / 2;

            if (array[mid] == element)
            {
                printf("Element found in binary_search at index %d\n", mid);
                return 0;
            }

            else if (array[mid] > element)
            {
                end = mid;
            }

            else if (array[mid] < element)
            {
                start = mid;
            }
        }

        if (abs(end - start) == 1)
        {
            printf("Element not found in binary_search");
            return -1;
        }
    }
}

int main()
{
    int *sorted_array = (int *)malloc(10 * sizeof(int));
    sorted_array[0] = 2;
    sorted_array[1] = 28;
    sorted_array[2] = 43;
    sorted_array[3] = 65;
    sorted_array[4] = 78;
    sorted_array[5] = 90;
    sorted_array[6] = 123;
    sorted_array[7] = 212;
    sorted_array[8] = 564;
    sorted_array[9] = 2345;

    // linear_search(sorted_array, 10, 212);
    binary_search(sorted_array, 10, 28);
    return 0;
}