#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

#define MAX_CITIES 4

char cities[][16] = {
    "",
    "Thes/niki",
    "Athens",
    "Volos",
    "Hrakleio"
};

typedef struct
{
    int code;
    char names[16];
    long sells;
    int area;
} Sellers;

int getData(Sellers pwlhtes[],int count);
long totalSells(Sellers pwlhtes[],int count,int area);

int main()
{
    int i,data,count;
    long total[3];
    Sellers pwlhtes[20];
    long grandTotal = 0;


    printf("Dwse to plhtos twn pwlhtwn? ");
    count = GetInteger();
    data = getData( pwlhtes, count);

    for(i=0; i<count; i++) {
        total[i] = 0;
    }
    // print report
    printf("%11s %13s","PERIOXH","SYN.PWLHSEWN\n");
    printf("------------------------------------------------\n");
    for(i=1; i<=MAX_CITIES; i++) {
        long sum = totalSells( pwlhtes,count,i);
        grandTotal = grandTotal + sum;
        printf("%11s%13ld\n",cities[i], sum);
    }
    printf("------------------------------------------------\n");
    printf("%11s%13ld\n", "SYNOLO:", grandTotal);
    return 0;

}
int getData(Sellers pwlhtes[],int count)
{
    int i;
    for(i=0; i<count; i++) {
        printf("Kwdikos? ");
        pwlhtes[i].code = GetInteger();
        printf("Onomatepwnymo? ");
        gets(pwlhtes[i].names);
        printf("Poso Pwlhsewn? ");
        pwlhtes[i].sells = GetInteger();
        printf("Kwdikos (1= Thes/niki, 2= Athens, 3= Volos, 4= Hrakleio)? ");
        pwlhtes[i].area = GetInteger();
    }
    return count;
}

long totalSells(Sellers pwlhtes[],int count,int area)
{
    int i;
    long sum = 0;
    for(i=0; i<count; i++) {
        if (pwlhtes[i].area == area) {
            sum = sum + pwlhtes[i].sells;
        }
    }
    return sum;
}










