/*File: a5f3.c
* -------------
* askhsh 5 fylladio 3
*/

#include <stdio.h>

#include "simpio.h"
#include "stdlib.h"


int main()
{
    int plhthos, code, fyllo, baros, ypsos, hlikia, maxKwdikos,max, maxBaros,maxYpsos,maxHlikia,i,maxFyllo;

    printf ("Dwse to plhthos: ");
    plhthos = GetInteger();
    max = -1;
    for (i=1; i<=plhthos; i++) {

        printf ("Dwse ton kwdiko: ");
        code = GetInteger();
        printf ("Dwse to fyllo: ");
        fyllo = GetInteger();
        printf  ("Dwse to baros: ");
        baros = GetInteger();
        printf ("Dwse to ypsos: ");
        ypsos = GetInteger();
        printf ("Dwse thn hlikia: ");
        hlikia = GetInteger();
        if (fyllo==0  && ypsos>max) {
            max = ypsos;
            maxKwdikos = code;
            maxBaros = baros;
            maxYpsos = ypsos;
            maxHlikia = hlikia;
            maxFyllo = fyllo;
            }
    }
    printf ("%d %d %d %d %d", maxKwdikos, maxFyllo, maxBaros, maxYpsos, maxHlikia );


        return 0;
}
