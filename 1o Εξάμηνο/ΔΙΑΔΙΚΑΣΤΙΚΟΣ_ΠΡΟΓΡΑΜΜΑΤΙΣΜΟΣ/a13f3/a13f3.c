/*File: a13f3.c
* -------------
* askhsh 13 fylladio 3
*/

#include <stdio.h>

#include "simpio.h"
#include "stdlib.h"

int main()
{
    int i,N;
    float sum;
    sum = 0;
    printf ("Dwse orio: ");
    N = GetInteger ();
    for (i=1; i<=N; i++)
    {
        sum = sum + (1.00/i) ;
    }
    printf ("To athroisma einai %.2f\n",sum);
    return 0;
}
