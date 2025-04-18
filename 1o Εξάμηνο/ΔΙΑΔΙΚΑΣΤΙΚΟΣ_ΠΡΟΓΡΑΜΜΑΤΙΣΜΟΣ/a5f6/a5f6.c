#include <stdio.h>

#include "simpio.h"
#include "genlib.h"

void inputArray(int Table[], int n)
{
    int i;
    for (i = 0; i<n; i++) {
        printf("Give element [%d] : ",i);
        Table[i] = GetInteger();
    }
}

void inputNumbers( int *A,int *B)
{

    printf("Give Α: ");
    *A = GetInteger();
    printf("Give B: ");
    *B = GetInteger();
}

void performCalculations(int A, int B,int Table[],int n, int *counter1, int *counter2, int *counter3)
{
    int counter_1 = 0;
    int counter_2 = 0;
    int counter_3 = 0;
    int i;

    for (i=0; i<n; i++) {
        if (Table[i]<=A)
            counter_1++;
        if (Table[i]>=B)
            counter_2++;
        if (Table[i]>A && Table[i]<B)
            counter_3++;

    }
    *counter1 = counter_1;
    *counter2 = counter_2;
    *counter3 = counter_3;

    return;
}

void ShowResults(int Table[], int n, int A, int B, int counter1, int counter2, int counter3)
{
    int i;

    printf("\n");
    printf("----The numbers of the array-----\n");
    for (i = 0; i < n; i++ ) {
        printf("%d ", Table[i]);
    }
    printf("\n");
    printf("A = %d \n", A);
    printf("Β = %d \n", B);
    printf("Numbers smaller or equal to A: %d \n",counter1);
    printf("Numbers bigger or equal to B: %d \n",counter2);
    printf("Numbers bigger than A and smaller than B: %d\n",counter3);

}

int main()
{
    int Table[100],n,counter1,counter2,counter3;
    int A,B;

    printf("Give n: ") ;
    n = GetInteger();

    inputArray(Table,n);

    inputNumbers(&A,&B);

    performCalculations( A, B, Table, n, &counter1, &counter2, &counter3);

    ShowResults(Table,n, A, B, counter1,counter2,counter3);

    return 0;

}
