/* File: a6f1.c
* --------------
* askhsh 6 fylladio 1
*/

#include <stdio.h>

#include "simpio.h"
#include "genlib.h"

int main()
{
    // Δήλωση μεταβλητών
    int workingDays;
    long dailySalary;
    double gift, giftPercentage;
    // Εισαγωγή δεδομένων
    printf (" Dwse tis hmeres ergasias tou etous: ");
    workingDays = GetInteger ();
    printf (" Dwse thn hmerisia amoivh: ");
    dailySalary = GetLong ();
    printf (" Dwse to pososto dwroy: ");
    giftPercentage = GetReal ();

    gift = workingDays * dailySalary * giftPercentage;

    printf("To dwro einai %g\n", gift);

    return 0;
}
