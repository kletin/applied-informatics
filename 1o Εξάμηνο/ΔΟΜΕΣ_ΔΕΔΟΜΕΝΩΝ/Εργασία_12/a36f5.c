/*******************************************************************************
 * Filename: a36f5.c
 * data structures (AIC205)
 * ics23088
 ******************************************************************************/
#include <stdio.h>

#define MaxElements 8         // το μέγιστο πλήθος των στοιχείων του σωρού

typedef char HeapElementType;  // ο τύπος δεδομένων των στοιχείων του σωρού
typedef struct {
  HeapElementType key;
  // int Data;                // οποισδήποτε τύπος για τα παρελκόμενα δεδομένα κάθε κόμβου
} HeapNode;

typedef struct {
  int Size;
  HeapNode Element[MaxElements + 1];
} HeapType;

typedef enum {
  FALSE,
  TRUE
} boolean;

void CreateMaxHeap(HeapType *Heap);
boolean FullHeap(HeapType Heap);
void InsertMaxHeap(HeapType *Heap, HeapNode Item);
boolean EmptyHeap(HeapType Heap);
void DeleteMaxHeap(HeapType *Heap, HeapNode *Item);
void PrintHeap(HeapType Heap);

/* new functions -----------------------------------------------------------  */

boolean Search(HeapType Heap, HeapElementType ArgKey, int *left, int *right);

/* -------------------------------------------------------------------------- */

void CreateMaxHeap(HeapType *Heap)
/* Λειτουργία: Δημιουργεί ένα κενό σωρό.
   Επιστρέφει: Ένα κενό σωρό
*/
{
  (*Heap).Size = 0;
}

boolean EmptyHeap(HeapType Heap)
/* Δέχεται:    Ένα σωρό Heap.
   Λειτουργία: Ελέγχει αν ο σωρός είναι κενός.
   Επιστρέφει: TRUE αν ο σωρός είναι κενός, FALSE διαφορετικά
*/
{
  return (Heap.Size == 0);
}

boolean FullHeap(HeapType Heap)
/* Δέχεται:    Ένα σωρό.
   Λειτουργία: Ελέγχει αν ο σωρός είναι γεμάτος.
   Επιστρέφει: TRUE αν ο σωρός είναι γεμάτος, FALSE διαφορετικά
*/
{
  return (Heap.Size == MaxElements);
}

void InsertMaxHeap(HeapType *Heap, HeapNode Item)
/*  Δέχεται:    Ένα σωρό Heap και ένα στοιχείο δεδομένου Item .
    Λειτουργία: Εισάγει το στοιχείο Item στο σωρό, αν ο σωρός δεν είναι γεμάτος.
    Επιστρέφει: Τον τροποποιημένο σωρό.
    Έξοδος:     Μήνυμα γεμάτου σωρού αν ο σωρός είναι γεμάτος
*/
{
  int hole;

  if (!FullHeap(*Heap)) {
    (*Heap).Size++;

    hole = (*Heap).Size;
    while (hole > 1 && Item.key > Heap->Element[hole / 2].key) {
      (*Heap).Element[hole] = (*Heap).Element[hole / 2];
      hole = hole / 2;
    }
    (*Heap).Element[hole] = Item;
  } else
    printf("Full Heap...\n");
}

void DeleteMaxHeap(HeapType *Heap, HeapNode *Item)
/* Δέχεται:    Ένα σωρό Heap.
   Λειτουργία: Ανακτά και διαγράφει το μεγαλύτερο στοιχείο του σωρού.
   Επιστρέφει: Το μεγαλύτερο στοιχείο Item του σωρού και τον τροποποιημένο σωρό
*/
{
  int parent, child;
  HeapNode last;
  boolean done;

  if (!EmptyHeap(*Heap)) {
    done = FALSE;
    *Item = (*Heap).Element[1];
    last = (*Heap).Element[(*Heap).Size];
    (*Heap).Size--;

    parent = 1;
    child = 2;

    while (child <= (*Heap).Size && !done) {
      if (child < (*Heap).Size)
        if ((*Heap).Element[child].key < (*Heap).Element[child + 1].key)
          child++;
      if (last.key >= (*Heap).Element[child].key)
        done = TRUE;
      else {
        (*Heap).Element[parent] = (*Heap).Element[child];
        parent = child;
        child = 2 * child;
      }
    }
    (*Heap).Element[parent] = last;
  } else
    printf("Empty heap...\n");
}

void PrintHeap(HeapType Heap)
{
    int i,l,r,n;
    printf("Size=%d \n",Heap.Size);
     printf("N  L  R\n");
     n=Heap.Size/2;
     for (i=1; i<=n;i++)
     {
         l=2*i;
         r=2*i+1;
         printf("%c, ",Heap.Element[i].key);
         if (l<=Heap.Size)
            printf("%c, ",Heap.Element[l].key);
         else printf(",   ");
         if (r<=Heap.Size)
            printf("%c \n",Heap.Element[r].key);
         else printf("\n");
     }
     printf("Heap array\n");
     for (i=1; i<=Heap.Size;i++)
        printf("%c ",Heap.Element[i].key);
    printf(" \n");
}

/* new function -------------------------------------------------------------  */

boolean Search(HeapType Heap, HeapElementType ArgKey, int *left, int *right) 
{
  *left = -1;
  *right = -1;
  boolean found=FALSE;

  //if (!EmptyHeap(*Heap)) {
  //  return found;
  //}
  int index=1;
  while (!found && index<=Heap.Size) {
    if (Heap.Element[index].key != ArgKey) {
      index++;
    }
    else {
      //printf("index=%d key=%c\n",index,Heap.Element[index].key);
      if (2*index <= Heap.Size) {
        *left=2*index;
      }
      if (2*index+1 <= Heap.Size) {
        *right=2*index+1;
      }
      //printf("left=%d key=%c\n",*left,Heap.Element[*left].key);
      //printf("right=%d key=%c\n",*right,Heap.Element[*right].key);
      found=TRUE;
    }
  }
  return found;
}

/* -------------------------------------------------------------------------- */

int main() {

  HeapType AHeap;
  HeapNode ANode;
  boolean f;
  int l,r;

  CreateMaxHeap(&AHeap);


  for (int i = 1; i <= MaxElements; i++) {
    printf("Enter a letter : ");
    scanf("%c", &ANode.key);getchar();
    InsertMaxHeap(&AHeap, ANode);
  }
  PrintHeap(AHeap);

  for (int i = 1; i <= 4; i++) {
    printf("Enter a letter : ");
    scanf("%c", &ANode.key);getchar();
    f = Search(AHeap,ANode.key,&l,&r);
    if (f==TRUE) {
      printf("L=%d,R=%d\n",l,r);
      if (l <= AHeap.Size) {
        printf("%c",AHeap.Element[l].key);
      }
      printf(" ");
      if (r <= AHeap.Size) {
        printf("%c",AHeap.Element[r].key);
      }
      printf("\n");

    }
    else {
      printf("Not found\n");
    }
  }

  return 0;
}
