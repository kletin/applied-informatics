#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Queue */
#define QueueLimit (2+1)             //το όριο μεγέθους της ουράς
#define QueueLimit2 (20+1)           //το όριο μεγέθους της ουράς 2 

#define NUM_CLINICS 5

typedef char QueueElementType[25];   /* ο τύπος δεδομένων των στοιχείων της ουράς */

typedef struct
{
  int Front, Rear;
  QueueElementType Element[QueueLimit];
} QueueType;

typedef struct                     /* ο τύπος δεδομένων των στοιχείων της ουράς 2 */ 
{
  QueueElementType name;
  int code;
  char phoneNumber[10];
} QueueElementType2;

typedef struct
{
  int Front, Rear;
  QueueElementType2 Element[QueueLimit2];
} QueueType2;

typedef enum
{
  FALSE, TRUE
} boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void showQ(QueueType Queue, int code);


void CreateWQ(QueueType2 *Queue);
boolean EmptyWQ(QueueType2 Queue);
boolean FullWQ(QueueType2 Queue);
void RemoveWQ(QueueType2 *Queue, QueueElementType *Item);
void AddWQ(QueueType2 *Queue, QueueElementType2 Item);
void showWaitingQ(QueueType2 Queue);


void newAppointment(int code, QueueType *Q, QueueType2 *WQ);


/* implementation of functions */

void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
  Queue->Front = 0;
  Queue->Rear = 0;
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
    strcpy(*Item, Queue->Element[Queue->Front]);
    Queue ->Front  = (Queue ->Front + 1) % QueueLimit;
  } else
    printf("Empty Queue\n");
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
    strcpy(Queue->Element[Queue->Rear], Item);
    Queue ->Rear = (Queue ->Rear + 1) % QueueLimit;
  } else
    printf("Full Queue\n");
}


void showQ(QueueType Queue, int code)
{
  printf("\nAppointments of clinic %d\n", code);

  int current;
  if (!EmptyQ(Queue)) {
    current = Queue.Front;
    while (current != Queue.Rear) {
      printf("%s\n", Queue.Element[current]);
      current = (current + 1) % QueueLimit;
    }
  } else {
    // printf("Empty Queue\n");
  }
}

/* ---------------------------------------------------------------- */

void
CreateWQ(QueueType2 * Queue)
{
  Queue->Front = 0;
  Queue->Rear = 0;
}

boolean
EmptyWQ(QueueType2 Queue)
{
  return (Queue.Front == Queue.Rear);
}

boolean
FullWQ(QueueType2 Queue)
{
  return ((Queue.Front) == ((Queue.Rear + 1) % QueueLimit2));
}

void
AddWQ(QueueType2 * Queue, QueueElementType2 Item)
{
  if (!FullWQ(*Queue)) {
    Queue->Element[Queue->Rear].code = Item.code;
    strcpy(Queue->Element[Queue->Rear].name, Item.name);
    strcpy(Queue->Element[Queue->Rear].phoneNumber, Item.phoneNumber);

    Queue->Rear = (Queue->Rear + 1) % QueueLimit2;
  } else {
    printf("Full Queue\n");
  }
}


void
showWaitingQ(QueueType2 Queue)
{
  printf("\nWaiting list:\n");

  int current;
  if (!EmptyWQ(Queue)) {
    current = Queue.Front;
    while (current != Queue.Rear) {
      printf("%s, %d, %s \n", Queue.Element[current].name, Queue.Element[current].code, Queue.Element[current].phoneNumber);
      current = (current + 1) % QueueLimit2;
    }
  } else {
    // printf("Empty Queue\n");
  }
}

/* ---------------------------------------------------------------- */

void
newAppointment(int code, QueueType *Q, QueueType2 *WQ)
{
  QueueElementType name;
  boolean waiting = FALSE;
  char phoneNumber[10];
  QueueElementType2 elem2;

  printf("Give your name: ");
  scanf("%24s", name);

  if (!FullQ(*Q)) {
    AddQ(Q, name);
    printf("Successful appointment for clinic %d\n", code);
  } else {
    waiting = TRUE;
    printf("You are in a waiting list\n");
    printf("Give your phone number: ");
    scanf("%9s", phoneNumber);

    elem2.code = code;
    strcpy(elem2.name, name);
    strcpy(elem2.phoneNumber, phoneNumber);
    AddWQ(WQ, elem2);
  }
}


/* ---------------------------------------------------------------- */

int main()
{
  QueueType Q[NUM_CLINICS + 1];
  QueueType2 waitingQ;

  int i;
  char a;

  for (i = 1; i <= NUM_CLINICS; i++) {
    CreateQ(&Q[i]);
  }

  CreateWQ(&waitingQ);

  srand(54);
  do {
    int code = rand() % NUM_CLINICS + 1;

    newAppointment(code, &Q[code], &waitingQ);
    printf("Continue Y/N (Y=yes, N=No): ");
    scanf(" %c", &a);
  } while ((a != 'N') && (a != 'n'));

  for (i = 1; i <= NUM_CLINICS; i++) {
    showQ(Q[i], i);
  }

  showWaitingQ(waitingQ);

}
