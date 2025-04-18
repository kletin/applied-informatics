#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

int exp10(int x)
{
    int i;
    int res=10;
    if (x==0) {
        return 1;
    }
    for (i=1;i<x;i++) {
        res=res*10;
    }
    return res;
}

int main()
{
    int start,pos,x,x0,L;
    char y,str[80];
    int digits = 0;

    int y1,d1;

    printf("Dwse thetiko akeraio: ");
    x = GetInteger();
    printf("Dwse mhkos: ");
    L = GetInteger();

    x0 = x;
    while (x0>0) {
        x0 = x0 /10;
        digits++;
    }

        if (L>digits) {
            start = L - digits;
            pos = 0;
            while (pos<start){
                str[pos]='0';
                pos++;
            }
            pos=0;
             while (pos<L) {
                d1 = exp10(digits - (pos+1));
                y1 = x / d1;
                x = x % d1;
                y = y1 + '0';
                str[pos+start] = y;
                pos++;
            }
            str[pos] = '\0';

        }


         else {
            pos = 0;
            while (pos<digits) {
                d1 = exp10(digits - (pos+1));
                y1 = x / d1;
                x = x % d1;
                y = y1 + '0';
                str[pos] = y;
                pos++;
            }
            str[pos] = '\0';
        }
            printf("%s\n",str);

        return 0;
    }
