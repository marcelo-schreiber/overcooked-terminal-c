#include <stdio.h>
#include <stdlib.h>
#include "maputils.h"

// print map function
void printMap(char map[6][21])
{
    system("clear");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

// find character function
void findChar(char map[6][21], char c, int *x, int *y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (map[i][j] == c)
            {
                *x = i;
                *y = j;
            }
        }
    }
}