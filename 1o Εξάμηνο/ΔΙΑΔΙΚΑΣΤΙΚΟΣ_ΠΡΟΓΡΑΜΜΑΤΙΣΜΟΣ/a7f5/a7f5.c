#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

int main()
{
    int M1,N1,M2,N2,i=0,j=0,k;
    long A[50][50],B[50][50];
    long C[50][50],D[50][50],M[50][50];

    printf("Dwse to plhthos twn grammwn m1: ");
    M1=GetInteger();
    printf("Dwse to plhthos twn sthlwvn n1: ");
    N1=GetInteger();
    printf("Dwse to plhthos twn grammwn m2: ");
    M2=GetInteger();
    printf("Dwse to plhthos twn sthlwn  n2: ");
    N2=GetInteger();


    // ΕΙΣΑΓΩΓΗ ΠΙΝΑΚΑ Α
    for (i=0; i<M1; i++)
        for (j=0; j<N1; j++)
            A[i][j] = GetReal();

    // ΕΙΣΑΓΩΓΗ ΠΙΝΑΚΑ Β
    for (i=0; i<M2; i++)
        for (j=0; j<N2; j++)
            B[i][j] = GetReal();



    // ΠΟΛΛΑΠΛΑΣΙΑΣΜΟΣ ΠΙΝΑΚΩΝ
    if ((M1==M2) && (N1==N2))
    {
        for (i=0; i<M1; i++)
        {
            for (j=0; j<N1; j++)
            {
                C[i][j] = A[i][j] + B[i][j];
                printf("%ld ",C[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("ERROR +\n");
    }


    // ΑΦΑΙΡΕΣΗ ΠΙΝΑΚΩΝ

    if ((M1==M2) && (N1==N2))
    {
        for (i=0; i<M2; i++)
        {
            for (j=0; j<N2; j++)
            {
                M[i][j] = A[i][j] - B[i][j];
                printf("%ld ",D[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("ERROR -\n");
    }

    // ΠΟΛΛΑΠΛΑΣΙΑΣΜΟΣ ΠΙΝΑΚΩΝ
    if (N1==M2)
    {
        for (i=0; i<M1; i++)
        {
            for (j=0; j<N2; j++)
            {
                M[i][j] = 0;
                for (k=0; k<N1; k++)
                {
                    M[i][j] += (A[i][k] *B[k][j]);
                }
                printf("%ld ",M[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("ERROR *\n");
    }

    return 0;
}
