#include <stdio.h>

#include "genlib.h"
#include "simpio.h"


// returns :
// 1: number is > 1
// 0: number is 0
int decompose(int N,int *digits_total,double *digits_average,int *digit_max)
{
    int digit;
    int number_of_digits=0;
    double sum=0.0;

    // set default values for case N=0
    *digit_max=0;
    *digits_average=0;
    *digits_total=1;

    // case N=0
    if (N==0)
        return 0;

    // case N>0
    while (N > 0) {
        digit = N % 10;
        number_of_digits++;
        N = N / 10;
        if (digit > *digit_max) {
            *digit_max = digit;
        }
        sum = sum + digit;
    }
    *digits_total = number_of_digits;
    *digits_average = sum / number_of_digits;

    return 1;
}

int main()
{
  int Num;
  int total=0,max=0;
  double average=0.0;

  printf("Please insert non-negative number: ");
  scanf("%d",&Num);

  decompose(Num,&total,&average,&max);
  printf("Digits: %d\n",total);
  printf("Average: %.3f\n",average);
  printf("Max: %d\n",max);

    return 0;
}


