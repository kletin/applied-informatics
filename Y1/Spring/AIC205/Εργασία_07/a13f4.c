/*******************************************************************************
* Filename: a13f4.c
* data structures (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char name[9];
  char filename[13];
} QueueElementType;

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
	QueueElementType Data;
    QueuePointer Next;
} QueueNode;

typedef struct
{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void TraverseQ(QueueType Queue);
                        

void CreateQ(QueueType *Queue)
{
	Queue->Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
{
	return (Queue.Front==NULL);
}

void AddQ(QueueType *Queue, QueueElementType Item)
{
	QueuePointer TempPtr;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    TempPtr->Data = Item; 
    TempPtr->Next = NULL;
    if (Queue->Front==NULL) {
        Queue->Front=TempPtr;
    }
    else {
        Queue->Rear->Next = TempPtr;
    }
    Queue->Rear=TempPtr;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
{
    QueuePointer TempPtr;
    
    if (EmptyQ(*Queue)) {
   	    printf("EMPTY Queue\n");
    }
   else
   {
        TempPtr = Queue->Front;
        *Item=TempPtr->Data;
        Queue->Front = Queue->Front->Next;     
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }   
}

void TraverseQ(QueueType Queue) {
  QueuePointer CurrPtr;

  if (EmptyQ(Queue)) {
    //printf("EMPTY Queue\n");
  } else {
    CurrPtr = Queue.Front;
    while (CurrPtr != NULL) {
      printf("Printing the job of %s,%s\n", CurrPtr->Data.name,CurrPtr->Data.filename);
      printf("Press any key to continue");
      getchar();
      CurrPtr = CurrPtr->Next;
    }
  }
  //printf("\n");
}

#define FILENAME "i13f4.dat"

#define UPREFIX1 "USER"
#define UPREFIX2 "FORT"

/* main function ------------------------------------------------------------*/

int main(void) {
  QueueType AQueue, BQueue;
  QueueElementType AnItem;
  FILE *fp;
  char username[9];
  char filename[13];
  boolean isUser;

  CreateQ(&AQueue);
  CreateQ(&BQueue);

  /* Open File --------------------------------------------------------------*/
  fp = fopen(FILENAME, "r");

  if (fp == NULL) {
    printf("Error: File not found:%s\n", FILENAME);
    return 1;
  }

  /* Read line from File ----------------------------------------------------*/
  while (!feof(fp)) {
    int nscan = fscanf(fp, "%s", username);
    if (nscan == EOF) {
      break;
    }
    nscan = fscanf(fp, "%s", filename);
    if (nscan == EOF) {
      break;
    }

    isUser = FALSE;
    strcpy(AnItem.name, username);
    strcpy(AnItem.filename, filename);
    if (strncmp(username, UPREFIX1, strlen(UPREFIX1)) == 0) {
      isUser = TRUE;
    }
    if (strncmp(username, UPREFIX2, strlen(UPREFIX2)) == 0) {
      isUser = TRUE;
    }
    if (isUser==TRUE) {
      AddQ(&AQueue, AnItem);
    } else {
      AddQ(&BQueue, AnItem);
    }
  }
  fclose(fp);

  /* Traverse Queues --------------------------------------------------------*/

  TraverseQ(BQueue);
  TraverseQ(AQueue);

  printf("There are no jobs in the printing queue\n");

}
