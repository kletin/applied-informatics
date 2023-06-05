/*******************************************************************************
* Filename: a2tf4.c
* Δομές Δεδομένων (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int ListElementType;           /* ο τύπος των στοιχείων της συνδεδεμένης λίστας
                                        ενδεικτικά τύπου int */
typedef struct ListNode *ListPointer;   //ο τύπος των δεικτών για τους κόμβους
typedef struct ListNode
{
  ListElementType Data;
  ListPointer Next;
} ListNode;

typedef enum
{
  FALSE, TRUE
} boolean;


void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);

void PrintList(ListPointer List);
void difference_list(ListPointer AList,ListPointer BList,ListPointer *CList);

/* ---------------------------------------------------------------------- */

void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
  Επιστρέφει:  Τον μηδενικό δείκτη List
*/
{
  *List = NULL;
}

boolean EmptyList(ListPointer List)
/* Δέχεται:   Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
  Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
  Επιστρέφει: True αν η λίστα είναι κενή και false διαφορετικά
*/
{
  return (List == NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο,
                ένα στοιχείο δεδομένων Item και έναν δείκτη PredPtr.
   Λειτουργία: Εισάγει έναν κόμβο, που περιέχει το Item, στην συνδεδεμένη λίστα
                μετά από τον κόμβο που δεικτοδοτείται από τον PredPtr
                ή στην αρχή  της συνδεδεμένης λίστας,
                αν ο PredPtr είναι μηδενικός(NULL).
  Επιστρέφει:  Την τροποποιημένη συνδεδεμένη λίστα με τον πρώτο κόμβο της
                να δεικτοδοτείται από τον List.
*/
{
  ListPointer TempPtr;

  TempPtr = (ListPointer) malloc(sizeof(struct ListNode));
  TempPtr->Data = Item;
  if (PredPtr == NULL) {
    TempPtr->Next = *List;
    *List = TempPtr;
  } else {
    TempPtr->Next = PredPtr->Next;
    PredPtr->Next = TempPtr;
  }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο της
                 και έναν δείκτη PredPtr.
   Λειτουργία: Διαγράφει από τη συνδεδεμένη λίστα τον κόμβο που έχει
                για προηγούμενό του αυτόν στον οποίο δείχνει ο PredPtr
                ή διαγράφει τον πρώτο κόμβο, αν ο PredPtr είναι μηδενικός,
                εκτός και αν η λίστα είναι κενή.
   Επιστρέφει: Την τροποποιημένη συνδεδεμένη λίστα με τον πρώτο κόμβο
                να δεικτοδοτείται από τον List.
   Έξοδος:     Ένα μήνυμα κενής λίστας αν η συνδεδεμένη λίστα ήταν κενή .
*/
{
  ListPointer TempPtr;

  if (EmptyList(*List))
    printf("EMPTY LIST\n");
  else {
    if (PredPtr == NULL) {
      TempPtr = *List;
      *List = TempPtr->Next;
    } else {
      TempPtr = PredPtr->Next;
      PredPtr->Next = TempPtr->Next;
    }
    free(TempPtr);
  }
}

void LinkedTraverse(ListPointer List)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
   Λειτουργία: Διασχίζει τη συνδεδεμένη λίστα και
                επεξεργάζεται κάθε δεδομένο ακριβώς μια φορά.
   Επιστρέφει: Εξαρτάται από το είδος της επεξεργασίας.
*/
{
  ListPointer CurrPtr;

  if (EmptyList(List))
    printf("EMPTY LIST\n");
  else {
    CurrPtr = List;
    printf("%-16s\t%-4s\t%-16s\n", "CurrPtr", "Data", "Next");
    while (CurrPtr != NULL) {
      printf("%p\t%d\t%p\n", CurrPtr, (*CurrPtr).Data, (*CurrPtr).Next);
      CurrPtr = CurrPtr->Next;
    }
  }
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/* Δέχεται:   Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
  Λειτουργία: Εκτελεί μια γραμμική αναζήτηση στην μη ταξινομημένη συνδεδεμένη
              λίστα για έναν κόμβο που να περιέχει το στοιχείο Item.
  Επιστρέφει: Αν η αναζήτηση είναι επιτυχής η Found είναι true, ο CurrPtr δείχνει
                στον κόμβο που περιέχει το Item και ο PredPtr στον προηγούμενό του
                ή είναι nil αν δεν υπάρχει προηγούμενος.
                Αν η αναζήτηση δεν είναι επιτυχής η Found είναι false.
*/
{
  ListPointer CurrPtr;
  boolean stop;

  CurrPtr = List;
  *PredPtr = NULL;
  stop = FALSE;
  while (!stop && CurrPtr != NULL) {
    if (CurrPtr->Data == Item)
      stop = TRUE;
    else {
      *PredPtr = CurrPtr;
      CurrPtr = CurrPtr->Next;
    }
  }
  *Found = stop;
}

void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/* Δέχεται:    Ένα στοιχείο Item και μια ταξινομημένη συνδεδεμένη λίστα,
                που περιέχει στοιχεία δεδομένων σε αύξουσα διάταξη και στην οποία
                ο δείκτης List δείχνει στον πρώτο  κόμβο.
   Λειτουργία: Εκτελεί γραμμική αναζήτηση της συνδεδεμένης ταξινομημένης λίστας
                για τον πρώτο κόμβο που περιέχει το στοιχείο Item ή για μια θέση
                για να εισάγει ένα νέο κόμβο που να περιέχει το στοιχείο Item.
   Επιστρέφει: Αν η αναζήτηση είναι επιτυχής η Found είναι true,
                ο CurrPtr δείχνει στον κόμβο που περιέχει το Item και
                ο PredPtr στον προηγούμενό του ή είναι nil αν δεν υπάρχει προηγούμενος.
                Αν η αναζήτηση δεν είναι επιτυχής η Found είναι false.
*/
{
  ListPointer CurrPtr;
  boolean DoneSearching;

  CurrPtr = List;
  *PredPtr = NULL;
  DoneSearching = FALSE;
  *Found = FALSE;
  while (!DoneSearching && CurrPtr != NULL) {
    if (CurrPtr->Data >= Item) {
      DoneSearching = TRUE;
      *Found = (CurrPtr->Data == Item);
    } else {
      *PredPtr = CurrPtr;
      CurrPtr = CurrPtr->Next;
    }
  }
}

void PrintList(ListPointer List)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
   Λειτουργία: Διασχίζει τη συνδεδεμένη λίστα και
                επεξεργάζεται κάθε δεδομένο ακριβώς μια φορά.
   Επιστρέφει: Εξαρτάται από το είδος της επεξεργασίας.
*/
{
  ListPointer CurrPtr;

  if (EmptyList(List))
    printf("EMPTY LIST\n");
  else {
    CurrPtr = List;
    while (CurrPtr != NULL) {
      printf("%d ", CurrPtr->Data);
      CurrPtr = CurrPtr->Next;
    }
    printf("\n");
  }
}

void difference_list(ListPointer AList,ListPointer BList,ListPointer *CList)
{
  ListPointer CurPtr, PredPtr;
  ListElementType item;
  boolean found1,found2;

  // traverse all item at AList

  if (EmptyList(AList))
    printf("EMPTY LIST\n");
  else {
    CurPtr = AList;
    while (CurPtr != NULL) {
      item = CurPtr->Data;
      // search item at BList
      LinearSearch(BList,item,&PredPtr,&found1);
      if (found1==FALSE) {
        // add to CList but only once
        LinearSearch(*CList,item,&PredPtr,&found2);
        if (found2==FALSE) {
          LinkedInsert(CList,item, NULL);
        }
      }
      CurPtr = CurPtr->Next;
    }
  }
}

int main()
{
  ListPointer AList, BList,CList;
  ListElementType item;
  int i,n;

  CreateList(&AList);

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 1: ");
  scanf("%d", &n);

  // insert data in list
  for (i = 1; i <= n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 1: ");
    scanf("%d", &item);
    LinkedInsert(&AList, item, NULL);
  }

  CreateList(&BList);

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 2: ");
  scanf("%d", &n);

  // insert data in list
  for (i = 1; i <= n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 2: ");
    scanf("%d", &item);
    LinkedInsert(&BList, item, NULL);
  }

  printf("1i lista\n");
  PrintList(AList);

  printf("2i lista\n");
  PrintList(BList);

  CreateList(&CList);

  difference_list(AList,BList,&CList);

  printf("Teliki lista\n");
  PrintList(CList);

  return 0;
}

