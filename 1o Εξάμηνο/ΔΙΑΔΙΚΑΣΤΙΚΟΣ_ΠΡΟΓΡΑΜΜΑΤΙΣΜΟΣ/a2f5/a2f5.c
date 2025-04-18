#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

long TABLE[][4] =
{
    {1,10000,0,0},
    {10001,39000,18,5220},
    {39001,49000,21,7320},
    {49001,59000,24,9720},
    {59001,85000,28,17000},
    {85001,100000,33,21950},
    {100001,120000,38,29550},
    {120001,150000,43,42450},
    {150001,170000,49,52250},
    {170001,4*10e8,50,0}
};


int main()
{

    int M=10,N=4;

    int i,j,row=M-1;
    long eisodhma,pf;


    printf("Dwse to eisodhma: ");
    eisodhma = GetReal();

    printf("%ld Euro\n",eisodhma);
    for (i=0; i<M; i++)
    {
        if ((eisodhma >= TABLE[i][0]) && (eisodhma <= TABLE[i][1]))
        {
            row = i;
            break;

        }
    }

    long P0 = TABLE[row-1][3];
    printf("%ld Euro\n",P0);
    long P1 = TABLE[row-1][1];
    long P2 = ((eisodhma - P1)*TABLE[row][2]/100);
    printf("%ld Euro\n",((eisodhma - P1)*TABLE[row][2]/100));
    long P3 =  P0 + P2;
    printf("%ld Euro\n",P3);









    return 0;
}
