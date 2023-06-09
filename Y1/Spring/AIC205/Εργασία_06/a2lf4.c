/*******************************************************************************
* Filename: a2lf4.c
* ����� ��������� (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int ListElementType;           /* � ����� ��� ��������� ��� ������������ ������
                                        ���������� ����� int */
typedef struct ListNode *ListPointer;   //� ����� ��� ������� ��� ���� �������
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
void MergeLinkedLists(ListPointer *List, ListPointer BList);

/* ---------------------------------------------------------------------- */

void CreateList(ListPointer *List)
/* ����������: ���������� ��� ���� ����������� �����.
  ����������:  ��� �������� ������ List
*/
{
  *List = NULL;
}

boolean EmptyList(ListPointer List)
/* �������:   ��� ����������� ����� �� ��� List �� ������� ���� ����� �����.
  ����������: ������� �� � ����������� ����� ����� ����.
  ����������: True �� � ����� ����� ���� ��� false �����������
*/
{
  return (List == NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
/* �������:    ��� ����������� ����� �� ��� List �� ������� ���� ����� �����,
                ��� �������� ��������� Item ��� ���� ������ PredPtr.
   ����������: ������� ���� �����, ��� �������� �� Item, ���� ����������� �����
                ���� ��� ��� ����� ��� �������������� ��� ��� PredPtr
                � ���� ����  ��� ������������ ������,
                �� � PredPtr ����� ���������(NULL).
  ����������:  ��� ������������� ����������� ����� �� ��� ����� ����� ���
                �� �������������� ��� ��� List.
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
/* �������:    ��� ����������� ����� �� ��� List �� ������� ���� ����� ����� ���
                 ��� ���� ������ PredPtr.
   ����������: ��������� ��� �� ����������� ����� ��� ����� ��� ����
                ��� ����������� ��� ����� ���� ����� ������� � PredPtr
                � ��������� ��� ����� �����, �� � PredPtr ����� ���������,
                ����� ��� �� � ����� ����� ����.
   ����������: ��� ������������� ����������� ����� �� ��� ����� �����
                �� �������������� ��� ��� List.
   ������:     ��� ������ ����� ������ �� � ����������� ����� ���� ���� .
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
/* �������:    ��� ����������� ����� �� ��� List �� ������� ���� ����� �����.
   ����������: ��������� �� ����������� ����� ���
                ������������� ���� �������� ������� ��� ����.
   ����������: ��������� ��� �� ����� ��� ������������.
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
/* �������:   ��� ����������� ����� �� ��� List �� ������� ���� ����� �����.
  ����������: ������� ��� �������� ��������� ���� �� ������������ �����������
              ����� ��� ���� ����� ��� �� �������� �� �������� Item.
  ����������: �� � ��������� ����� �������� � Found ����� true, � CurrPtr �������
                ���� ����� ��� �������� �� Item ��� � PredPtr ���� ����������� ���
                � ����� nil �� ��� ������� ������������.
                �� � ��������� ��� ����� �������� � Found ����� false.
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
/* �������:    ��� �������� Item ��� ��� ������������ ����������� �����,
                ��� �������� �������� ��������� �� ������� ������� ��� ���� �����
                � ������� List ������� ���� �����  �����.
   ����������: ������� �������� ��������� ��� ������������ ������������� ������
                ��� ��� ����� ����� ��� �������� �� �������� Item � ��� ��� ����
                ��� �� ������� ��� ��� ����� ��� �� �������� �� �������� Item.
   ����������: �� � ��������� ����� �������� � Found ����� true,
                � CurrPtr ������� ���� ����� ��� �������� �� Item ���
                � PredPtr ���� ����������� ��� � ����� nil �� ��� ������� ������������.
                �� � ��������� ��� ����� �������� � Found ����� false.
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
/* �������:    ��� ����������� ����� �� ��� List �� ������� ���� ����� �����.
   ����������: ��������� �� ����������� ����� ���
                ������������� ���� �������� ������� ��� ����.
   ����������: ��������� ��� �� ����� ��� ������������.
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

void MergeLinkedLists(ListPointer *List, ListPointer BList)
{
  ListPointer CurrPtr, PredPtr;
  boolean found;

  // traverse all items in BList at inserted them at List
  if (EmptyList(BList))
    printf("EMPTY LIST\n");
  else {
    CurrPtr = BList;
    while (CurrPtr != NULL) {
      OrderedLinearSearch(*List, CurrPtr->Data, &PredPtr, &found);
      LinkedInsert(List, CurrPtr->Data, PredPtr);
      CurrPtr = CurrPtr->Next;
    }
  }
}

int main()
{
  ListPointer AList, BList, PredPtr;
  int i, n;
  ListElementType item;
  boolean found;

  CreateList(&AList);

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 1: ");
  scanf("%d", &n);

  // insert data in list
  for (i = 1; i <= n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 1: ");
    scanf("%d", &item);
    OrderedLinearSearch(AList, item, &PredPtr, &found);
    LinkedInsert(&AList, item, PredPtr);
  }

  CreateList(&BList);

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 2: ");
  scanf("%d", &n);

  // insert data in list
  for (i = 1; i <= n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 2: ");
    scanf("%d", &item);
    OrderedLinearSearch(BList, item, &PredPtr, &found);
    LinkedInsert(&BList, item, PredPtr);
  }

  printf("1i lista\n");
  PrintList(AList);

  printf("2i lista\n");
  PrintList(BList);

  MergeLinkedLists(&AList,BList);
  printf("Teliki lista\n");
  PrintList(AList);

  return 0;
}

