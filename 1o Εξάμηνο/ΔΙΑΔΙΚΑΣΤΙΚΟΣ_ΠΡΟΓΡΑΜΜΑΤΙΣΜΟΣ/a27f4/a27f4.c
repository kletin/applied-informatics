#include "stdio.h"

#include "genlib.h"
#include "simpio.h"

long encode(long N)
{
    long newCode;
    newCode =  100*N + (98 - (N*100) % 97) % 97;
    return newCode;

}

bool check (long newCode)
{
    bool res = FALSE;
    if ((newCode % 97) == 1)
        res = TRUE;
    return res;
}

int main()
{
    int i;
    long lowerLimit, upperLimit;

    printf("Lower Limit: ");
    lowerLimit=GetLong();
    printf("Upper Limit: ");
    upperLimit=GetLong();

    for (i=lowerLimit; i<=upperLimit; i++) {
        long newCode = encode(i);
        bool isValid = check(newCode);
        printf("Code: %d Encoding: %ld ",i,newCode);
        if (isValid == TRUE)
            printf("isValid: yes\n");
        else
            printf("isValid: no\n");
    }

    return 0;
}
