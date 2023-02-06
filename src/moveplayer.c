#include <stdlib.h>
#include "../include/maputils.h"
#include "../include/moveplayer.h"

void movePlayer(char map[MAP_HEIGHT][MAP_WIDTH], int *row, int *col, char move)
{
    int playerX = *row;
    int playerY = *col;
    // move player
    switch (move)
    {
    case 'w':
        if (map[playerX - 1][playerY] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX - 1][playerY] = '&';
        *row = *row - 1;
        break;
    case 'a':
        if (map[playerX][playerY - 1] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX][playerY - 1] = '&';
        *col = *col - 1;
        break;
    case 's':
        if (map[playerX + 1][playerY] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX + 1][playerY] = '&';
        *row = *row + 1;
        break;
    case 'd':
        if (map[playerX][playerY + 1] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX][playerY + 1] = '&';
        *col = *col + 1;
        break;
    default:
        break;
    }
}