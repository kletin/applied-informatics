/*******************************************************************************
* Filename: a21f4.c
* Δομές Δεδομένων (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>

#define NumberOfNodes 20    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 20*/
#define NilValue (-1)      // ειδική μηδενικη τιμη δείχνει το τέλος της Συνδ.λίστας


typedef int ListPointer;

typedef struct {
    int am;
    float mark;
} ListElementType;

typedef struct {
    ListElementType Data;
    ListPointer Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr που δείχνει στον
                πρώτο διαθέσιμο κόμβο.
  Λειτουργία: Αρχικοποιεί τον πίνακα Node ως συνδεδεμένη λίστα συνδέοντας μεταξύ
                τους διαδοχικές εγγραφές του πίνακα,
                και αρχικοποιεί τον δείκτη FreePtr .
  Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον
                δείκτη FreePtr του πρώτου διαθέσιμου κόμβου
*/
{
    int i;

    for (i = 0; i < NumberOfNodes - 1; i++) {
        Node[i].Next = i + 1;
        Node[i].Data.mark = -1; /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
        Node[i].Data.am = -1;
    }
    Node[NumberOfNodes - 1].Data.mark = -1;
    Node[NumberOfNodes - 1].Data.am = -1;
    *FreePtr = 0;
}

void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
   Επιστρέφει: Έναν (μηδενικό) δείκτη που δείχνει σε κενή λίστα
*/
{
    *List = NilValue;
}

boolean EmptyList(ListPointer List)
/* Δέχεται:    Έναν δείκτη List που δείχνει σε μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
   Επιστρέφει: True αν η συνδεδεμένη λίστα είναι κενή και false διαφορετικά
*/
{
    return (List == NilValue);
}

boolean FullList(ListPointer FreePtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι γεμάτη.
   Επιστρέφει: True αν η συνδεδεμένηλίστα είναι γεμάτη, false διαφορετικά
*/
{
    return (FreePtr == NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr.
  Λειτουργία: Αποκτά έναν "ελεύθερο" κόμβο που τον δείχνει ο δείκτης P.
  Επιστρέφει: Τον δείκτη P και τον τροποποιημένο  δείκτη FreePtr
                που δεικτοδοτεί στο πρώτο διαθέσιμο κόμβο
*/
{
    *P = *FreePtr;
    if (!FullList(*FreePtr))
        *FreePtr = Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
    Node[P].Next = *FreePtr;
    Node[P].Data.mark = -1;
    Node[P].Data.am = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην
                        εκτύπωση οι διαγραμμένοι κόμβοι */
    *FreePtr = P;
}

void Insert(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
/* Δέχεται:    Μια συνδεδεμένη λίστα, τον πίνακα Node, τον δείκτη PredPtr και
                ένα στοιχείο Item.
  Λειτουργία: Εισάγει στη συνδεδεμένη λίστα, αν δεν είναι γεμάτη, το στοιχείο
                Item μετά από τον κόμβο στον οποίο δείχνει ο δείκτης PredPtr.
  Επιστρέφει: Την τροποποιημένη συνδεδεμένη λίστα, τον τροποποιημένο πίνακα Node
                και τον δείκτη FreePtr.
  Εξοδος:     Μήνυμα γεμάτης λίστας, αν η συνδεδεμένη λίστα είναι γεμάτη
*/
{
    ListPointer TempPtr;
    GetNode(&TempPtr, FreePtr, Node);
    if (!FullList(TempPtr)) {
        if (PredPtr == NilValue) {
            Node[TempPtr].Data.am = Item.am;
            Node[TempPtr].Data.mark = Item.mark;

            Node[TempPtr].Next = *List;
            *List = TempPtr;
        } else {
            Node[TempPtr].Data.am = Item.am;
            Node[TempPtr].Data.mark = Item.mark;
            Node[TempPtr].Next = Node[PredPtr].Next;
            Node[PredPtr].Next = TempPtr;
        }
    } else
        printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr)
/* Δέχεται:   Μια συνδεδεμένη λίστα και τον δείκτη PredPtr που δείχνει
                στον προηγούμενο κόμβο από αυτόν που θα διαγραφεί.
  Λειτουργία: Διαγράφει από τη συνδεδεμένη λίστα, αν δεν είναι κενή,
                τον προηγούμενο κόμβο από αυτόν στον οποίο δείχνει ο PredPtr.
  Επιστρέφει: Την τροποποιημένη λίστα και το δείκτη FreePtr.
  Έξοδος:     Μήνυμα κενής λίστας, αν η συνδεδεμένη λίστα είναι κενή
*/
{
    ListPointer TempPtr;

    if (!EmptyList(*List)) {
        if (PredPtr == NilValue) {
            TempPtr = *List;
            *List = Node[TempPtr].Next;
        } else {
            TempPtr = Node[PredPtr].Next;
            Node[PredPtr].Next = Node[TempPtr].Next;
        }
        ReleaseNode(Node, TempPtr, FreePtr);
    } else
        printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Κάνει διάσχιση της συνδεδεμένης λίστας, αν δεν είναι κενή.
   Έξοδος:     Εξαρτάται από την επεξεργασία
*/
{
    ListPointer CurrPtr;
    int count = 0;

    if (!EmptyList(List)) {
        CurrPtr = List;
        while (CurrPtr != NilValue) {
            count++;
            CurrPtr = Node[CurrPtr].Next;
        }
    }
    printf("Plithos soixeiwn sth lista %d\n", count);

    if (!EmptyList(List)) {
        CurrPtr = List;
        while (CurrPtr != NilValue) {
            count++;
            printf("[%d: (%d,%g) ->%d] ", CurrPtr, Node[CurrPtr].Data.am, Node[CurrPtr].Data.mark, Node[CurrPtr].Next);
            CurrPtr = Node[CurrPtr].Next;
        }
        printf("\n");
    } else
        printf("Empty List ...\n");
}

int main() {

    ListPointer List;
    ListElementType elem1;

    NodeType Node[NumberOfNodes];
    ListPointer FreePtr;
    int studentsNum;
    int pos;

    InitializeStoragePool(Node, &FreePtr);
    CreateList(&List);

    printf("DWSE ARI8MO MA8HTWN: ");
    scanf("%d", &studentsNum);

    for (int i = 1; i <= studentsNum; i++) {
        printf("DWSE ARI8MO MHTRWOU GIA EISAGWGH STH LISTA: ");
        scanf("%d", &(elem1.am));
        printf("DWSE BA8MO GIA EISAGWGH STH LISTA: ");
        scanf("%f", &(elem1.mark));
        printf("DWSE TH 8ESH META THN OPOIA 8A GINEI H EISAGWGH STOIXEIOU: ");
        scanf("%d", &pos);
        printf("\n");

        Insert(&List, Node, &FreePtr, pos, elem1);
        TraverseLinked(List, Node);

    }

    printf("DWSE TH 8ESH TOU PROHGOUMENOU STOIXEIOU GIA DIAGRAFH: ");
    scanf("%d", &pos);
    printf("\n");

    Delete(&List, Node, &FreePtr, pos);
    TraverseLinked(List, Node);

    for (int i = 0; i <= 1; i++) {
        printf("DWSE ARI8MO MHTRWOU GIA EISAGWGH STH LISTA: ");
        scanf("%d", &(elem1.am));
        printf("DWSE BA8MO GIA EISAGWGH STH LISTA: ");
        scanf("%f", &(elem1.mark));
        printf("DWSE TH 8ESH META THN OPOIA 8A GINEI H EISAGWGH STOIXEIOU: ");
        scanf("%d", &pos);
        printf("\n");

        Insert(&List, Node, &FreePtr, pos, elem1);
        TraverseLinked(List, Node);
    }
    return 0;
}
