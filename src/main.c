#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/pedido.h"
#include "../include/maputils.h"
#include "../include/cliente.h"
#include "../include/collision.h"
#include "../include/mainmenu.h"
#include "../include/moveplayer.h"
// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

int checkOrder(Cliente *q, Pedido *p)
{
    char *pedido = peek(q);
    char ingrediente;
    int correctOrder = 1;

    for (int i = strlen(pedido) - 1; i >= 0; i--)
    {
        ingrediente = pop(p);
        if (pedido[i] != ingrediente)
            correctOrder = -1;
    }

    if (correctOrder == 1)
        dequeue(q);

    popAll(p);

    return correctOrder;
}
int randomNumber(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void addRandomOrder(Cliente *q, int size)
{
    initializeQueue(q, size);
    for (int i = 0; i < size; i++)
        adicionarPedido(q, randomNumber(1, 6));
}

int main()
{
    srand(time(NULL));
    static struct termios oldt, newt;
    Cliente *q = malloc(sizeof(Cliente));
    addRandomOrder(q, randomNumber(3, 6));

    Pedido *p = malloc(sizeof(Pedido));

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    // game map
    char map[MAP_HEIGHT][MAP_WIDTH] = {
        " #----------------------------# ",
        " |[P]  [p]         [Q]        | ",
        " |                            | ",
        " |                            | ",
        " |                            | ",
        " |                         [S]| ",
        " |                            | ",
        " |                            | ",
        " |              [F]           | ",
        " #-------------------         | ",
        " |     [R]                    | ",
        " |                            | ",
        " @                            | ",
        " @                &           | ",
        " @                            | ",
        " |                            | ",
        " |     [H]                   o| ",
        " #----------------------------# ",
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

    int points = 0;

    while (move == 'w' || move == 'a' || move == 's' || move == 'd')
    {
        system("clear"); // clear screen
        printMap(map);
        printStack(p); // prints current ingredients
        printQueue(q); // prints current orders
        printf("Pontos: %d", points);

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
        else if (ingredient == '@')
        {
            points += checkOrder(q, p);
        }

        else if (ingredient != ' ')
            push(p, ingredient);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore to old settings before quitting
    return 0;
}