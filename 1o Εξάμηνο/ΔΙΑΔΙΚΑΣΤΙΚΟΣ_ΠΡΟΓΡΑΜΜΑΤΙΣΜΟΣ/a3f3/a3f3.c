/*File: a3f3.c
* -------------
* askhsh 3 fylladio 3
*/

#include <stdio.h>

#include "simpio.h"
#include "stdlib.h"


int main()
{
    long kivwtiaEs, kivwtiaEj, sumEj, sumEs, sum, sumApost;

    printf ("Kivwtia eswterikou? ");
    kivwtiaEs = GetLong();

    sumEj = 0;
    sumEs = 0;
    sumApost = 0;

    while (kivwtiaEs != -9999 ) {
        kivwtiaEs = kivwtiaEs * 10;
        sumEs = sumEs + kivwtiaEs;
        printf ("Kivwtia ejwterikou? ");
        kivwtiaEj = GetLong();
        //
        kivwtiaEj = kivwtiaEj * 15;
        sumEj = sumEj + kivwtiaEj;
        sum = kivwtiaEj + kivwtiaEs ;
        sumApost = sumApost + sum;
        printf ("%10ld%10ld%10ld\n", kivwtiaEs, kivwtiaEj, sum );
        //
        printf ("Kivwtia eswterikou ? ");
        kivwtiaEs = GetLong();
    }
    printf ("%10ld%10ld%10ld\n", sumEs, sumEj, sumApost ) ;
    return 0;
}
