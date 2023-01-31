#include <stdio.h>
#include <stdlib.h>

#include "pedido.h"
#include "maputils.h"
#include "cliente.h"
#include "collision.h"

// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

int main()
{
    int c;
    static struct termios oldt, newt;
    Cliente *q = malloc(sizeof(Cliente));
    initializeQueue(q, 2);
    adicionarPedido(q, 1); // x-burger

    Pedido *p = malloc(sizeof(Pedido));
    initializeStack(p, 7);

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    // game map
    char map[6][21] = {
        "#--------|@|--------#",
        "|  [R]              |",
        "|  [F]             o|",
        "|       &           |",
        "|[p] [H] [Q] [S] [P]|",
        "#-------------------#"};

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printMap(map);
    char move = getchar();
    char ingredient = ' ';

    while (move == 'w' || move == 'a' || move == 's' || move == 'd')
    {
        system("clear"); // clear screen
        printMap(map);
        printStack(p);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        move = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings

        int row, col;
        findChar(map, '&', &row, &col);

        // move player
        switch (move)
        {
        case 'w':
            if (map[row - 1][col] != ' ')
                break;
            map[row][col] = ' ';
            map[row - 1][col] = '&';
            break;
        case 'a':
            if (map[row][col - 1] != ' ')
                break;
            map[row][col] = ' ';
            map[row][col - 1] = '&';
            break;
        case 's':
            if (map[row + 1][col] != ' ')
                break;
            map[row][col] = ' ';
            map[row + 1][col] = '&';
            break;
        case 'd':
            if (map[row][col + 1] != ' ')
                break;
            map[row][col] = ' ';
            map[row][col + 1] = '&';
            break;
        default:
            break;
        }

        // collision
        ingredient = isGettingIngredient(map, col, row);

        // add or remove ingredient from stack
        if (ingredient == 'o')
            pop(p);
        else if (ingredient != ' ')
            push(p, ingredient);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}