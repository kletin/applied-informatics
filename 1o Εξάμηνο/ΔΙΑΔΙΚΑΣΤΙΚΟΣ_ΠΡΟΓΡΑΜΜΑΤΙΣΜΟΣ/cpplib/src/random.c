#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genlib.h"
#include "random.h"

void Randomize(void)
{
  srand((int) time(NULL));
}

int RandomInteger(int low, int high)
{
  int k;
  double d;

  d = (double) rand() / ((double) RAND_MAX + 1);
  k = (int) (d * (high - low + 1));
  return (low + k);
}

double RandomReal(double low, double high)
{
  double d;

  d = (double) rand() / ((double) RAND_MAX + 1);
  return (low + d * (high - low));
}

bool RandomChance(double p)
{
  return (RandomReal(0, 1) < p);
}
