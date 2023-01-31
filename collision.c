int check(char position)
{
    if (position == 'p' || position == 'H' || position == 'Q' || position == 'o' || position == 'P' || position == 'S' || position == 'F' || position == 'R')
        return 1;
    return 0;
}

char isGettingIngredient(char map[6][21], int playerX, int playerY)
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
