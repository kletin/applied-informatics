/*******************************************************************************
* Filename: a33f5.c
* data structures (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char BinTreeElementType; /*� ����� ��� ��������� ��� ���
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

typedef BinTreeNode StackElementType; /*� ����� ��� ��������� ��� �������
                                        ���������� ����� int */
typedef struct StackNode *StackPointer;
typedef struct StackNode {
  StackElementType Data;
  StackPointer Next;
} StackNode;

void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);

/* new function */
void NonRecTraversal(BinTreePointer Root);

/* bts functions ----------------------------------------------------------*/

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
    printf("%c ", Root->Data);
    InorderTraversal(Root->RChild);
  }
}

void BSTTraversal(BinTreePointer Root) {
  if (Root != NULL) {
    printf("%c ", Root->Data);
    if (Root->LChild) {
      printf("%c ", Root->LChild->Data);
    } else {
      printf("  ");
    }
    if (Root->RChild) {
      printf("%c ", Root->RChild->Data);
    } else {
      printf("  ");
    }
    printf("\n");
    BSTTraversal(Root->LChild);
    BSTTraversal(Root->RChild);
  }
}

/* stack functions ----------------------------------------------------------*/

void CreateStack(StackPointer *Stack)
/* ����������: ���������� ��� ���� ����������� ������. 
   ����������: ��� ���� ����������� ������, Stack  
*/
{
  *Stack = NULL;
}

boolean EmptyStack(StackPointer Stack)
/* �������:     ��� ����������� ������, Stack.
   ����������:  ������� �� � Stack ����� ����.
   ����������:  TRUE �� � ������ ����� ����, FALSE �����������
*/
{
  return (Stack == NULL);
}

void Push(StackPointer *Stack, StackElementType Item)
/* �������:    ��� ����������� ������ ��� � ������ ��� �������������� ��� ��� 
                ������ Stack ��� ��� �������� Item. 
   ����������: ������� ���� ������ ��� ������������ �������, �� �������� Item. 
   ����������: ��� ������������� ����������� ������ 
*/
{
  StackPointer TempPtr;

  TempPtr = (StackPointer)malloc(sizeof(struct StackNode));
  TempPtr->Data = Item;
  TempPtr->Next = *Stack;
  *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item)
/* �������:    ��� ����������� ������ ��� � ������ ��� �������������� ��� ��� ������ Stack. 
   ����������: ������� ��� ��� ������ ��� ������������ �������, 
                �� � ������ ��� ����� ����, �� �������� Item. 
   ����������: ��� ������������� ����������� ������ ��� �� �������� Item. 
   ������:     ������ ����� �������, �� � ����������� ������ ����� ���� 
*/
{
  StackPointer TempPtr;

  if (EmptyStack(*Stack)) {
    printf("EMPTY Stack\n");
  } else {
    TempPtr = *Stack;
    *Item = TempPtr->Data;
    *Stack = TempPtr->Next;
    free(TempPtr);
  }
}

/* new function ------------------------------------------------------------*/

void NonRecTraversal(BinTreePointer Root) {
  StackPointer TempStack;
  StackElementType AnItem;
  boolean done = FALSE;

  CreateStack(&TempStack);
  Push(&TempStack, *Root);

  while (!EmptyStack(TempStack)) {
    Pop(&TempStack, &AnItem);
    printf("%c ", AnItem.Data);
    if (AnItem.RChild != NULL) {
      Push(&TempStack, *AnItem.RChild);
    }
    if (AnItem.LChild != NULL) {
      Push(&TempStack, *AnItem.LChild);
    }
  }
}

/* main function ------------------------------------------------------------*/

int main(void) {
  BinTreePointer ARoot, BRoot;
  char *word = "ALGORITHM";
  int len = strlen(word);
  int i;

  CreateBST(&ARoot);
  CreateBST(&BRoot);

  for (i = 0; i < len; i++) {
    BSTInsert(&ARoot, word[i]);
    BSTInsert(&BRoot, word[len - 1 - i]);
  }

  NonRecTraversal(ARoot);
  printf("\n");
  NonRecTraversal(BRoot);
  printf("\n");
}