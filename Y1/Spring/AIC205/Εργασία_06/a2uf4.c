/*******************************************************************************
* Filename: a2uf4.c
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
void delete_list_after_n(ListPointer *List, int n);

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

void delete_list_after_n(ListPointer *List, int n)
{
  int i = 1;
  ListPointer CurrPtr, PredPtr;
  boolean valid_n = FALSE;

  if (n <= 0) {
    printf("Invalid n value\n");
    return;
  }
  if (EmptyList(*List)) {
    printf("EMPTY LIST\n");
    return;
  }

  // using code at LinkedTraverse

  CurrPtr = *List;
  while (CurrPtr != NULL) {
    if (i == n) {
      valid_n = TRUE;
      break;
    } else {
      i++;
      CurrPtr = CurrPtr->Next;
    }
  }

  if (valid_n == TRUE) {
    while (CurrPtr->Next != NULL) {
      LinkedDelete(List, CurrPtr);
    }
  } else {
    printf("Invalid n value\n");
  }

}

int main()
{
  ListPointer AList;
  ListPointer PredPtr = NULL;
  int i, n, pos;
  ListElementType item;

  CreateList(&AList);

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS: ");
  scanf("%d", &n);

  // insert data in list
  for (i = 1; i <= n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS: ");
    scanf("%d", &item);
    LinkedInsert(&AList, item, NULL);
  }

  printf("Arxiki lista\n");
  PrintList(AList);

  printf("DWSE TI THESI, META APO TIN OPOIA THA DIAGRAFOYN TA STOIXEIA: ");
  scanf("%d", &pos);

  delete_list_after_n(&AList, pos);

  printf("Teliki lista\n");
  PrintList(AList);

  return 0;
}

