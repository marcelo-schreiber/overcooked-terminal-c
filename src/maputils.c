#include <stdio.h>
#include <stdlib.h>
#include "../include/maputils.h"

// print map function
void printMap(char map[MAP_HEIGHT][MAP_WIDTH])
{
    system("clear");
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

// find character function
void findChar(char map[MAP_HEIGHT][MAP_WIDTH], char c, int *x, int *y)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j] == c)
            {
                *x = i;
                *y = j;
            }
        }
    }
}