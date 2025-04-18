/*File: a18f3.c
* -------------
* askhsh 18 fylladio 3
*/

#include <stdio.h>

#include "simpio.h"
#include "stdlib.h"

int main()
{
   int synolikoPoso, poso, max, min, plhthos;

   plhthos = 0;
   synolikoPoso = 0;
   max = -1;
   min = 99999999;
   while (synolikoPoso < 100000)
   {
     printf ("Dose poso: ");
     poso = GetInteger();
     synolikoPoso = synolikoPoso + poso;
     plhthos = plhthos + 1;
     if (poso > max)
        max = poso;
     if (poso < min)
        min = poso;
   }

   printf ("Plithos atomwn: %d\n",plhthos);
   printf ("Synoliko poso: %d\n",synolikoPoso);
   printf ("Megalytero poso: %d  ",max);
   printf ("Mikrotero poso: %d\n",min);




    return 0;
}
