#include <stdio.h>

#include "genlib.h"
#include "simpio.h"

bool Valid_Time (int hours, int minutes,int seconds)
{
    bool res=FALSE;
    if (hours>=0 && hours<=23)
        if (minutes>=0 && minutes<=59)
            if (seconds>=0 && seconds<=59) {
                res=TRUE;
            }
    return res;
}




int main()
{
    int hours,minutes,seconds;

    printf ("Dwse tis ores: ");
    hours = GetInteger();
    printf ("Dwse ta lepta: ");
    minutes = GetInteger();
    printf ("Dwse ta defterolepta: ");
    seconds = GetInteger();
    bool valid = Valid_Time(hours,minutes,seconds);
    if (valid == TRUE) {
       printf ("Valid: yes");
    }
    else {
       printf ("Valid: no");
    }

    return 0;
}
