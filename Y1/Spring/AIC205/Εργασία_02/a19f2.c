#include <stdio.h>
#define StackLimit 8   // το όριο μεγέθους της στοίβας, ενδεικτικά ίσο με 50


typedef int StackElementType;   // ο τύπος των στοιχείων  της στοίβας
//ενδεικτικά τύπος int
typedef struct
{
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum
{
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void CreateStack(StackType *Stack)
/* Λειτουργία: Δημιουργεί μια κενή στοίβα.
   Επιστρέφει: Κενή Στοίβα.*
*/
{
    Stack -> Top = -1;
    // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι κενή.
   Επιστρέφει: True αν η Stack είναι κενή, False διαφορετικά
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι γεμάτη.
   Επιστρέφει: True αν η Stack είναι γεμάτη, False διαφορετικά
*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* Δέχεται: Μια στοίβα Stack και ένα στοιχείο Item.
   Λειτουργία: Εισάγει το στοιχείο Item στην στοίβα Stack αν η Stack δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη Stack.
   Έξοδος: Μήνυμα γεμάτης στοίβας, αν η στοίβα Stack είναι γεμάτη
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Διαγράφει το στοιχείο Item από την κορυφή της Στοίβας αν η Στοίβα δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη Stack.
   Έξοδος:  Μήνυμα κενής στοίβας αν η Stack είναι κενή
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...\n");
}

void TraverseStack(StackType Stack)
{
    int i;
    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}



StackElementType minElement(StackType *Stack);
StackElementType maxElement(StackType *Stack);

int main()
{


    StackType S;
    StackElementType item;

    int i;

    CreateStack(&S);
    for(i=0; i<StackLimit; i++) {
        scanf("%d",&item);
        Push(&S,item);
    }
    TraverseStack(S);



    StackElementType min1 = minElement(&S);
    StackElementType max1 = maxElement(&S);

    printf("Min: %d\n",min1);
    printf("Max: %d\n",max1);

    TraverseStack(S);

    return 0;


}


StackElementType minElement(StackType *Stack)
{
    /*Υπόδειξη: Χρησιμοποιείστε μία άλλη βοηθητική Στοίβα*/
    StackElementType min, item;
    StackType tempS;

    CreateStack(&tempS);

    //Pop(&(*Stack),(&min);
    Pop(&(*Stack),&min);

    Push(&tempS, min);
    //Αδειάζω τη στοίβα Stack στη στοίβα tempS και αποθηκεύω το μικρότερο στοιχείο
    while(!EmptyStack(*Stack)) {
        Pop(Stack, &item);
        Push(&tempS, item);


        if(min>item)
            min = item;
    }
//Αδειάζω την tempS και εισάγω στην Stack μόνο τα στοιχεία που δεν είναι ίσα με min
    while(!EmptyStack(tempS)) {
        Pop(&tempS, &item);
        if (item != min)
            Push(Stack, item);
    }
    return min;
}
StackElementType maxElement(StackType *Stack)
{
    StackElementType max, item;
    StackType tempS;
    CreateStack(&tempS);

    Pop(&(*Stack),&max);

    Push(&tempS, max);


//Αδειάζω τη στοίβα Stack στη στοίβα tempS και αποθηκεύω το μεγαλύτερο στοιχείο
    while(!EmptyStack(*Stack)){

        Pop(Stack, &item);
        Push(&tempS, item);
        if(max<item)
            max = item;
    }

//Αδειάζω την tempS και εισάγω στην Stack μόνο τα στοιχεία που δεν είναι ίσα με max
          while(!EmptyStack(tempS)){
            Pop(&tempS,&item);
            if (item != max)
                Push(Stack,item);
          }
        return max;

    }






