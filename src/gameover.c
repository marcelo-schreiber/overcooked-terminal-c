#include <stdio.h>
#include <stdlib.h>

#include "../include/gameover.h"
#include "../include/colors.h"

char displayGameOverScreen(int points)
{
  system("clear");
  brown();
  printf("   _____          __  __ ______    ______      ________ _____\n");
  printf("  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n");
  printf(" | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n");
  printf(" | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /\n");
  printf(" | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n");
  printf("  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n");
  red();
  printf("                  _   _                     __  __\n");
  printf("                 | | (_)                   / /  \\ \\            \n");
  printf("   ___ ___  _ __ | |_ _ _ __  _   _  ___  | | ___| |\n");
  printf("  / __/ _ \\| '_ \\| __| | '_ \\| | | |/ _ \\ | |/ __| |\n");
  printf(" | (_| (_) | | | | |_| | | | | |_| |  __/ | | (__| |\n");
  printf("  \\___\\___/|_| |_|\\__|_|_| |_|\\__,_|\\___| | |\\___| |\n");
  printf("              _ _      __    __            \\_\\  /_/\n");
  printf("             (_) |    / /    \\ \\                               \n");
  printf("   __ _ _   _ _| |_  | | __ _ | |\n");
  printf("  / _` | | | | | __| | |/ _` || |\n");
  printf(" | (_| | |_| | | |_  | | (_| || |\n");
  printf("  \\__, |\\__,_|_|\\__| | |\\__, || |\n");
  printf("     | |              \\_\\  | /_/\n");
  printf("     |_|                   |_| \n");
  reset();
  printf("\n");
  darkGray();
  // print the comment above with printfs escaping backslashes
  printf("       (\\ \n");
  printf("        \\ \\ \n");
  printf("    __    \\/ ___,.-------..__        __ \n");
  printf("   //\\\\ _,-'\\\\               `'--._ //\\\\ \n");
  printf("   \\\\ ;'      \\\\        :(         `: //  You scored %d points! \n", points);
  printf("    `(          \\\\                   )' \n");
  printf("      :.          \\\\,----,         ,; \n");
  printf("       `.`--.___   (    /  ___.--',' \n");
  printf("         `.     ``-----'-''     ,' \n");
  printf("            -.               ,- \n");
  printf("               `-._______.-' \n");
  reset();

  return getchar();
};