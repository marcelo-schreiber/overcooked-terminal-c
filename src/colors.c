#include <stdio.h>
void reset()
{
  printf("\033[0m");
}
void brown() { printf("\033[0;33m"); }
void darkGray() { printf("\033[1;30m"); }
void lightBrown() { printf("\033[0;35m"); }
void red() { printf("\033[1;31m"); }
void green() { printf("\033[0;32m"); }
void yellow() { printf("\033[1;33m"); }