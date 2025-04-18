#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

#define N  5

void readData(int TABLE[][4],int i)
{


    printf("Dwse fylo: ");
    TABLE[i][0] = GetInteger();
    printf("Dwse varos: ");
    TABLE[i][1] = GetInteger();
    printf("Dwse ypsos: ");
    TABLE[i][2] = GetInteger();
    printf("Dwse ilikia: ");
    TABLE[i][3] = GetInteger();
    printf("-----\n");
}

void FindMean(int TABLE[][4],int metric,float *maleAverage,float *femaleAverage)
{
    int i;
    int maleSum=0;
    int femaleSum=0;
    float gynaikes = 0;
    float andres = 0;

    for(i=0; i<N; i++) {
        if (TABLE[i][0]==0) {
            maleSum+=TABLE[i][metric];
            andres++;
        } else {
            femaleSum+=TABLE[i][metric];
            gynaikes++;
        }
    }

    *maleAverage =  maleSum / andres;
    *femaleAverage = femaleSum / gynaikes;
}

int main()
{
    int TABLE[N][4],i,j;
    float maleAverage,femaleAverage;


    for (i=0; i<N; i++)
        readData(TABLE,i);

    for (j=1; j<N; j++) {
        FindMean(TABLE,j,&maleAverage,&femaleAverage);
        if (j==1) {
            printf("Mesos oros barous andrwn: %.1f\n",maleAverage);
            printf("Mesos oros barous gynaikwn: %.1f\n\n",femaleAverage);
        }
        if (j==2) {
            printf("Mesos oros ypsous andrwn: %.1f\n",maleAverage);
            printf("Mesos oros ypsous gynaikwn: %.1f\n\n",femaleAverage);
        }

        if (j==3) {
            printf("Mesos oros hlikias andrwn: %.1f\n",maleAverage);
            printf("Mesos oros hlikias gynaikwn: %.1f\n\n",femaleAverage);
        }
    }





    return 0;
}
