/* File: a5f1.c
* -------------
* Askhsh 5 fylladio 1
*/

#include <stdio.h>

#include <simpio.h>
#include <genlib.h>

int main () {

    // Δήλωση μεταβλητών
    int hours;
    long hourlySalary;
    double checkOffPercentage, checkOff, grossEarnings, earnings;

    // Εισαγωγή δεδομένων

    printf ("Dwse ton arithmo twn wrwn: ");
    hours = GetInteger ();
    printf ("Dwse thn wriaia antimisthia: ");
    hourlySalary = GetLong ();
    printf ("Dwse to pososto twn krathsewn: ");
    checkOffPercentage = GetReal ();

    earnings = hours * hourlySalary;
    checkOff =  earnings * checkOffPercentage;
    grossEarnings = earnings + checkOff;

    printf ("Oi akatharistes apodoxes einai: %g\n", grossEarnings );
    printf ("Oi krathseis einai: %g\n", checkOff );
    printf ("Oi kathares apodoxes einai: %g\n", earnings );

    return 0;
}








