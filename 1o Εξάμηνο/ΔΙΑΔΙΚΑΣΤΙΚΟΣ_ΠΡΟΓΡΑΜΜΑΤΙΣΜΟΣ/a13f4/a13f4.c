#include <stdio.h>

#include "simpio.h"
#include "genlib.h"

// function declaration
int Fibonacci (int n);

// function definition
int Fibonacci (int n)
 {
  if ( n == 0 || n == 1)
      return n;
  else
      return Fibonacci( n-1 ) + Fibonacci( n-2 );
 }

/* ---------------------------------------------------- */

int main() {
  int n,a;

  printf ("Dwse to n: ");
  n = GetInteger();

  for (int i=0;i<=n;i++) {
     a = Fibonacci (i);
     printf("%5d\n",a);
  }
  return 0;
}


