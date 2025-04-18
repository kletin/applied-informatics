#include <stdio.h>
#include <stdlib.h>
#include "simpio.h"
#include "genlib.h"

#define M 10
#define N 10

void populate_data(int A[M][N],int R,int C)
{
    int i,j;
    for (i=0; i<R; i++)
    {
        for (j=0; j<C; j++)
        {
            A[i][j] = rand()%100;
        }
    }
}


void print_array(int A[M][N],int R,int C)
{
    int i,j;
    for (i=0; i<R; i++)
    {
        for (j=0; j<C; j++)
        {
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }
}

void change_array(int A[M][N],int R,int C)
{
    int i,j,max;
    for (i=0; i<R; i++)
    {
        max = 0;
        for (j=0; j<C; j++)
        {
            if (A[i][j]>max)
                max = A[i][j];
        }

        for (j=0; A[i][j]<max; j++) {
            A[i][j] = max;
        }
    }
}


int main()
{
    int R,C;
    int A[M][N];
    printf("Dwse ton arithmo twn grammwn: ");
    R = GetInteger();
    printf("Dwse ton arithmo twn sthlwn: ");
    C = GetInteger();

    populate_data(A,R,C);
    printf("ARXIKOS PINAKAS\n");
    print_array(A,R,C);
    change_array(A,R,C);
    printf("ALLAGMENOS PINAKAS\n");
    print_array(A,R,C);


    return 0;
}
