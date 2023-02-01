#include <stdio.h>
#include <stdlib.h>
#include "mainmenu.h"

char printMainMenu()
{
    system("clear");
    printf(" _______           _______  _______  _______  _______  _______  _        _______  ______  \n");
    printf("(  ___  )|\\     /|(  ____ \\(  ____ )(  ____ \\(  ___  )(  ___  )| \\    /\\(  ____ \\(  __  \\ \n");
    printf("| (   ) || )   ( || (    \\/| (    )|| (    \\/| (   ) || (   ) ||  \\  / /| (    \\/| (  \\  )\n");
    printf("| |   | || |   | || (__    | (____)|| |      | |   | || |   | ||  (_/ / | (__    | |   ) |\n");
    printf("| |   | |( (   ) )|  __)   |     __)| |      | |   | || |   | ||   _ (  |  __)   | |   | |\n");
    printf("| |   | | \\ \\_/ / | (      | (\\ (   | |      | |   | || |   | ||  ( \\ \\ | (      | |   ) |\n");
    printf("| (___) |  \\   /  | (____/\\| ) \\ \\__| (____/\\| (___) || (___) ||  /  \\ \\| (____/\\| (__/  )\n");
    printf("(_______)   \\_/   (_______/|/   \\__/(_______/(_______)(_______)|_/    \\/(_______/(______/ \n\n");
    printf("Bem-vindo, pressione qualquer tecla para continuar ou 'q' para sair...\n");
    char pressed = getchar();
    system("clear");

    return pressed;
}