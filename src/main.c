#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "../include/pedido.h"
#include "../include/maputils.h"
#include "../include/cliente.h"
#include "../include/collision.h"
#include "../include/mainmenu.h"
#include "../include/moveplayer.h"
#include "../include/gameover.h"
#include "../include/winscreen.h"
#include "../include/colors.h"

// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

#define MAX_WRONG_ORDERS 3
#define POINTS_PER_ORDER 10
#define POINTS_PER_WRONG_ORDER 5
#define MAX_TIME_PER_ORDER 20

// global variables for comunicating between threads
pthread_t threadId;
int percentage = 0;
int wrongOrders = 0;

void *timeout_thread(void *arg)
{
    for (percentage = 0; percentage < 100; percentage += 100 / MAX_TIME_PER_ORDER) // 20 seconds to complete an order
        sleep(1);

    Cliente *q = (Cliente *)arg;
    dequeue(q);
    wrongOrders++;

    if (isEmpty(q) == 0)
        pthread_create(&threadId, NULL, timeout_thread, (void *)q);
    else
    {
        displayGameOverScreen(3); // TODO: make a timed out game over screen
        pthread_cancel(threadId);
        pthread_exit(NULL);
        exit(0);
    }

    return NULL;
}

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

    Pedido *p = malloc(sizeof(Pedido));
    Cliente *q = malloc(sizeof(Cliente));

    int numOfOrders = 1;
    addRandomOrder(q, numOfOrders);

    pthread_create(&threadId, NULL, timeout_thread, (void *)q);
    // main game loop
    while (1)
    {
        system("clear"); // clear screen

        if (wrongOrders == MAX_WRONG_ORDERS)
        {
            free(q); // free memory
            free(p);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
            displayGameOverScreen(points);

            system("clear");
            break;
        }

        printMap(map);
        findChar(map, '&', &row, &col);

        // collision
        ingredient = isGettingIngredient(map, col, row);

        // add or remove ingredient from stack
        if (ingredient == 'o')
            pop(p);
        else if (ingredient == '@' && isEmptyStack(p) == 0)
        {
            percentage = 0; // reset patience bar

            if (checkOrder(q, p) == -1)
            {
                points -= POINTS_PER_WRONG_ORDER;
                wrongOrders++;
            }
            else
                points += POINTS_PER_ORDER;

            // check if queue is empty
            if (isEmpty(q) == 1 && wrongOrders != MAX_WRONG_ORDERS) // prevent losing and winning at the same time
            {

                free(q); // free memory
                free(p);
                tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
                displayWinScreen(points);

                system("clear");
                break;
            }
        }
        else if (ingredient != ' ' && ingredient != 'o' && ingredient != '@')
            push(p, ingredient);

        red();
        printf("Points: %d | Patience meter: %d%%\n", points, 100 - percentage);
        reset();

        printQueue(q); // prints current orders
        printStack(p); // prints current ingredients

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        move = getchar(); // get next move
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        movePlayer(map, row, col, move);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    pthread_cancel(threadId);
    pthread_exit(NULL);

    return 0;
}