#include <stdio.h>

#include "simpio.h"
#include "genlib.h"

// global data

int MAX_NOMISMA = 5;
double isotimies[] = {0,0.89,0.618,1.5465,1.3565,109.22};

// function declaration

int menu();
double convert(int nomisma,double poso);

// function definition

int menu()
{
    printf("-------------------------------\n");
    printf("1. Metatropi se dollaria\n");
    printf("2. Metatropi se lires\n");
    printf("3. Metatropi se fraga Elbetias\n");
    printf("4. Metatropi se dollaria Canada\n");
    printf("5. Metatropi se gien\n");
    printf("6. Exodos\n");
    printf("Epilogi : ");
    return GetInteger();
}

double convert(int nomisma,double poso)
{
    double axia;
    if ((nomisma > 0) && (nomisma <= MAX_NOMISMA)) {
        axia = poso/isotimies[nomisma];
        //printf("DEBUG convert: m=%u isotimia=%f axia=%.2f\n",nomisma,isotimies[nomisma],axia);
    }
    else {
        axia = 0.0;
        printf("Error Lathos Eisodos Nomismatos\n");
    }
    return axia;
}

int main()
{
    int m=1;
    while (m <= MAX_NOMISMA) {
        m = menu();
        if (m <= MAX_NOMISMA) {
            printf("Dwse poso se euro : ");
            double poso = GetReal();

            double axia = convert(m,poso);
            printf("Axia = %.2f\n",axia);
            printf("\n");
        }
    }
    return 0;
}
