/*******************************************************************************
 * Filename: a14f5.c
 * data structures (AIC205)
 * ics23088
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char name[21];
  char phone[11];
  int code;
} BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
  BinTreeElementType Data;
  BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
  FALSE,
  TRUE
} boolean;

/* ------------------------------------------------------------------------- */

void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);

/* new functions */
int BuildBST(char *filename, BinTreePointer *ARoot);
void printTeachers(BinTreePointer ARoot);
void RecBSTSearchBySubject(BinTreePointer Root, int code);

/* ------------------------------------------------------------------------- */

void CreateBST(BinTreePointer *Root)
/* Λειτουργία: Δημιουργεί ένα κενό ΔΔΑ.
   Επιστρέφει:  Τον μηδενικό δείκτη(NULL) Root
*/
{
  *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
/* Δέχεται:   Ενα ΔΔα με το Root να δείχνει στη ρίζα του.
  Λειτουργία: Ελέγχει αν το ΔΔΑ είναι κενό.
  Επιστρέφει: TRUE αν το ΔΔΑ είναι κενό και FALSE διαφορετικά
*/
{
  return (Root == NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/* Δέχεται:     Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και ένα στοιχείο Item.
   Λειτουργία:  Εισάγει το στοιχείο Item στο ΔΔΑ.
   Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του
*/
{
  if (BSTEmpty(*Root)) {
    (*Root) = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    strcpy((*Root)->Data.name,Item.name);
    strcpy((*Root)->Data.phone,Item.phone);
    (*Root)->Data.code = Item.code;
    (*Root)->LChild = NULL;
    (*Root)->RChild = NULL;
  } else if (strcmp(Item.name, (*Root)->Data.name) < 0)
    RecBSTInsert(&(*Root)->LChild, Item);
  else if (strcmp(Item.name, (*Root)->Data.name) > 0)
    RecBSTInsert(&(*Root)->RChild, Item);
  else
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                  boolean *Found, BinTreePointer *LocPtr)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του.
   Επιστρέφει: Η Found έχει τιμή TRUE και ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE
*/
{
  if (BSTEmpty(Root))
    *Found = FALSE;
  else if (strcmp(KeyValue.name, Root->Data.name) < 0)
    RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
  else if (strcmp(KeyValue.name, Root->Data.name) > 0)
    RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
  else {
    *Found = TRUE;
    *LocPtr = Root;
  }
}

void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
/* Δέχεται:  Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Προσπαθεί να βρει έναν κόμβο στο ΔΔΑ που να περιέχει την τιμή
                KeyValue στο πεδίο κλειδί του τμήματος δεδομένων του και,
                αν τον βρει, τον διαγράφει από το ΔΔΑ.
  Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του.
*/
{
  BinTreePointer TempPtr;  //* true AN TO STOIXEIO KeyValue EINAI STOIXEIO TOY DDA *)

  if (BSTEmpty(*Root))  //* ΑΔΕΙΟ ΔΕΝΔΡΟ ΤΟ KeyValue ΔΕ ΘΑ ΒΡΕΘΕΙ *)
    printf("TO STOIXEIO DEN BRE8HKE STO DDA\n");
  else
    //* αναζήτησε αναδρομικά τον κόμβο που περιέχει την τιμή KeyValue και διάγραψέ τον
    if (strcmp(KeyValue.name, (*Root)->Data.name) < 0)
      RecBSTDelete(&((*Root)->LChild), KeyValue);  //* ΑΡΙΣΤΕΡΟ ΥΠΟΔΕΝΔΡΟ *
    else if (strcmp(KeyValue.name, (*Root)->Data.name) > 0)
      RecBSTDelete(&((*Root)->RChild), KeyValue);  //* ΔΕΞΙ  ΥΠΟΔΕΝΔΡΟ *
    else                                           //* TO KeyValue ΒΡΕΘΗΚΕ ΔΙΑΓΡΑΦΗ ΤΟΥ ΚΟΜΒΟΥ *)
      if ((*Root)->LChild == NULL) {
        TempPtr = *Root;
        *Root = (*Root)->RChild;  //* ΔΕΝ ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ *)
        free(TempPtr);
      } else if ((*Root)->RChild == NULL) {
        TempPtr = *Root;
        *Root = (*Root)->LChild;  //* ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ, ΑΛΛΑ ΟΧΙ ΔΕΞΙ *)
        free(TempPtr);
      } else  //* ΕΧΕΙ 2 ΠΑΙΔΙΑ *)
      {
        //* ΕΥΡΕΣΗ ΤΟΥ INORDER ΑΠΟΓΟΝΟΥ ΤΟΥ *)
        TempPtr = (*Root)->RChild;
        while (TempPtr->LChild != NULL)
          TempPtr = TempPtr->LChild;
        /* ΜΕΤΑΚΙΝΗΣΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΤΗς ΡΙΖΑΣ ΤΟΥ ΥΠΟΔΕΝΔΡΟΥ
        ΠΟΥ ΕΞΕΤΑΖΕΤΑΙ ΚΑΙ ΔΙΑΓΡΑΦΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΚΟΜΒΟΥ */
        (*Root)->Data = TempPtr->Data;
        RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
      }
}

void RecBSTInorder(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
  if (Root != NULL) {
    //    printf("L");
    RecBSTInorder(Root->LChild);
    printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
    //    printf("R");
    RecBSTInorder(Root->RChild);
  }
  // printf("U");
}

void RecBSTPreorder(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί προδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
  if (Root != NULL) {
    printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
    // printf("L");
    RecBSTPreorder(Root->LChild);
    //  printf("R");
    RecBSTPreorder(Root->RChild);
  }
  // printf("U");
}

void RecBSTPostorder(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί μεταδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
  if (Root != NULL) {
    //  printf("L");
    RecBSTPostorder(Root->LChild);
    //   printf("R");
    RecBSTPostorder(Root->RChild);
    printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
  }
  // printf("U");
}



/* new functions */

int BuildBST(char *filename, BinTreePointer *ARoot) {
  FILE *fp;
  char surname[21];
  char phone[11];
  int code;
  int nscan;
  char termch;
  boolean stop = FALSE;
  BinTreeElementType ARec;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  while (TRUE) {
    nscan = fscanf(fp, "%20[^,], %10[^,],%d%c", surname, phone, &code, &termch);
    if (nscan == EOF) break;
    if (nscan != 4 || termch != '\n') {
      printf("Improper file format\n");
      return 1;
      stop = TRUE;
      break;
    } else {
      strcpy(ARec.name, surname);
      strcpy(ARec.phone, phone);
      ARec.code = code;
      RecBSTInsert(ARoot, ARec);
    }
  }
  fclose(fp);
  return 0;
}

void printTeachers(BinTreePointer ARoot) {
  printf("Print teachers data\n");
  RecBSTInorder(ARoot);
  printf("\n");
}

void RecBSTSearchBySubject(BinTreePointer Root, int code) {
  if (Root != NULL) {
    RecBSTSearchBySubject(Root->LChild, code);
    if (Root->Data.code == code) {
      printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
    }
    RecBSTSearchBySubject(Root->RChild, code);
  }
}

int main(void) {
  int res;
  int i;
  boolean found;

  BinTreePointer ARoot;
  BinTreeElementType ARec;
  BinTreePointer LocPtr;

  // 1
  CreateBST(&ARoot);

  res = BuildBST("I14F5.TXT", &ARoot);
  if (res != 0) {
    return res;
  }

  // 2
  printTeachers(ARoot);

  // 3
  for (i = 1; i <= 2; i++) {
    printf("Give teacher full name: ");
    scanf("%[^\n]", ARec.name);
    printf("Give teacher phone number: ");
    scanf("%s", ARec.phone);
    printf("Give teacher code: ");
    scanf("%d", &ARec.code);
    getchar();
    RecBSTInsert(&ARoot, ARec);
    printf("\n");
  }

  // 4
  printf("Give teacher full name to search: ");
  scanf("%[^\n]", ARec.name);
  RecBSTSearch(ARoot, ARec, &found, &LocPtr);
  if (found == TRUE) {
    printf("%s, %s, %d\n", LocPtr->Data.name, LocPtr->Data.phone, LocPtr->Data.code);
  }

  // 5
  printf("\nGive code to search: ");
  scanf("%d", &ARec.code);
  getchar();
  RecBSTSearchBySubject(ARoot, ARec.code);

  // 6
  printf("\nGive teacher full name to delete: ");
  scanf("%[^\n]", ARec.name);
  RecBSTDelete(&ARoot, ARec);

  // 7
  printf("\n");
  printTeachers(ARoot);
}
