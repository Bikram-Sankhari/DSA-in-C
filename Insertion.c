#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct a
{
    int size, capacity, *baseAddress;
} array;

array new_array(int capacity, int size)
{
    array arr;
    arr.capacity = capacity;
    arr.size = size;
    arr.baseAddress = (int *)malloc(capacity * sizeof(int));
    return arr;
}

int insert(array arr, int index, int element)
{
    if (arr.size >= arr.capacity)
    {
        arr.baseAddress = realloc(arr.baseAddress, (arr.capacity + 1) * sizeof(int));
    }
    
    for (int i = arr.size; i >= index; i--)
    {
        arr.baseAddress[i + 1] = arr.baseAddress[i];
    }
    arr.baseAddress[index] = element;
    arr.size = arr.size + 1;
    return 0;
}

int main()
{
    array arr = new_array(10, 5);

    for (int i = 0; i < arr.size; i++)
    {
        arr.baseAddress[i] = i;
    }

    insert(arr, 4, 34);

    for (int i = 0; i < arr.size; i++)
    {
        printf("%d ", arr.baseAddress[i]);
    }
    return 0;
}