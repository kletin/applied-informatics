/* File: a4f1.c
* --------------
* This program calculates
* the profit of a sell
*/

#include <stdio.h>
#include <simpio.h>
#include <genlib.h>

int main() {

    // Δήλωση μεταβλητών
    int rate;
    long purchaseAmount;
    double profit, saleAmount;

    printf("Dwse thn katharh axia: ");
    purchaseAmount = GetLong ();
    printf ("Dwse to pososto kerdous: ");
    rate = GetInteger();

    profit = purchaseAmount * (rate / 100.0);
    saleAmount = profit + purchaseAmount;

    printf("To kerdos einai %g\n", profit);
    printf("To synoliko poso einai %g\n", saleAmount) ;

    return 0;
}
