#include <stdio.h>
#include <stdlib.h>

#include <pthread.h> // printing while getting input
#include <string.h>  // memset
#include <math.h>    // sin, cos
#include <ncurses.h> // get terminal size

#include "../include/mainmenu.h"

#define MAX_COLS 90
#define MAX_LINES 35

void checkTerminalSize(void)
{
    int h, w;
    initscr();
    getmaxyx(stdscr, h, w);
    endwin();
    if ((h < MAX_LINES) || (w < MAX_COLS))
    {
        fprintf(stderr, "\nSorry.\n");
        fprintf(stderr, "To play Pacman for Console, your console window must be at least %dx%d\n", MAX_COLS, MAX_LINES);
        fprintf(stderr, "Currently It's %dx%d\n", w, h);
        fprintf(stderr, "Please resize your window/resolution and re-run the game.\n\n");
        exit(0);
    }
}

void printLogo(void)
{
    printf(" _______           _______  _______  _______  _______  _______  _        _______  ______  \n");
    printf("(  ___  )|\\     /|(  ____ \\(  ____ )(  ____ \\(  ___  )(  ___  )| \\    /\\(  ____ \\(  __  \\ \n");
    printf("| (   ) || )   ( || (    \\/| (    )|| (    \\/| (   ) || (   ) ||  \\  / /| (    \\/| (  \\  )\n");
    printf("| |   | || |   | || (__    | (____)|| |      | |   | || |   | ||  (_/ / | (__    | |   ) |\n");
    printf("| |   | |( (   ) )|  __)   |     __)| |      | |   | || |   | ||   _ (  |  __)   | |   | |\n");
    printf("| |   | | \\ \\_/ / | (      | (\\ (   | |      | |   | || |   | ||  ( \\ \\ | (      | |   ) |\n");
    printf("| (___) |  \\   /  | (____/\\| ) \\ \\__| (____/\\| (___) || (___) ||  /  \\ \\| (____/\\| (__/  )\n");
    printf("(_______)   \\_/   (_______/|/   \\__/(_______/(_______)(_______)|_/    \\/(_______/(______/ \n\n");
    printf("Bem-vindo ao overcooked em...\n");
}

void *printDonut(void *arg)
{
    int k;
    double sin(), cos();
    char *input = (char *)arg;
    float A = 0, B = 1.2, i, j, z[1760];
    char b[1760];
    printf("\x1b[2J");
    while (*input == ' ')
    {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (j = 0; 6.28 > j; j += 0.07)
        {
            for (i = 0; 4.05 > i; i += 0.02)
            {
                float sini = sin(i),
                      cosj = cos(j),
                      sinA = sin(A),
                      sinj = sin(j),
                      cosA = cos(A),
                      cosj2 = cosj + 2,
                      mess = 1 / (sini * cosj2 * sinA + sinj * cosA + 5),
                      cosi = cos(i),
                      cosB = cos(B),
                      sinB = sin(B),
                      t = sini * cosj2 * cosA - sinj * sinA;
                int x = 40 + 30 * mess * (cosi * cosj2 * cosB - t * sinB),
                    y = 12 + 15 * mess * (cosi * cosj2 * sinB + t * cosB),
                    o = x + 80 * y,
                    N = 8 * ((sinj * sinA - sini * cosj * cosA) * cosB - sini * cosj * sinA - sinj * cosA - cosi * cosj * sinB);
                if (22 > y && y > 0 && x > 0 && 80 > x && mess > z[o])
                {
                    z[o] = mess;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[d");
        printLogo();
        for (k = 0; 1761 > k; k++)
            putchar(k % 80 ? b[k] : 10);
        printf("Pressione qualquer tecla para começar ou 'q' para sair...\n");
        A += 0.005;
    }

    return NULL;
}

char printMainMenu()
{
    char input = ' ';
    pthread_t thread;
    system("clear");
    checkTerminalSize();
    pthread_create(&thread, NULL, printDonut, &input); // print menu
    input = getchar();                                 // get input in another thread
    pthread_join(thread, NULL);                        // wait for thread to finish with user input

    system("clear");

    return input;
}