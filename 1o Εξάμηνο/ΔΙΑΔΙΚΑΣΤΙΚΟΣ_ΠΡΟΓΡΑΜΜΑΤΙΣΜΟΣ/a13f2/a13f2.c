/*File: a13f2.c
* -------------
* askhsh 13 fylladio 2
*/

#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

int main()

{
  int kafedes;
  double timi = 0.7;
  double resta;
  int k2,k1,k50,k20,k10;

  printf("Dwse kafedes:");
  kafedes = GetInteger();

  if ((kafedes * timi) > 5.0) {
    printf("Sfalma");
    return 1;
  }
  resta = 5.0 - (kafedes * timi);
  printf("Resta: %.2f\n", resta);

  k2 = resta / 2;
  printf ("Kermata twn  2E: %d\n",k2);
  if (k2>0) {
    resta = resta - 2*k2;
  }

  k1 = resta / 1;
  printf ("Kermata twn  1E: %d\n",k1);
  if (k1>0) {
    resta = resta - 1*k1;
  }

  k50 = resta / 0.5;
  printf ("Kermata twn 50L: %d\n",k50);
  if (k50>0) {
    resta = resta - 0.5*k50;
  }

  k20 = resta / 0.2;
  printf ("Kermata twn 20L: %d\n",k20);
  if (k20>0) {
    resta = resta - 0.2*k20;
  }

  // diorthosi gia periptosh pou xanetai h akribeia
  resta = resta + 0.01;

  k10 = (resta) / 0.1;
  printf ("Kermata twn 10L: %d\n",k10);
  if (k10>0) {
    resta = resta - 0.1*k10;
  }

  //printf("Epalitheysi Resta: %.2f\n", 2*k2+1*k1+0.5*k50+0.2*k20+0.1*k10);

  return 0;
}
