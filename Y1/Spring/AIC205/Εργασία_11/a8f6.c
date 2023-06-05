/*******************************************************************************
 * Filename: a8f6.c
 * data structures (AIC205)
 * ics23088
 ******************************************************************************/

#include <stdio.h>

#include "ctype.h"

#define HMax 10      /*     το μέγεθος του πίνακα HashTable \
                        ενδεικτικά ίσο με 10 */
#define VMax 30      /*το μέγεθος της λίστας, \
                         ενδεικτικά ίσο με 30 */
#define EndOfList -1 /* σημαία που σηματοδοτεί το τέλος της λίστας \
                         και της κάθε υπολίστας συνωνύμων */

typedef struct
{
  int type;
  char name[20];
} ListElementType;

typedef int KeyType;

typedef struct
{
  KeyType RecKey;
  ListElementType Data;
  int Link;
} ListElm;

typedef struct
{
  int HashTable[HMax];  // πίνακας δεικτών προς τις υπολίστες συνωνύμων
  int Size;             // πλήθος εγγραφών της λίστας List
  int SubListPtr;       // Dδείκτης σε μια υπολίστα συνωνύμων
  int StackPtr;         // δείκτης προς την πρώτη ελεύθερη θέση της λίστας List
  ListElm List[VMax];
} HashListType;

typedef enum {
  FALSE,
  TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType Key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred);
void SearchHashList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred);
void AddRec(HashListType *HList, ListElm InRec);
void DeleteRec(HashListType *HList, KeyType DelKey);
void Print_HashList(HashListType HList);
void PrintPinakes(HashListType HList);

char *userTyper[] = {"student", "postgraduate student", "teacher", "visitor"};

int main() {
  ListElm AnItem;
  HashListType Hlist;
  char ch;
  int Loc, Pred;

  // 1 create HashList
  CreateHashList(&Hlist);

  // 2 insert new user
  do {
    printf("Enter user's key: ");
    scanf("%d", &AnItem.RecKey);
    printf("Enter user's name: ");
    scanf("%s", AnItem.Data.name);
    getchar();
    printf("Enter user's position (1 = student, 2 = postgraduate student, 3 = teacher, 4 = visitor): ");
    scanf("%d", &AnItem.Data.type);
    AnItem.Link = EndOfList;
    AddRec(&Hlist, AnItem);
    printf("\nContinue Y/N: ");
    do {
      scanf("%c", &ch);
    } while (toupper(ch) != 'N' && toupper(ch) != 'Y');
  } while (toupper(ch) != 'N');

  // 3 delete a user
  do {
    printf("Enter user's key for deleting in the Hash: ");
    scanf("%d", &AnItem.RecKey);
    DeleteRec(&Hlist, AnItem.RecKey);
    printf("\nContinue Y/N: ");
    do {
      scanf("%c", &ch);
    } while (toupper(ch) != 'N' && toupper(ch) != 'Y');
  } while (toupper(ch) != 'N');

  // 4 search for a user
  do {
    printf("Enter user's key for searching in the Hash: ");
    scanf("%d", &AnItem.RecKey);
    SearchHashList(Hlist, AnItem.RecKey, &Loc, &Pred);
    if (Loc != EndOfList) {
      printf("[%d,%s,%s]\n", Hlist.List[Loc].RecKey, Hlist.List[Loc].Data.name, userTyper[Hlist.List[Loc].Data.type - 1]);
    } else {
      printf("There is no user with code %d\n", AnItem.RecKey);
    }

    printf("\nContinue Y/N: ");
    do {
      scanf("%c", &ch);
    } while (toupper(ch) != 'N' && toupper(ch) != 'Y');
  } while (toupper(ch) != 'N');

  // 5 print list of all users
  Print_HashList(Hlist);

  return 0;
}

int HashKey(KeyType Key)
/* Δέχεται:    Την τιμή Key ενός κλειδιού.
   Λειτουργία: Βρίσκει την τιμή κατακερματισμού HValue για το κλειδί Key.
   Επιστρέφει: Την τιμή κατακερματισμού HValue
*/
{
  /*σε περίπτωση που το KeyType δεν είναι ακέραιος
  θα πρέπει να μετατρέπεται κατάλληλα το κλειδί σε αριθμό*/
  return Key % HMax;
}

void CreateHashList(HashListType *HList)
/* Λειτουργία: Δημιουργεί μια δομή HList.
   Επιστρέφει: Την δομή HList
*/
{
  int index;

  HList->Size = 0;      // ΔΗΜΙΟΥΡΓΕΙ ΜΙΑ ΚΕΝΗ ΛΙΣΤΑ
  HList->StackPtr = 0;  // ΔΕΙΚΤΗς ΣΤΗ ΚΟΡΥΦΗ ΤΗΣ ΣΤΟΙΒΑΣ ΤΩΝ ΕΛΕΥΘΕΡΩΝ ΘΕΣΕΩΝ

  /*ΑΡΧΙΚΟΠΟΙΕΙ ΤΟΝ ΠΙΝΑΚΑ HashTable ΤΗΣ ΔΟΜΗΣ HList ΩΣΤΕ ΚΑΘΕ ΣΤΟΙΧΕΙΟΥ ΤΟΥ
      ΝΑ ΕΧΕΙ ΤΗ ΤΙΜΗ EndOfList (-1)*/
  for (index = 0; index < HMax; index++) {
    HList->HashTable[index] = EndOfList;
  }
  // Δημιουργία της στοίβας των ελεύθερων θέσεων στη λίστα HList

  for (index = 0; index < VMax - 1; index++) {
    HList->List[index].Link = index + 1;
  }
  HList->List[index].Link = EndOfList;
}

