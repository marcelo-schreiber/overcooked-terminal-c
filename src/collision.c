#include "../include/collision.h"
#include "../include/maputils.h"

int check(char position)
{
    if (position == 'p' || position == 'H' || position == 'Q' || position == '@' || position == 'o' || position == 'P' || position == 'S' || position == 'F' || position == 'R')
        return 1;
    return 0;
}

// returns the ingredient that the player is next to or blank space if none
char isGettingIngredient(char map[MAP_HEIGHT][MAP_WIDTH], int playerX, int playerY)
{
    char up, down, left, right;

    up = map[playerY - 1][playerX];
    down = map[playerY + 1][playerX];
    left = map[playerY][playerX - 1];
    right = map[playerY][playerX + 1];

    if (check(up) == 1)
        return up;
    else if (check(down) == 1)
        return down;
    else if (check(left) == 1)
        return left;
    else if (check(right) == 1)
        return right;
    else
        return ' ';
}
