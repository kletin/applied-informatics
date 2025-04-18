
/* File: a7f1.c
* --------------
* askhsh 7 fylladio 1
*/

#include <stdio.h>

#include "simpio.h"
#include "genlib.h"

int main()
{
    // Δήλωση σταθερών
    double perFPA1 = 0.04;
    double perFPA2 = 0.08;
    double perFPA3 = 0.18;

    // Δήλωση μεταβλητών
    long proceeds1, proceeds2, proceeds3;
    double totalFPA;

    //Eισαγωγή δεδομένων
    printf ("Dwse tis synolikes eispraxeis gia FPA 0.04:" );
    proceeds1 = GetLong();
    printf ("Dwse tis synolikes eispraxeis gia FPA 0.08:" );
    proceeds2 = GetLong();
    printf ("Dwse tis synolikes eispraxeis gia FPA 0.18:" );
    proceeds3 = GetLong();

    totalFPA = (perFPA1 * proceeds1) + (perFPA2 * proceeds2) + (perFPA3 * proceeds3);
    printf ("To synoliko FPA einai %g\n" , totalFPA);

    return 0;
}
