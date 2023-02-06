#include <stdio.h>
#include "../include/colors.h"

void printPatience(int points, int percentage)
{
  const int patience = 100 - percentage;

  printf("\n");

  red();
  printf("Points: %d", points);
  reset();

  printf(" | "); // Separator

  if (patience > 66)
  {
    green();
    printf(":)");
  }
  else if (patience > 33)
  {
    yellow();
    printf(":|");
  }
  else
  {
    red();
    printf(":(");
  }

  printf("\t");
  // Print initial loading bar
  const int barLengthMax = 5;
  printf("|");
  for (int i = 0; i < 100 / barLengthMax; i++)
  {
    if (i < percentage / barLengthMax)
      printf("▓");
    else
      printf("░");
  }
  printf("|");
  reset();
  printf("\n");
};