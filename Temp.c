#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int visited[8] = {0};

void dfs(int node, int graph[][8])
{
    printf("%d ", node);
    visited[node] = 1;

    for (int i = 0; i < 8; i++)
    {
        if (graph[node][i] == 1 && visited[i] == 0)
        {
            dfs(i, graph);
        }
    }

    return;
}

int main()
{
    int graph[8][8] = {
        //   0  1  2  3  4  5  6  7
        {0, 1, 1, 1, 0, 0, 0, 0}, // 0
        {1, 0, 0, 0, 0, 0, 0, 0}, // 1
        {1, 0, 0, 1, 0, 0, 0, 0}, // 2
        {1, 0, 1, 0, 1, 1, 0, 0}, // 3
        {0, 0, 0, 1, 0, 0, 0, 0}, // 4
        {0, 0, 0, 1, 0, 0, 1, 1}, // 5
        {0, 0, 0, 0, 0, 1, 0, 0}, // 6
        {0, 0, 0, 0, 0, 1, 0, 0}  // 7
    };

    dfs(graph[0][1], graph);
    return 0;
}