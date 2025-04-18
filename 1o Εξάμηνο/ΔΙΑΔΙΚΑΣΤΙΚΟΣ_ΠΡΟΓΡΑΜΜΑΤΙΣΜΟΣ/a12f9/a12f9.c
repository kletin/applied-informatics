#include <stdio.h>
#include "simpio.h"
#include "genlib.h"
#include <string.h>

#define MAX 100

typedef struct
{
    long AFM;
    char name[30];
    long annoualEarnings;

} salaryData;


int readDataFromFile(FILE* infile, salaryData salArray[]);
void writeToFile(FILE* outfile, salaryData salArray[],int size);

int main()
{
    int size;

    FILE* infile;
    FILE* outfile;

    char inputfilename[30];
    char outputfilename[30];

    salaryData salArray[MAX];

    while(TRUE) {
        printf("Dwse onoma arxeiou gia eisodo: ");
        gets(inputfilename);

        infile = fopen(inputfilename, "r");

        if (infile == NULL)
            printf("Cannot open file %s. Please try again",inputfilename);
        else
            break;
    }

    printf("Dwse onoma arxeiou gia eksodo: ");
    gets(outputfilename);

    outfile = fopen(outputfilename, "w");


    size = readDataFromFile( infile,  salArray);
    writeToFile(outfile,  salArray, size);

    fclose(infile);
    fclose(outfile);

    return 0;
}

int readDataFromFile(FILE* infile, salaryData salArray[])
{
    int n = 0;
    int nscan;
    long AFM;
    char name[30];
    long annoualEarnings;

    while(TRUE) {
        nscan = fscanf(infile, "%ld , %30[^,], %ld", &AFM,name, &annoualEarnings);

        if (nscan == EOF)
            break;
        salArray[n].AFM = AFM;
        strcpy(salArray[n].name,name);
        salArray[n].annoualEarnings = annoualEarnings;

        n++;
    }
    return n;


}

void writeToFile(FILE* outfile, salaryData salArray[],int size)
{

    double totalForos = 0;
    int i = 0 ;



    fprintf(outfile,"%-11s%-22s%11s\n","AFM", "ONOMATEPWNYMO", "FOROS");


    for(i=0; i<44; i++) {
        fputc('-',outfile);


    }
    fputc('\n',outfile);


    for(i=0; i<size; i++) {

        long eis;
        double f;
        eis = salArray[i].annoualEarnings;

        if(eis <= 10000 )
            f = eis * 14/100;
        else if ((eis > 10000 ) && (eis <= 23000))
            f =  eis * 19/100;
        else if ((eis > 23000) && (eis <= 55000))
            f =  eis * 23/100;
        else
            f =  eis * 28/100;

        printf("%d %ld %.2f\n", i,eis,f);
        totalForos += f;
        fprintf(outfile,"%-11ld%-22s%11.2f\n",salArray[i].AFM,salArray[i].name,f);

    }

    for (i=0;i<44;i++){
        fputc('-',outfile);
    }
    fputc('\n',outfile);

    fprintf(outfile,"%-14s%30.2f","SYNOLO FOROU", totalForos);



}





