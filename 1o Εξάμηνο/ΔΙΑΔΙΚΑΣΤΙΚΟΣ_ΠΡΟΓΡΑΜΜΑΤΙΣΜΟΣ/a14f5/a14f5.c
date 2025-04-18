#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

// int is 4 bytes = 32 bits
// smallest negative int is -2^31
#define MIN_VALUE (-2147483648)

int dhlwshPlhthous()

{
    int size;
    size = GetInteger();
    return size;

}
void diavasmaPinaka(long a[50],int size)
{
    int i;
    for (i=0; i<size; i++) {
        a[i] = GetLong();
    }

}

void emfanishPinaka(long a[],int size)
{
    int i;
    for (i=0; i<size; i++) {
        printf("%ld ",a[i]);
    }
    printf("\n");

}


int FindMaxsPos(int size, long a[], int index[])
{
    int counter = 0;
    int i,j,max;
    max = MIN_VALUE;
    j = 0;
    index[j] = 0;
    for (i=0; i<size; i++)\
    {
        if (a[i] == max)
        {
            j++;
            index[j] = i;
            counter += 1;

        }
        if (a[i] > max)
        {
            j = 0;
            max = a[i];
            index[j] = i;
            counter = 1;
        }
    }
    return counter;

}

int main()
{
    int i,N;
    int index[50];
    long  a[50];

    printf("Dwse to plhthos twn stoixeiwn: ");
    N =  dhlwshPlhthous();

    diavasmaPinaka(a,N);
    emfanishPinaka(a,N);

    int count = FindMaxsPos(N, a, index);
    printf("maximum %ld \n",a[index[0]]);
    printf("Plithos maximum %d\n",count);
    printf("Positions of maximum ");
    for (i=0; i<count; i++) {
        printf("%d ",index[i]);
    }
    printf("\n");

    return 0;
}

