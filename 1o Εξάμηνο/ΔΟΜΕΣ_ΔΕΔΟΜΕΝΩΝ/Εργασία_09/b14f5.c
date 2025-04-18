/*******************************************************************************
 * Filename: a14f5.c
 * data structures (AIC205)
 * ics23088
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char name[21];
  char phone[11];
  int code;
} BinTreeElementType;

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
int BuildBST(char *filename, BinTreePointer *ARoot);
void printTeachers(BinTreePointer ARoot);

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
    if (strcmp(Item.name, LocPtr->Data.name) < 0)
      LocPtr = LocPtr->LChild;
    else if (strcmp(Item.name, LocPtr->Data.name) > 0)
      LocPtr = LocPtr->RChild;
    else
      Found = TRUE;
  }
  if (Found)
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
  else {
    LocPtr = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    strcpy(LocPtr->Data.name, Item.name);
    strcpy(LocPtr->Data.phone, Item.phone);
    LocPtr->Data.code = Item.code;
    LocPtr->LChild = NULL;
    LocPtr->RChild = NULL;
    if (Parent == NULL)
      *Root = LocPtr;
    else if (strcmp(Item.name, Parent->Data.name) < 0)
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
    if (strcmp(KeyValue.name, (*LocPtr)->Data.name) < 0)
      (*LocPtr) = (*LocPtr)->LChild;
    else if (strcmp(KeyValue.name, (*LocPtr)->Data.name) > 0)
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
    if (strcmp(KeyValue.name, (*LocPtr)->Data.name) < 0) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->LChild;
    } else if (strcmp(KeyValue.name, (*LocPtr)->Data.name) > 0) {
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
      n,          // ������� ���� ����� ��� �������� ��� ���� KeyValue *)
      Parent,     // ������� ��� n � ��� nNext
      nNext,      // ����������������� �������� ��� n
      SubTree;    // ������� ���� ��������� ��� n
  boolean Found;  // TRUE AN TO �������� KeyValue EINAI ������� ��� ��� *)

  BSTSearch2(*Root, KeyValue, &Found, &n, &Parent);
  if (!Found)
    printf("TO STOIXEIO DEN EINAI STO DDA\n");
  else {
    if (n->LChild != NULL && n->RChild != NULL) {  // ������ ���� �������� �� ��� ������
      // ���� ��� ���������������� ������� ��� ��� ������ ���
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
    }  // ����������� �� ��� ��������� ��� � ������ ���� �� ���� 1 �����
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
    printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
    InorderTraversal(Root->RChild);
  }
}

/* new functions */

int BuildBST(char *filename, BinTreePointer *ARoot) {
  FILE *fp;
  char surname[21];
  char phone[11];
  int code;
  int nscan;
  char termch;
  boolean stop = FALSE;
  BinTreeElementType ARec;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  while (TRUE) {
    nscan = fscanf(fp, "%20[^,], %10[^,],%d%c", surname, phone, &code, &termch);
    if (nscan == EOF) break;
    if (nscan != 4 || termch != '\n') {
      printf("Improper file format\n");
      return 1;
      stop = TRUE;
      break;
    } else {
      strcpy(ARec.name, surname);
      strcpy(ARec.phone, phone);
      ARec.code = code;
      BSTInsert(ARoot, ARec);
    }
  }
  fclose(fp);
  return 0;
}

void printTeachers(BinTreePointer ARoot) {
  printf("Print teachers data\n");
  InorderTraversal(ARoot);
  printf("\n");
}


void BSTSearchBySubject(BinTreePointer Root,int code )
{
  if (Root != NULL) {
    BSTSearchBySubject(Root->LChild,code);
    if (Root->Data.code == code) {
      printf("%s, %s, %d \n", Root->Data.name, Root->Data.phone, Root->Data.code);
    }
    BSTSearchBySubject(Root->RChild,code);
  }
}

int main(void) {
  int res;
  int i;
  boolean found;

  BinTreePointer ARoot;
  BinTreeElementType ARec;
  BinTreePointer LocPtr;

  // 1
  CreateBST(&ARoot);

  res = BuildBST("I14F5.TXT", &ARoot);
  if (res != 0) {
    return res;
  }

  // 2
  printTeachers(ARoot);

  // 3
  for (i = 1; i <= 2; i++) {
    printf("Give teacher full name: ");
    scanf("%[^\n]", ARec.name);
    printf("Give teacher phone number: ");
    scanf("%s", ARec.phone);
    printf("Give teacher code: ");
    scanf("%d", &ARec.code);getchar();
    BSTInsert(&ARoot, ARec);
    printf("\n");
  }

  // 4
  printf("Give teacher full name to search: ");
  scanf("%[^\n]", ARec.name);
  BSTSearch(ARoot,ARec,&found,&LocPtr);
  if(found==TRUE) {
    printf("%s, %s, %d\n",LocPtr->Data.name,LocPtr->Data.phone,LocPtr->Data.code);
  }

  // 5
  printf("\nGive code to search: ");
  scanf("%d", &ARec.code);getchar();
  BSTSearchBySubject(ARoot,ARec.code);

  // 6
  printf("\nGive teacher full name to delete: ");
  scanf("%[^\n]",ARec.name);
  BSTDelete(&ARoot,ARec);

  // 7
  printf("\n");
  printTeachers(ARoot);
}
