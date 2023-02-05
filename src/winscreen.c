#include <stdio.h>
#include <stdlib.h>

#include "../include/colors.h"

char displayWinScreen(int points)
{
  system("clear");
  red();
  // one printf per line
  printf("           ¤               ╬             ╬\n");
  printf("                   ╬      (¤)           (¤)      ╬\n");
  printf("                  (¤)      |             |      (¤)\n");
  printf("                   |      |~|      ¤    |~|      |          ¤\n");
  printf(" ¤                |~|     | |           | |     |~|\n");
  printf("                 ,| |a©©©©| |©©©©©©©©©©©| |©©©©a| |.\n");
  printf("            .,a©©©| |©©©©©| |©©©©©©©©©©©| |©©©©©| |©©©©a,.\n");
  printf("   ¤      ,a©©©©©©| |©©©©©©©©©©©©.©©©©©©©©©©©©©©| |©©©©©©©a,\n");
  printf("         a©©©©©©©©©©©©©©©©©©©©©' . `©©©©©©©©©©©©©©©©©©©©©©©©a\n");
  printf("         ;`©©©©©©©©©©©©©©©©©©'   .   `©©©©©©©©©©©©©©©©©©©©©';\n");
  printf("         ;©©©`©©©©©©©©©©©©©'     .     `©©©©©©©©©©©©©©©©'©©©;\n");
  printf("         ;©©©;,.aaaaaaaaaa       .       aaaaa,,aaaaaaa,;©©©;\n");
  printf("         ;;©;;;;©©©©©©©©;©      ©.©      ;©©©;;;©©©©©©;;;;©©;\n");
  printf("         ;;;;;;;©©©©;©©;;©    ©© . ©©    ;;©;;;;©©;©©©;;;;;;;\n");
  printf("         ;;;;;;;;©©;;;;;;;  ©©   .   ©©  ;;;;;;;;;;;©©;;;;©;;;\n");
  printf("         ;;;;;;;;;;;;;;;;;©©     .     ©©;;;;;;;;;;;;;;;;©©a;\n");
  printf("     ,▓▓▓;;;;;;;;©;;;;;;;;       .       ;;;;;;;;;;;;;;;;©©;;▓▓▓,\n");
  printf("  .▓▓▓▓▓▓;;;;;;;a©;;;;;;;;     ,▓▓▓,     ;;;;;;;;;;;;;;;;;;;;▓▓▓▓▓▓,\n");
  printf(" .▓▓▓▓▓▓▓;;;;;;;©©;;;;;;;;   ,▓▓▓▓▓▓▓,   ;;;;;;;;;;;;;;;;;;;;▓▓▓▓▓▓▓,\n");
  printf(" ▓▓▓▓▓▓▓▓`;;;;;;;;;;;;;;;;  ▓▓▓▓▓▓▓▓▓▓▓  ;;;;;;;;;;;;;;;;;;;'▓▓▓▓▓▓▓▓\n");
  printf(" ▓▓▓▓▓▓▓▓▓▓▓▓`;;;;;;;;;;;;,▓▓▓▓▓▓▓▓▓▓▓▓▓,;;;;;;;;;;;;;;;'▓▓▓▓▓▓▓▓▓▓▓▓\n");
  printf(" `▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓,,,,,,,▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓,,,,,,,▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓'\n");
  printf("   `▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓'\n");
  printf("       `▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓'\n");
  printf("              \"\"\"\"\"\"\"\"\"\"\"\"\"\"`,,,,,,,,,'\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\" \n");
  printf("                             `▓▓▓▓▓▓▓'\n");
  printf("                              `▓▓▓▓▓'\n");
  printf("                                ▓▓▓\n");
  printf("                               ▓▓▓▓▓\n");
  printf("                            .,▓▓▓▓▓▓▓,.\n");
  printf("                       ,▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓,\n\n");
  reset();
  yellow();
  printf("Congratulations!\n");
  reset();
  green();
  printf("You have won the game with %d points!\n\n", points);
  reset();
  printf("Press any key to continue...");
  return getchar();
};