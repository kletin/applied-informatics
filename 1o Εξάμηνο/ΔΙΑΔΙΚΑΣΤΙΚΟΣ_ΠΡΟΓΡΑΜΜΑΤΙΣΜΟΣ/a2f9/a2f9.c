#include <stdio.h>
#include <string.h>
#include "simpio.h"
// #include "genlib.h"

#define FALSE 0
#define TRUE 1

#define M 100

typedef struct
{
    char name [30];
    int apousies;
} studentRec ;

void readInput( FILE* infile, studentRec students[], int* pTotal, int *pApontes);
void writeOutput( FILE* outfile, int size,  studentRec students[], int total );

int main()
{

    char inputfilename[30];
    char outputfilename[30];
    FILE* infile;
    FILE* outfile;
    int totalStudents;
    int apontes;

    studentRec students[M];

    while(TRUE)
    {
        printf("Dwste to onoma gia arxeio eisodou: ");
        gets(inputfilename);

        infile = fopen(inputfilename, "r");

        if(infile  != NULL)
            break;
        printf("Cannot open file %s. Try again.\n", inputfilename);
    }

    printf("Dwste to onoma gia arxeio exodou: ");
    gets(outputfilename);

    outfile = fopen(outputfilename, "w");

    readInput(infile, students, &totalStudents, &apontes);
    writeOutput(outfile, apontes, students, totalStudents );

    fclose(infile);
    fclose(outfile);


    return 0;
}

void readInput( FILE* infile, studentRec students[], int* pTotal, int *pApontes)
{

    int nscan, apousies, line;
    char name[30], comments[68], termch;
    int totalStudents = 0;
    int apontes = 0 ;

    line = 0;

    while (TRUE)
    {
        nscan = fscanf(infile, "%30[^,], %d, %68[^\n]%c", name, &apousies, comments, &termch);

        if ( nscan == EOF)
            break;
        line++;

        if ( nscan != 4 || termch != '\n' )
        {
            printf("Error in line %d. Program trmination\n",line);
            exit(1);
        }

        if(apousies > 100)
        {
            strcpy(students[apontes].name, name);
            students[apontes].apousies = apousies;
            apontes++;

        }
        totalStudents++;

    }

    *pTotal = totalStudents;
    *pApontes = apontes;
}
void writeOutput( FILE* outfile, int size,  studentRec students[], int total )
{
        int i;
        fprintf(outfile, "%-30s%-9s\n", "ONOMATEPWNYMO" , "APOUSIES");

        for(i = 1; i<=39; i++)
            fputc('-', outfile);
        fputc('\n', outfile);

        for(i=0; i<size; i++)
            fprintf(outfile, "%-30s%9d\n", students[i].name, students[i].apousies);

        for(i = 1; i<=39; i++)
            fputc('-', outfile);
        fputc('\n', outfile);

        fprintf(outfile, "%-30s%9d\n", "SYNOLO MATHITWN: " , total);
        fprintf(outfile, "%-30s%9d\n", "SYNOLO APONTWN: " , size);
}



















