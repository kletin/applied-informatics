   #include <stdio.h>
#include "simpio.h"
#include "genlib.h"
#include <string.h>


#define ΜΑΧ 100

typedef struct
{
    int number;
    char name [28];
    int points;
} playerInf;

void readFromFile(FILE* infile, playerInf plArray[] , int *pointsTotal, int *players, int *players10);
void writeToFile(FILE* outfile, playerInf plArray[] , int pointsTotal, int players, int players10);

int main()
{
    char inputfilename[30];
    char outputfilename[30];

    FILE* infile;
    FILE* outfile;

    playerInf plArray[ΜΑΧ];

    int pointsTotal=0;
    int players=0;
    int players10=0;


    while (TRUE) {
        printf("Dwse to onoma tou arxeiou gia anoigma ");
        scanf(inputfilename);

        infile = fopen(inputfilename, "r");

        if (infile == NULL) {
            printf("Cannot open file %s. Try again. \n",inputfilename);
        }
        else
            break;
    }

    printf("Dwse to onoma tou arxeiou gia eksodo ");
    gets(outputfilename);
    outfile = fopen(outputfilename, "w");

    readFromFile(infile, plArray, &pointsTotal,&players,&players10);
    writeToFile(outfile, plArray, pointsTotal,players,players10);

    fclose(infile);
    fclose(outfile);

    return 0;
}

void readFromFile(FILE* infile, playerInf plArray[] , int *pointsTotal, int *players, int *players10)
{
    int n=0;
    int number;
    char name[28];
    int points;

    *players=0;
    *pointsTotal = 0;
    *players = 0;


    while (TRUE) {
        int nscan = fscanf(infile, "%d, %28[^,], %d",&number,name,&points);

        if (nscan == EOF)
            break;

        plArray[n].number =  number;
        strcpy(plArray[n].name,name);
        plArray[n].points = points;


        *pointsTotal +=  plArray[n].points;
        if ( plArray[n].points > 10)
            *players10 += 1;
        n++;
    }
    *players = n;
}

void writeToFile(FILE* outfile, playerInf plArray[] , int pointsTotal, int players, int players10)
{


    int i;

    fprintf(outfile, "%-28s%10s\n", "ONOMATEPWNYMO", "PONTOI");

    for(i=1; i<=38; i++) {
        fputc('-',outfile);
    }
    fputc('\n',outfile);

    for(i=0; i<players; i++) {
        fprintf(outfile, "%-28s%10d\n",plArray[i].name,plArray[i].points);
    }

    for(i=1; i<=38; i++) {
        fputc('-',outfile);
    }
    fputc('\n',outfile);

    fprintf(outfile, "%-28s%10d\n","SYNOLO PONTWN: ", pointsTotal);
    fprintf(outfile, "%-28s%10d\n","SYNOLO PAIKTVN >= 10", players10);

}

