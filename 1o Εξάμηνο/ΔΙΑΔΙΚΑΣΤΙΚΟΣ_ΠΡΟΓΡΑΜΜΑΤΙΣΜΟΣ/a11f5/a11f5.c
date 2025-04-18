#include <simpio.h>
#include "genlib.h"
#include "stdio.h"
#include <math.h>

#define CTS 10
#define S 3

int main (){

   double temper[CTS][S];
   double average[CTS];
   double devnat[CTS][S];
   double mdeviation[CTS];

    double natavg;
    int i,j;

    //Ανάγνωση θερμοκρασιών από τον χρήστη
   for(i=0; i<CTS; i++) {
      for(j=0; j<S; j++) {
          printf("Temp of City %d During %d 8-hour period: ",i,j);
          temper[i][j] = GetReal();
      }
   }


   //Υπολογισμός εθνικού μέσου όρου
    natavg = 0;
    for(i=0; i<CTS; i++)
        for(j=0; j<S; j++)
            natavg += temper[i][j];

    natavg = natavg/(CTS*S);

   //Υπολογισμός μέσης θερμοκρασίας κάθε πόλης
    for(i=0; i<CTS; i++) {
      average[i] = 0;
      for(j=0; j<S; j++)
         average[i] += temper[i][j];
      average[i] = average[i] / S;
    }

   //Υπολογισμός αποκλίσεων από τον εθνικό μέσο όρο
    for(i=0; i<CTS; i++)
        for(j=0; j<S; j++)
            devnat[i][j] = fabs(temper[i][j] - natavg);

    //Υπολογισμός μέγιστης απόκλισης κάθε πόλης
    for(i=0; i<CTS; i++) {
            mdeviation[i] = devnat[i][0];
            for(j=0; j<S; j++)
                if(devnat[i][j] > mdeviation[i])
                   mdeviation[i] = devnat[i][j];
    }

   //Εκτυπώσεις
    printf("%.1f\n", natavg);
    for(i=0; i<CTS; i++) {
            printf("City %d  %.1f  %.1f\n",i, average[i], mdeviation[i]);
    }

    return 0;
}
