#include <stdio.h>
#include <stdlib.h>
#include "../include/maputils.h"
#include "../include/colors.h"

// print map function
void printMap(char map[MAP_HEIGHT][MAP_WIDTH])
{
    system("clear");
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            switch (map[i][j]) // print different characters that occupy 2 bits instead of 1 bit, to prevent variable array size
            {
            case '#':
                printf("┼");
                break;
            case '|':
                printf("│");
                break;
            case '-':
                printf("─");
                break;
            case '@':
                printf("«");
                break;
            case 'o':
                darkGray();
                printf("Ø");
                reset();
                break;
            case 'p':
                lightBrown();
                printf("p");
                reset();
                break;
            case 'P':
                lightBrown();
                printf("P");
                reset();
                break;
            case 'H':
                brown();
                printf("H");
                reset();
                break;
            case 'Q':
                yellow();
                printf("Q");
                reset();
                break;
            case 'F':
                yellow();
                printf("F");
                reset();
                break;
            case 'R':
                red();
                printf("R");
                reset();
                break;
            case 'S':
                green();
                printf("S");
                reset();
                break;
            default:
                printf("%c", map[i][j]);
            }
            //  if (position == 'p' || position == 'H' || position == 'Q' || position == '@' || position == 'o' || position == 'P' || position == 'S' || position == 'F' || position == 'R')
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