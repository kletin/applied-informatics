/*******************************************************************************
* Filename: a3f1.c
* Δομές Δεδομένων (AIC205)
* ΜΑΡΙΑ ΑΙΚΑΤΕΡΙΝΗ ΣΑΤΡΑΤΖΕΜΗ, ΓΕΩΡΓΙΑ ΚΟΛΩΝΙΑΡΗ, ΑΛΕΞΑΝΔΡΟΣ ΚΑΡΑΚΑΣΙΔΗΣ
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 26         //μέγιστο πλήθος στοιχείων συνόλου

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


void displayset(typos_synolou set);

void EmfanisiSynolou(typos_synolou set);

int main()
{
    stoixeio_synolou AnItem,i;
    int choice, s;
    typos_synolou     Kath, S, T, Union, Intersection, Difference;
    char ch;

    Dimiourgia(Kath);
    Katholiko(Kath);
    EmfanisiSynolou(Kath);

    Dimiourgia(S);
    for(i=0; i<4; i++) {
        Eisagogi(i,S);
    }
    EmfanisiSynolou(S);

    Dimiourgia(T);
    for(i=0; i<5; i++) {
        int j=2*i;
        Eisagogi(j,T);
    }
    EmfanisiSynolou(T);


    if (IsaSynola(S,T))
        printf("ISA SYNOLA\n");
    else printf("NOT ISA SYNOLA\n");

    if (Yposynolo(S,T))
        printf("S YPOSYNOLO T");
    else printf("NOT S YPOSYNOLO T\n");

     if (Yposynolo(T,S))
        printf("T YPOSYNOLO S");
    else printf("NOT T YPOSYNOLO S\n");

    Dimiourgia(Union);
    EnosiSynolou(S, T, Union);
    EmfanisiSynolou(Union);

    Dimiourgia(Intersection);
    TomiSynolou(S, T, Intersection);
    EmfanisiSynolou(Intersection);

    Dimiourgia(Difference);
    DiaforaSynolou(S, T, Difference);
    EmfanisiSynolou(Difference);

    return 0;
}

void displayset(typos_synolou set)
{
    stoixeio_synolou i;

    for (i=0; i < megisto_plithos; i++) {
        if(Melos(i,set))
            printf(" %d",i);
    }
    printf("\n");
}

void EmfanisiSynolou(typos_synolou set)
{

    stoixeio_synolou i;
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(i=0; i < megisto_plithos; i++) {
        if(Melos(i,set)) {
            printf("%c ",alphabet[i]);
        }
    }
    printf("\n");
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


