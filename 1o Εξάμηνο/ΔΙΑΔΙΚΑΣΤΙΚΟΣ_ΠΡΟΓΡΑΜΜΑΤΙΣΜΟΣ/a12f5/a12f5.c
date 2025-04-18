#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

int main()
  {

   int M,N,i,j;
   double Marks[30][10], avMark[30];

   printf("Dwse ton arithmo twn mathitwn: ");
   M = GetInteger();
   printf("Dwse ton arithmo twn thematwn: ");
   N = GetInteger();
   for (i=0; i<M; i++) {
     for (j=0; j<N; j++) {
          printf("Dwse th bathmologia tou %dou thematos tou %dou mathith: ",(j+1),(i+1) );
          Marks[i][j]=GetReal();
     }
   }

   for (i=0; i<M; i++) {
     double sum = 0;
     for (j=0; j<N; j++) {
        sum += Marks[i][j];
    }
    avMark[i] =  sum / N;
  }

    for (i=0; i<M; i++){
        for (j=0; j<N; j++) {
            printf("%6.1lf", Marks[i][j]);
        }
        printf("%6.1lf\n", avMark[i]);
        // 20 base
        for (j=0; j<N; j++) {
            printf("%6.1lf", Marks[i][j] / 5.0);
        }
        printf("%6.1lf\n", avMark[i] / 5.0);
    }

return 0;
}
