#include <stdio.h>
#include <stdlib.h>

#include "../include/pedido.h"
#include "../include/maputils.h"
#include "../include/cliente.h"
#include "../include/collision.h"
#include "../include/mainmenu.h"
#include "../include/moveplayer.h"

// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

int main()
{
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
    char map[MAP_HEIGHT][MAP_WIDTH] = {
        "                                ",
        "                                ",
        "                                ",
        "                                ",
        "                                ",
        "                                ",
        " #----------------------------# ",
        " |[P]  [p]         [Q]        | ",
        " |                            | ",
        " |                            | ",
        " |                         [S]| ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " |              [F]           | ",
        " #-------------------         | ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " @                            | ",
        " @                            | ",
        " @                &           | ",
        " @                            | ",
        " @                            | ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " |     [H]                   o| ",
        " #----------------------------# ",
        "                                "

    };

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
    char quitted = printMainMenu() == 'q';
    if (quitted)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings before quitting
        return 0;
    }

    printMap(map);
    char move = getchar();
    char ingredient = ' ';

    while (move == 'w' || move == 'a' || move == 's' || move == 'd')
    {
        system("clear"); // clear screen
        printMap(map);
        printStack(p); // prints current ingredients

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        move = getchar();                        // get next move
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore

        int row, col;
        findChar(map, '&', &row, &col);
        movePlayer(map, row, col, move);

        // collision
        ingredient = isGettingIngredient(map, col, row);

        // add or remove ingredient from stack
        if (ingredient == 'o')
            pop(p);
        else if (ingredient != ' ')
            push(p, ingredient);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore to old settings before quitting
    return 0;
}