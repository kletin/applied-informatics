#include <stdio.h>

#include "simpio.h"
#include "genlib.h"


// function declaration
int max (int a, int b);
int gr (int a, int b, int c);

// function definition

// return max of two numbers

int max (int a,int b)
{
    if (a>=b) {
        return a;
    }
    else {
        return b;
    }
}

// return max of three numbers using max(a,b)

int gr (int a, int b, int c)
{
    return max(max(a,b),c);
}


int main()
{
    int a,b,c;
    double y;

    printf ("Dwse a: ");
    a = GetInteger();
    printf ("Dwse b: ");
    b = GetInteger();
    printf ("Dwse c: ");
    c = GetInteger();

    y = (2.0*max(a,b)+3*gr(a,b,c))/4.0;

    printf("y = %.2f\n",y);

    return 0;
}
