// * Filename: a7f1.c
// * Klelia Tintikaki
// * ics23088

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 5         //������� ������ ��������� �������

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
    /* ����������: ���������� ��� ������ ����� ��������, ������ �� ���� ������.
       ����������: �� ���� ������
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            synolo[i] = FALSE;
    }

    void Katholiko(typos_synolou synolo)
    /* �������:     ��� ������.
       ����������: ���������� ��� ������ �� ��� �� �������� �������,
                    ���� ���� �������� ��� ����� �������� ��� ������������.
       ����������: �� �������� ������ ��� �������������
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            synolo[i] = TRUE;
    }

    void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* �������:    ��� ������ ��� ��� ��������.
       ����������: ������� �� �������� ��� ������.
       ����������: �� ������������� ������
    */
    {
        synolo[stoixeio] = TRUE;
    }

    void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* �������:     ��� ������ ��� ��� ��������.
       ����������:  ��������� �� �������� ��� �� ������.
       ����������:  �� ������������� ������
    */
    {
        synolo[stoixeio] = FALSE;
    }

    boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
    /* �������:    ��� ������ ��� ��� ��������.
       ����������: ������� �� �� �������� ����� ����� ��� �������.
       ����������: ���������� TRUE �� �� �������� ����� ����� ��� ��� FALSE �����������
    */
    {
        return synolo[stoixeio];
    }

    boolean KenoSynolo(typos_synolou synolo)
    /*
    �������: ��� ������.
     ����������: ������� �� �� ������ ����� ����.
     ����������: ���������� TRUE �� �� ������ ����� ���� ��� FALSE �����������
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
    /* �������:     ��� ������ s1 ��� s2.
       ����������: ������� �� �� ��� ������ ����� ���.
       ����������: ���������� TRUE �� �� ��� ������ ����� �� ���� �������� ��� FALSE �����������
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
    /* �������:     ��� ������ s1 ��� s2.
       ����������: ������� �� �� ������ s1 ����� ��������� ��� s2.
       ����������: ���������� true �� �� ������ s1 ����� ��� ��������� ��� s2,
                    ������ �� ���� �������� ��� s1 ����� ��� �������� ��� s2
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
    /* �������:     ��� ������ s1 ��� s2.
       ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� � ��� s1 �
                    ��� s2 � ��� ��� ��� ������.
       ����������: ���������� �� ������ enosi ��� ��������� ��� ��� ����� ��� ������� s1 ��� s2
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            enosi[i] = Melos(i, s1) || Melos(i, s2);
    }

    void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
    /* �������:     ��� ������ s1 ��� s2.
       ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� ��� ��� ��� ������ s1 ��� s2.
       ����������: ���������� �� ������ tomi ��� ��������� ��� ��� ���� ��� ������� s1 ��� s2
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            tomi[i] = Melos(i, s1) && Melos(i, s2);
    }

    void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
    /* �������: ��� ������ s1 ��� s2.
     ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� ��� ������ s1 ��� ��� ������� ��� s2.
     ����������: ���������� �� ������ diafora ��� ��������� ��� ��� ������� ��� ������� s1-s2.
    */
    {
        stoixeio_synolou i;

        for (i = 0; i < megisto_plithos; i++)
            diafora[i] = Melos(i, s1) && (!Melos(i, s2));
    };


