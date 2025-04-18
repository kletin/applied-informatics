/*******************************************************************************
* Filename: a6f5.c
* data structures (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int BSTDepth(BinTreePointer Root);

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

/* new functions */

int BSTDepth(BinTreePointer Root)
{
  if (Root==NULL) {
    return 0;
  } 
  int LDepth,RDepth;

  LDepth = BSTDepth(Root->LChild);
  RDepth = BSTDepth(Root->RChild);

 if (LDepth > RDepth)
    return LDepth + 1;
  else
    return RDepth + 1;
}

int main(void) {
  BinTreePointer ARoot;
  char *word = "PROCEDURE";
  int i,depth;

  CreateBST(&ARoot);
  for (i = 0; i < strlen(word); i++) {
    BSTInsert(&ARoot, word[i]);
  }

  depth = BSTDepth(ARoot);
  printf("To vathos toy DDA einai: %d\n",depth);
}

 