boolean FullHashList(HashListType HList)
/* Δέχεται:    Μια δομή HList.
   Λειτουργία: Ελέγχει αν η λίστα List της δομής HList είναι γεμάτη.
   Επιστρέφει: TRUE αν η λίστα List είναι γεμάτη, FALSE διαφορετικά.
*/
{
  return (HList.Size == VMax);
}

void SearchSynonymList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στην υπολίστα συνωνύμων.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της προηγούμενης
                εγγραφής στην υπολίστα
*/
{
  int Next;
  Next = HList.SubListPtr;
  *Loc = -1;
  *Pred = -1;
  while (Next != EndOfList) {
    if (HList.List[Next].RecKey == KeyArg) {
      *Loc = Next;
      Next = EndOfList;
    } else {
      *Pred = Next;
      Next = HList.List[Next].Link;
    }
  }
}
void SearchHashList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στη δομή HList.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της
                προηγούμενης εγγραφής της υπολίστας στην οποία ανήκει.
                Αν δεν υπάρχει εγγραφή με κλειδί KeyArg τότε Loc=Pred=-1
*/
{
  int HVal;
  HVal = HashKey(KeyArg);
  if (HList.HashTable[HVal] == EndOfList) {
    *Pred = -1;
    *Loc = -1;
  } else {
    HList.SubListPtr = HList.HashTable[HVal];
    SearchSynonymList(HList, KeyArg, Loc, Pred);
  }
}

void AddRec(HashListType *HList, ListElm InRec)
/* Δέχεται:    Μια δομή HList και μια εγγραφή InRec.
   Λειτουργία: Εισάγει την εγγραφή InRec στη λίστα List, αν δεν είναι γεμάτη,
                και ενημερώνει τη δομή HList.
   Επιστρέφει: Την τροποποιημένη δομή HList.
   Έξοδος:     Μήνυμα γεμάτης λίστας, αν η List είναι γεμάτη, διαφορετικά,
                αν υπάρχει ήδη εγγραφή με το ίδιο κλειδί,
                εμφάνιση αντίστοιχου μηνύματος
*/
{
  int Loc, Pred, New, HVal;

  // New=0;
  if (!(FullHashList(*HList))) {
    Loc = -1;
    Pred = -1;
    SearchHashList(*HList, InRec.RecKey, &Loc, &Pred);
    if (Loc == -1) {
      HList->Size = HList->Size + 1;
      New = HList->StackPtr;
      HList->StackPtr = HList->List[New].Link;
      HList->List[New] = InRec;
      if (Pred == -1) {
        HVal = HashKey(InRec.RecKey);
        HList->HashTable[HVal] = New;
        HList->List[New].Link = EndOfList;
      } else {
        HList->List[New].Link = HList->List[Pred].Link;
        HList->List[Pred].Link = New;
      }
    }

    else {
      printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
    }
  } else {
    printf("Full list...");
  }
}
void DeleteRec(HashListType *HList, KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
  int Loc, Pred, HVal;

  SearchHashList(*HList, DelKey, &Loc, &Pred);
  if (Loc != -1) {
    if (Pred != -1) {
      HList->List[Pred].Link = HList->List[Loc].Link;
    } else {
      HVal = HashKey(DelKey);
      HList->HashTable[HVal] = HList->List[Loc].Link;
    }
    HList->List[Loc].Link = HList->StackPtr;
    HList->StackPtr = Loc;
    HList->Size = HList->Size - 1;
  } else {
    printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n", DelKey);
  }
}
void Print_HashList(HashListType HList) {
  int i, SubIndex;

  printf("USERS:\n");
  for (i = 0; i < HMax; i++) {
    SubIndex = HList.HashTable[i];
    if (SubIndex != EndOfList) {
      printf("Synonyms, collision at position: %d\n", i);
    }
    while (SubIndex != EndOfList) {
      printf("%d:[%d,%s,%s]\n",
             SubIndex,
             HList.List[SubIndex].RecKey,
             HList.List[SubIndex].Data.name,
             userTyper[HList.List[SubIndex].Data.type - 1]);
      SubIndex = HList.List[SubIndex].Link;
    }  //* while *)
  }
}
void PrintPinakes(HashListType HList) {
  int i;
  printf("Hash table\n");
  for (i = 0; i < HMax; i++)
    printf("%d| %d\n", i, HList.HashTable[i]);

  printf("Hash List\n");
  for (i = 0; i < VMax; i++)
    printf("%d) %d, %d\n", i, HList.List[i].RecKey, HList.List[i].Link);
  printf("\n");
}
