/*******************************************************************************
* Filename: a33f5.c
* data structures (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int BinTreeElementType; /*� ����� ��� ��������� ��� ���
                                        ���������� ����� int */
typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
  BinTreeElementType Data;
  BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
  FALSE,
  TRUE
} boolean;

void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);

/* new functions */
BinTreeElementType MinBSTValue(BinTreePointer Root);
BinTreeElementType MaxBSTValue(BinTreePointer Root);

void CreateBST(BinTreePointer *Root)
/* ����������: ���������� ��� ���� ���.
   ����������:  ��� �������� ������(NULL) Root
*/
{
  *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
/* �������:   ��� ��� �� �� Root �� ������� ��� ���� ���.
  ����������: ������� �� �� ��� ����� ����.
  ����������: TRUE �� �� ��� ����� ���� ��� FALSE �����������
*/
{
  return (Root == NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/* �������:     ��� ��� �� �� ������ Root �� ������� ��� ���� ��� ��� ��� �������� Item.
   ����������:  ������� �� �������� Item ��� ���.
   ����������: �� ������������� ��� �� ��� ������ Root �� ������� ��� ���� ���
*/
{
  BinTreePointer LocPtr, Parent;
  boolean Found;

  LocPtr = *Root;
  Parent = NULL;
  Found = FALSE;
  while (!Found && LocPtr != NULL) {
    Parent = LocPtr;
    if (Item < LocPtr->Data)
      LocPtr = LocPtr->LChild;
    else if (Item > LocPtr->Data)
      LocPtr = LocPtr->RChild;
    else
      Found = TRUE;
  }
  if (Found)
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
  else {
    LocPtr = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    LocPtr->Data = Item;
    LocPtr->LChild = NULL;
    LocPtr->RChild = NULL;
    if (Parent == NULL)
      *Root = LocPtr;
    else if (Item < Parent->Data)
      Parent->LChild = LocPtr;
    else
      Parent->RChild = LocPtr;
  }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
               BinTreePointer *LocPtr)
/* �������:    ��� ��� �� �� ������ Root �� ������� ��� ���� ��� ��� ��� ���� KeyValue.
   ����������: ������� ��� ��� ���� ����� �� ���� KeyValue ��� ����� ������ ���.
   ����������: � Found ���� ���� TRUE ��� � ������� LocPtr ������� ���� ����� ���
                �������� ��� ���� KeyValue, �� � ��������� ����� ��������.
                ����������� � Found ���� ���� FALSE
*/
{
  (*LocPtr) = Root;
  (*Found) = FALSE;
  while (!(*Found) && (*LocPtr) != NULL) {
    if (KeyValue < (*LocPtr)->Data)
      (*LocPtr) = (*LocPtr)->LChild;
    else if (KeyValue > (*LocPtr)->Data)
      (*LocPtr) = (*LocPtr)->RChild;
    else
      (*Found) = TRUE;
  }
}

void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr, BinTreePointer *Parent)
/* �������:    ��� ��� �� �� ������ Root �� ������� ��� ���� ��� ��� ��� ���� KeyValue.
   ����������: ������� ��� ��� ���� ����� �� ���� KeyValue ��� ����� ������ ���
                ��� ��� ������ ��� ������ �����.
   ����������: � Found ���� ���� TRUE, � ������� LocPtr ������� ���� ����� ���
                �������� ��� ���� KeyValue ��� � Parent ������� ���� ������
                ����� ��� ������, �� � ��������� ����� ��������.
                ����������� � Found ���� ���� FALSE.
*/
{
  *LocPtr = Root;
  *Parent = NULL;
  *Found = FALSE;
  while (!(*Found) && *LocPtr != NULL) {
    if (KeyValue < (*LocPtr)->Data) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->LChild;
    } else if (KeyValue > (*LocPtr)->Data) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->RChild;
    } else
      *Found = TRUE;
  }
}

