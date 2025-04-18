#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

struct box
{
    int width;
    int height;
    int depth;
    int area;
    int volume;
} ;

struct box getData();
void calc_box_area(struct box *a_box);
void calc_box_volume(struct box *a_box);
int main()
{
    struct box measures;
    measures = getData();
    calc_box_area(&measures);
    calc_box_volume(&measures);


    printf("To emvadon tou koutiou einai %d cm2 \n",measures.area);
    printf("O ogos tou koutiou einai %d cm3\n", measures.volume);
    return 0;
}

struct box getData()
{
    struct box measures;

    printf("Dose to mikos tou koutiou se cm: ");
    measures.width = GetInteger();
    printf("Dose to ypsos tou koutiou se cm: ");
    measures.height = GetInteger();
    printf("Dose to vathos tou koutiou se cm: ");
    measures.depth = GetInteger();

    return measures;
}

void calc_box_area(struct box *a_box)
{
    a_box->area = 2*(a_box->width * a_box->height + a_box->width *a_box->depth +  a_box->height * a_box->depth ) ;
    return ;
}

void calc_box_volume(struct box *a_box)
{
    a_box->volume = a_box->width * a_box->depth * a_box->height;
    return;
}








