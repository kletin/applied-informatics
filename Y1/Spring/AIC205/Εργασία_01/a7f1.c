/*******************************************************************************
* Filename: a7f1.c
* Δομές Δεδομένων (AIC205)
* ΜΑΡΙΑ ΑΙΚΑΤΕΡΙΝΗ ΣΑΤΡΑΤΖΕΜΗ, ΓΕΩΡΓΙΑ ΚΟΛΩΝΙΑΡΗ, ΑΛΕΞΑΝΔΡΟΣ ΚΑΡΑΚΑΣΙΔΗΣ
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 5         //μέγιστο πλήθος στοιχείων συνόλου

typedef enum
{
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Katholiko(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean KenoSynolo(typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);


/* calculates 2^N */
int power2N(int N);

void displayset(typos_synolou set);

void createPowerSet(int N, typos_synolou dynamosynolo[]);

int main()
{
    int powerSetsize = power2N(megisto_plithos);
    typos_synolou PS[powerSetsize];
    int i;

    createPowerSet(megisto_plithos,PS);

    printf("TO DYNAMOSYNOLO GIA N=%d\n",megisto_plithos);
    for (i=0;i<powerSetsize;i++) 
        displayset(PS[i]);

    return 0;
}

/* calculates 2^N */

int power2N(int N)
{
    int i;
    int res=1;
    for (i=1;i<=N;i++) {
        res = 2*res;
    } 
    return res;
}

void displayset(typos_synolou set)
{
    stoixeio_synolou i;

    for (i=0; i < megisto_plithos; i++) {
        if(Melos(i,set))
            printf(" %d",i+1);
    }
    printf("\n");
}

void createPowerSet(int N,typos_synolou dynamosynolo[])
{
    int powerSetsize = power2N(N);
    int counter, j;

    for(counter = 0;counter<powerSetsize;counter++) {
        Dimiourgia(dynamosynolo[counter]);
        for(j=0;j<N;j++) {
            if(counter & (1<<j)) {
                Eisagogi(j,dynamosynolo[counter]);
            }
        }
    }
}

    void Dimiourgia(typos_synolou synolo)
    /* Λειτουργία: Δημιουργεί ένα σύνολο χωρίς στοιχεία, δηλαδή το κενό σύνολο.
       Επιστρέφει: Το κενό σύνολο
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            synolo[i] = FALSE;
    }

    void Katholiko(typos_synolou synolo)
    /* Δέχεται:     Ένα σύνολο.
       Λειτουργία: Δημιουργεί ένα σύνολο με όλα τα στοιχεία παρόντα,
                    έτσι όπως ορίστηκε στο τμήμα δηλώσεων του προγράμματος.
       Επιστρέφει: Το καθολικό σύνολο που δημιουργήθηκε
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            synolo[i] = TRUE;
    }

    void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
       Λειτουργία: Εισάγει το στοιχείο στο σύνολο.
       Επιστρέφει: Το τροποποιημένο σύνολο
    */
    {
        synolo[stoixeio] = TRUE;
    }

    void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* Δέχεται:     Ένα σύνολο και ένα στοιχείο.
       Λειτουργία:  Διαγράφει το στοιχείο από το σύνολο.
       Επιστρέφει:  Το τροποποιημένο σύνολο
    */
    {
        synolo[stoixeio] = FALSE;
    }

    boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
       Λειτουργία: Ελέγχει αν το στοιχείο είναι μέλος του συνόλου.
       Επιστρέφει: Επιστρέφει TRUE αν το στοιχείο είναι μέλος του και FALSE διαφορετικά
    */
    {
        return synolo[stoixeio];
    }

    boolean KenoSynolo(typos_synolou synolo)
    /*
    Δέχεται: Ένα σύνολο.
     Λειτουργία: Ελέγχει αν το σύνολο είναι κενό.
     Επιστρέφει: Επιστρέφει TRUE αν το σύνολο είναι κενό και FALSE διαφορετικά
    */
    {
        stoixeio_synolou i;
        boolean keno;

        keno=TRUE;
        i = 0;

        while (i < megisto_plithos  && keno) {
            if (Melos(i, synolo))
                keno = FALSE;
            else
                i++;
        }
        return keno;
    }

    boolean IsaSynola(typos_synolou s1, typos_synolou s2)
    /* Δέχεται:     Δύο σύνολα s1 και s2.
       Λειτουργία: Ελέγχει αν τα δύο σύνολα είναι ίσα.
       Επιστρέφει: Επιστρέφει TRUE αν τα δύο σύνολα έχουν τα ίδια στοιχεία και FALSE διαφορετικά
    */
    {
        stoixeio_synolou i;
        boolean isa;

        isa = TRUE;
        i=0;
        while (i < megisto_plithos && isa)
            if (Melos(i,s1) != Melos(i,s2))
                isa = FALSE;
            else
                i++;
        return isa;
    }

    boolean Yposynolo(typos_synolou s1, typos_synolou s2)
    /* Δέχεται:     Δύο σύνολα s1 και s2.
       Λειτουργία: Ελέγχει αν το σύνολο s1 είναι υποσύνολο του s2.
       Επιστρέφει: Επιστρέφει true αν το σύνολο s1 είναι ένα υποσύνολο του s2,
                    δηλαδή αν κάθε στοιχείο του s1 είναι και στοιχείο του s2
    */
    {
        stoixeio_synolou i;
        boolean yposyn;

        yposyn = TRUE;
        i=0;
        while (i < megisto_plithos && yposyn)
            if (Melos(i, s1) && !Melos(i, s2))
                yposyn = FALSE;
            else
                i++;
        return yposyn;
    }

    void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi)
    /* Δέχεται:     Δύο σύνολα s1 και s2.
       Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν ή στο s1 ή
                    στο s2 ή και στα δύο σύνολα.
       Επιστρέφει: Επιστρέφει το σύνολο enosi που προκύπτει από την ένωση των συνόλων s1 και s2
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            enosi[i] = Melos(i, s1) || Melos(i, s2);
    }

    void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
    /* Δέχεται:     Δύο σύνολα s1 και s2.
       Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν και στα δύο σύνολα s1 και s2.
       Επιστρέφει: Επιστρέφει το σύνολο tomi που προκύπτει από την τομή των συνόλων s1 και s2
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            tomi[i] = Melos(i, s1) && Melos(i, s2);
    }

    void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
    /* Δέχεται: Δύο σύνολα s1 και s2.
     Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν στο σύνολο s1 και δεν ανήκουν στο s2.
     Επιστρέφει: Επιστρέφει το σύνολο diafora που προκύπτει από την διαφορά των συνόλων s1-s2.
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            diafora[i] = Melos(i, s1) && (!Melos(i, s2));
    };