void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
/* �������:  ��� ��� �� �� ������ Root �� ������� ��� ���� ��� ��� ��� ���� KeyValue.
  ����������: ��������� �� ���� ���� ����� ��� ��� ��� �� �������� ��� ����
                KeyValue ��� ����� ������ ��� �������� ��������� ��� ���,
                �� ��� ����, ��� ��������� ��� �� ���.
  ����������: �� ������������� ��� �� ��� ������ Root �� ������� ��� ���� ���.
*/
{
  BinTreePointer
      n,          //������� ���� ����� ��� �������� ��� ���� KeyValue *)
      Parent,     // ������� ��� n � ��� nNext
      nNext,      // ����������������� �������� ��� n
      SubTree;    // ������� ���� ��������� ��� n
  boolean Found;  // TRUE AN TO �������� KeyValue EINAI ������� ��� ��� *)

  BSTSearch2(*Root, KeyValue, &Found, &n, &Parent);
  if (!Found)
    printf("TO STOIXEIO DEN EINAI STO DDA\n");
  else {
    if (n->LChild != NULL && n->RChild != NULL) {  // ������ ���� �������� �� ��� ������
      //���� ��� ���������������� ������� ��� ��� ������ ���
      nNext = n->RChild;
      Parent = n;
      while (nNext->LChild != NULL)  //* DIASXISH PROS TA ARISTERA *)
      {
        Parent = nNext;
        nNext = nNext->LChild;
      }
      /* ��������� ��� ������������ ��� nNext ���� n ���
                ������ ��� n ���� �� ������� ���� ������� */
      n->Data = nNext->Data;
      n = nNext;
    }  //����������� �� ��� ��������� ��� � ������ ���� �� ���� 1 �����
    SubTree = n->LChild;
    if (SubTree == NULL)
      SubTree = n->RChild;
    if (Parent == NULL)  //* 8A DIAGRAFEI H RIZA *)
      *Root = SubTree;
    else if (Parent->LChild == n)
      Parent->LChild = SubTree;
    else
      Parent->RChild = SubTree;
    free(n);
  }
}

void InorderTraversal(BinTreePointer Root)
/* �������:    ��� ������� ������ �� �� ������ Root �� ������� ���� ���� ���.
   ����������: ������� ���������������� �������� ��� �������� ������� ���
                ������������� ���� ����� ������� ��� ����.
   ���������: �� ����������� ��� ������, ��� ��������� ��� �� ����� ��� ������������
*/
{
  if (Root != NULL) {
    InorderTraversal(Root->LChild);
    printf("%d ", Root->Data);
    InorderTraversal(Root->RChild);
  }
}

/* new functions ------------------------------------------------------------*/

BinTreeElementType MinBSTValue(BinTreePointer Root) {
  BinTreePointer current = Root;

  if (current == NULL) {
    return -1;
  }

  while (current->LChild != NULL) {
    current = current->LChild;
  }
  return current->Data;
}

BinTreeElementType MaxBSTValue(BinTreePointer Root) {
  BinTreePointer current = Root;

  if (current == NULL) {
    return -1;
  }

  while (current->RChild != NULL) {
    current = current->RChild;
  }
  return current->Data;
}

/* main function ------------------------------------------------------------*/

int main(void) {
  BinTreePointer ARoot, BRoot;
  BinTreeElementType AnItem;
  boolean Found;
  BinTreeElementType min1, min2;
  BinTreeElementType max1, max2;

  CreateBST(&ARoot);
  CreateBST(&BRoot);

  do {
    printf("Dose enan thetiko akeraio:");
    scanf(" %d", &AnItem);
    if (AnItem != -1) {
      if (AnItem % 2 != 0) {
        BSTInsert(&ARoot, AnItem);
      } else {
        BSTInsert(&BRoot, AnItem);
      }
    }
  } while (AnItem != -1);

  //InorderTraversal(ARoot);
  //printf("\n");
  //InorderTraversal(BRoot);
  //printf("\n");

  min1 = MinBSTValue(ARoot);
  max1 = MaxBSTValue(ARoot);

  min2 = MinBSTValue(BRoot);
  max2 = MaxBSTValue(BRoot);

  printf("H mikroteri timi toy DDA twn perittvn arithmwn einai:%d\n", min1);
  printf("H megalyteri timi toy DDA twn perittvn arithmwn einai:%d\n", max1);

  printf("H mikroteri timi toy DDA twn artiwn arithmwn einai:%d\n", min2);
  printf("H megalyteri timi toy DDA twn artiwn arithmwn einai:%d\n", max2);
}