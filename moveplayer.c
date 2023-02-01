#include <stdlib.h>
#include "moveplayer.h"

void movePlayer(char map[6][21], int playerX, int playerY, char move)
{
    // move player
    switch (move)
    {
    case 'w':
        if (map[playerX - 1][playerY] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX - 1][playerY] = '&';
        break;
    case 'a':
        if (map[playerX][playerY - 1] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX][playerY - 1] = '&';
        break;
    case 's':
        if (map[playerX + 1][playerY] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX + 1][playerY] = '&';
        break;
    case 'd':
        if (map[playerX][playerY + 1] != ' ')
            break;
        map[playerX][playerY] = ' ';
        map[playerX][playerY + 1] = '&';
        break;
    default:
        break;
    }
}