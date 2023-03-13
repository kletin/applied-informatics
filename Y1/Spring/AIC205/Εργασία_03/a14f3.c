#include <stdio.h>

/* Queue */
#define QueueLimit (20+1)  //το όριο μεγέθους της ουράς

typedef int QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς */

typedef struct
{
  int Front, Rear;
  int Size;
  QueueElementType Element[QueueLimit];
} QueueType;

typedef enum
{
  FALSE, TRUE
} boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);

void showQ(QueueType Queue);

void GetNthElementValueA(QueueType *Q, int n, QueueElementType *item);
void GetNthElementValueB(QueueType Q, int n, QueueElementType *item);


/* ------------------------------------------------------------------------*/

void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
  Queue->Front = 0;
  Queue->Rear = 0;
  Queue->Size = 0;
}

boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
  return (Queue.Front == Queue.Rear);
}

boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
  return ((Queue.Front) == ((Queue.Rear + 1) % QueueLimit));
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την εμπρός άκρη της ουράς
                αν η ουρά δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα κενής ουρά αν η ουρά είναι κενή
*/
{
  if (!EmptyQ(*Queue)) {
    *Item = Queue->Element[Queue->Front];
    Queue->Front = (Queue->Front + 1) % QueueLimit;
    --(Queue->Size);
  } else {
    //printf("Empty Queue\n");
  }
}

void AddQ(QueueType *Queue, QueueElementType Item)
/* Δέχεται:    Μια ουρά Queue και ένα στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στην ουρά Queue
                αν η ουρά δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα γεμάτης ουράς αν η ουρά είναι γεμάτη
*/
{
  if (!FullQ(*Queue)) {
    Queue->Element[Queue->Rear] = Item;
    Queue->Rear = (Queue->Rear + 1) % QueueLimit;
    ++(Queue->Size);
  } else {
    //printf("Full Queue\n");
  }
}

void showQ(QueueType Queue)
{
  int current;
  if (!EmptyQ(Queue)) {
    current = Queue.Front;
    while (current != Queue.Rear) {
      printf("%d ", Queue.Element[current]);
      current = (current + 1) % QueueLimit;
    }
    printf("\n");
  } else {
    // printf("Empty Queue\n");
  }
}


void GetNthElementValueA(QueueType *Q, int n, QueueElementType *item)
{
  QueueType tempQ;
  int i = 0;
  QueueElementType tempItem;

  CreateQ(&tempQ);

  // copy Queue Q to tempQ
  while (!EmptyQ(*Q)) {
    RemoveQ(Q, &tempItem);
    AddQ(&tempQ, tempItem);
    i++;
    if (i == n) {
      *item = tempItem;
    }
  }

  // restore original Queue Q
  while (!EmptyQ(tempQ)) {
    RemoveQ(&tempQ, &tempItem);
    AddQ(Q, tempItem);
  }
}

void GetNthElementValueB(QueueType Q, int n, QueueElementType *item)
{
  int index = 0;
  int current = 0;
  if (!EmptyQ(Q)) {
    current = Q.Front;
    while (current != Q.Rear) {
      index++;
      if (index == n) {
        *item = Q.Element[current];
      }
      current = (current + 1) % QueueLimit;
    }
  }
}

/* ------------------------------------------------------------------------*/

int main()
{
  QueueElementType ValueA, ValueB;
  QueueType AQueue;

  int n;
  CreateQ(&AQueue);

  int  i;
  for (i = 1; i < QueueLimit ; i++) {
    AddQ(&AQueue, i * 5);
  }

  showQ(AQueue);

  do {
    printf("Dwse n: ");
    scanf(" %d", &n);
  } while (n > AQueue.Size);

  //printf("n=%d\n",n);

  GetNthElementValueA(&AQueue, n, &ValueA);
  printf("ValueA:%d\n", ValueA);

  GetNthElementValueB(AQueue, n, &ValueB);
  printf("ValueB:%d\n", ValueB);

  showQ(AQueue);

}
