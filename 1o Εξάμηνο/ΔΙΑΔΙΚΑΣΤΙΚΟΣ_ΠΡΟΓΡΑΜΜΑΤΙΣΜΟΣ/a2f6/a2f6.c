#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

int readData(int Table[])
{
    int i,x;
    i = 0;
    printf("? ");
    x = GetInteger();
    while ( x != -1 ) {
        Table[i] = x;
        printf("? ");
        x = GetInteger();
        i++;
    }
    return i;
}

void findMinMax(int Table[],int counter,int *min, int *max)
{
    int i;
    int tmax = -1;
    int tmin = 2147483647;
    for (i = 0 ; i < counter; i++) {
        if (Table[i]<tmin) {
            tmin = Table[i];
        }
        if (Table[i]>tmax) {
            tmax = Table[i];
        }
    }
    *max = tmax;
    *min = tmin;
}



int main()
{
    int Table[100];
    int counter;
    int min,max;

    printf("Enter the elements of the array, one per line.\n");
    printf("Use -1 to signal the end of the list.\n");
    counter = readData(Table);

    findMinMax(Table,counter,&min,&max);
    printf("The range of values is %d-%d\n",min,max);
    return 0;
}
