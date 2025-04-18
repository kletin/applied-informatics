/*File: a10f2.c
* -------------
* askhsh 10 fylladio 2
*/

#include <stdio.h>

#include <simpio.h>

int main()
{
    long parousaEndeijh, prohgoumenhEndeijh, katanalwsh, ajiaReumatos;
    int code, pagio;
    double poso, FPA, synolikoPoso;
    double FPAvalue = 0.18;

    printf ("Dwse ton kwdiko kathgorias timologiou: ") ;
    code = GetInteger ();
    printf ("Dwse thn parousa endeijh metrhth:");
    parousaEndeijh = GetLong ();
    printf ("Dwse thn prohgoumenh endeixh toy metrhth:");
    prohgoumenhEndeijh = GetLong ();

    katanalwsh = parousaEndeijh - prohgoumenhEndeijh;
    printf ("Katanalwsh reumatos se monades:%ld\n",katanalwsh);

    if ((katanalwsh >= 1 ) && (katanalwsh <= 200)) {
        ajiaReumatos = katanalwsh * 12;
    }
    else if (katanalwsh <= 500) {
        ajiaReumatos = 200 * 12 + (( katanalwsh - 200) * 15 );
    }
    else if (katanalwsh <= 1500) {
        ajiaReumatos = 200 * 12 + 300 * 15 + ((katanalwsh - 500) * 15 );
    }
    else {
        ajiaReumatos = 200 * 12 + 300 * 15 + 1000 * 20 + ((katanalwsh - 1500) * 15 );
    }

    printf("Ajia reumatos(cent): %ld\n", ajiaReumatos);

    if ((code == 1) || (code==2 )) {
        pagio = 20;
    }
    else {
        pagio = 100;
    }
    printf ("Pagio (eyro): %d\n", pagio);
    poso = ajiaReumatos/100 + pagio;

    FPA = poso * FPAvalue;
    synolikoPoso = poso + FPA;

    printf ("Synoliko poso plhrwmhs (euro): %.2f\n", synolikoPoso);

    return 0;
}
