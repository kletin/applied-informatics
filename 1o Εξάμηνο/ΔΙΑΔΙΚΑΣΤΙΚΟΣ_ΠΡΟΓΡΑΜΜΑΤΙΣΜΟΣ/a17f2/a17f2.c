/* File: a17f2.c
* --------------
* askhsh 17 fylladio 2
*/

#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

int main()
{
    int theseis, epivates;
    double orio50, orio30;

    printf("Dwse theseis: ");
    theseis = GetInteger ();
    printf("Dwse epivates: ");
    epivates = GetInteger ();

    orio50 =  theseis * (50.0 / 100.0);
    orio30 = theseis * (30.0 / 100.0);

    if (epivates > orio50 ) {
        printf ("kerdos");
    }
    else if ( epivates < orio30 ) {
         printf ("zimia");
    }
    else
        printf ("kostos");

    return 0;


}
