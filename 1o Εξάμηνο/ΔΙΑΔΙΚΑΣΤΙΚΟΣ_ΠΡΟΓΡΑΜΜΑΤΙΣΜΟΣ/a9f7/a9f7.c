#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

void DateString(int day, int month, int year, char date[10]);

int main()
{
    int day,month,year;
    char date[10];

    printf("Dwse mera: ");
    day = GetInteger();

    printf("Dwse mhna: ");
    month = GetInteger();

    printf("Dwse xrono: ");
    year = GetInteger();

    DateString( day,  month,  year,  date);
    printf("%s\n",date);
    return 0;
}

void DateString(int day, int month, int year, char date[10])

{
    char monthsTable [][4]= {
        "inv","Jan","Fev","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
    };

    sprintf(date,"%d-%s-%d",day,monthsTable[month],year%100);
    return;
}



