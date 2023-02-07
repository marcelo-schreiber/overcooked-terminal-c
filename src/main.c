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
#include "../include/patience.h"

// terminal utils
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

#define MAX_WRONG_ORDERS 3
#define POINTS_PER_ORDER 10
#define POINTS_PER_WRONG_ORDER 10
#define MAX_TIME_PER_ORDER 25

// global variables for comunicating between threads
struct thread_args
{
    Cliente *q;

    pthread_t *threadId;
    int *wrongOrders;
    int *points;
    int *percentage;
};

void *timeout_thread(void *arg)
{
    struct thread_args arg_struct = *(struct thread_args *)arg;
    // get percentage from args
    int *percentage = arg_struct.percentage;

    for (*percentage = 0; *percentage < 100; *percentage += 100 / MAX_TIME_PER_ORDER) // 20 seconds to complete an order
        sleep(1);

    Cliente *q = (Cliente *)arg_struct.q;
    int *wrongOrders = arg_struct.wrongOrders;
    int *points = arg_struct.points;
    pthread_t *threadId = arg_struct.threadId;

    dequeue(q);
    *points -= POINTS_PER_WRONG_ORDER / 2;
    *wrongOrders += 1;

    struct thread_args *new_arg_struct = malloc(sizeof(struct thread_args));
    new_arg_struct->q = q;
    new_arg_struct->wrongOrders = wrongOrders;
    new_arg_struct->points = points;
    new_arg_struct->percentage = percentage;
    new_arg_struct->threadId = threadId;

    if (isEmpty(q) == 0)
        pthread_create(threadId, NULL, timeout_thread, (void *)new_arg_struct);

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
    static struct termios oldt, newt;
    pthread_t threadId;
    int points = 0;
    int row, col;
    findChar(map, '&', &row, &col);

    int wrongOrders = 0;
    int percentage = 0;
    int numOfOrders = 6;
    char ingredient = ' ';

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // disable echo and canonical mode

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
    char quitted = printMainMenu() == 'q';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings before quitting

    if (quitted)
        return 0;

    printMap(map);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set to new settings
    char move = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings before quitting

    Pedido *p = malloc(sizeof(Pedido));
    Cliente *q = malloc(sizeof(Cliente));

    addRandomOrder(q, numOfOrders);

    struct thread_args *arg_struct = malloc(sizeof(struct thread_args));
    arg_struct->q = q;
    arg_struct->wrongOrders = &wrongOrders;
    arg_struct->points = &points;
    arg_struct->percentage = &percentage;
    arg_struct->threadId = &threadId;

    // start thread
    pthread_create(&threadId, NULL, timeout_thread, (void *)arg_struct);

    // main game loop
    while (1)
    {
        // check if player lost
        if (wrongOrders == MAX_WRONG_ORDERS)
        {
            free(q); // free memory
            free(p);
            pthread_cancel(threadId); // cancel thread

            displayGameOverScreen(points);

            break;
        }

        // check if player won
        else if (isEmpty(q) == 1)
        {
            free(q); // free memory
            free(p);
            pthread_cancel(threadId);

            displayWinScreen(points);

            break;
        }

        system("clear"); // clear screen
        printMap(map);

        // collision
        ingredient = isGettingIngredient(map, col, row);

        // add or remove ingredient from stack
        if (ingredient == 'o')
            pop(p);
        if (ingredient == '@' && isEmptyStack(p) == 0)
        {
            percentage = 0; // reset patience bar

            if (checkOrder(q, p) == -1)
            {
                points -= POINTS_PER_WRONG_ORDER;
                wrongOrders++;
            }
            else
                points += POINTS_PER_ORDER;
        }
        if (ingredient != ' ' && ingredient != 'o' && ingredient != '@')
            push(p, ingredient);

        printStack(p);                     // prints current ingredients
        printPatience(points, percentage); // prints patience bar and points
        printQueue(q);                     // prints current orders

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        move = getchar(); // get next move
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        movePlayer(map, &row, &col, move);
    }

    pthread_exit(NULL);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings before quitting

    return 0;
}