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
#include "../include/gameover.h"
#include "../include/winscreen.h"

// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

#define POINTS_PER_ORDER 10
#define POINTS_PER_WRONG_ORDER -5

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
    int wrongOrders = 0;
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
    int row, col;

    while (move == 'w' || move == 'a' || move == 's' || move == 'd')
    {
        system("clear"); // clear screen

        if (wrongOrders == 3)
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
            char hasContinued = displayGameOverScreen(points);
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings

            free(q); // free memory
            free(p);
            if (hasContinued != 'c')
                break;

            wrongOrders = 0;
            points = 0;

            // reset queue
            q = malloc(sizeof(Cliente));
            addRandomOrder(q, randomNumber(3, 6));

            // reset stack
            p = malloc(sizeof(Pedido));

            // set player to initial position
            findChar(map, '&', &row, &col);
            map[row][col] = ' ';
            map[13][16] = '&'; // 13 16 is the default position
        }

        printMap(map);
        findChar(map, '&', &row, &col);

        // collision
        ingredient = isGettingIngredient(map, col, row);

        // add or remove ingredient from stack
        if (ingredient == 'o')
            pop(p);
        else if (ingredient == '@')
        {
            if (checkOrder(q, p) == -1)
            {
                points += POINTS_PER_WRONG_ORDER;
                wrongOrders++;
            }
            else
                points += POINTS_PER_ORDER;

            // check if won the game
            if (isEmpty(q) == 1)
            {
                free(q); // free memory
                free(p);

                tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
                displayWinScreen(points);
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
                system("clear");
                break;
            }
        }
        else if (ingredient != ' ')
            push(p, ingredient);

        printQueue(q); // prints current orders

        printf("Points: %d\n", points);
        printStack(p); // prints current ingredients

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        move = getchar();                        // get next move
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore

        movePlayer(map, row, col, move);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore to old settings before quitting
    return 0;
}