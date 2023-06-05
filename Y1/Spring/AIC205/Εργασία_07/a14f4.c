/*******************************************************************************
* Filename: a14tf4.c
* data structures (AIC205)
* ics23088
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char StackElementType;
                              
typedef struct StackNode *StackPointer;
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void TraverseStack(StackPointer Stack);


void CreateStack(StackPointer *Stack)
{
	*Stack = NULL;
}

boolean EmptyStack(StackPointer Stack)
{
	return (Stack==NULL);
}

void Push(StackPointer *Stack, StackElementType Item)
{
	StackPointer TempPtr;

    TempPtr= (StackPointer)malloc(sizeof(struct StackNode));
    TempPtr->Data = Item; 
    TempPtr->Next = *Stack;
    *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item)
{
    StackPointer TempPtr;
    
    if (EmptyStack(*Stack)) {
   	    //printf("EMPTY Stack\n");
    }
   else
   {
        TempPtr = *Stack;
        *Item=TempPtr->Data;
        *Stack = TempPtr->Next;     
        free(TempPtr);
    }
}

void TraverseStack(StackPointer Stack) {
  StackPointer CurrPtr;

  if (EmptyStack(Stack)) {
    //printf("EMPTY Stack\n");
  } else {
    CurrPtr = Stack;
    while (CurrPtr != NULL) {
      printf("%c ", CurrPtr->Data);
      CurrPtr = CurrPtr->Next;
    }
  }
  printf("\n");
}

/* main function ------------------------------------------------------------*/

int main(void) {


  StackPointer AStack;
  StackElementType AnItem;
  int i;
  char str[40];
  boolean found;
  StackElementType TopItem;

  /* Create Stack -----------------------------------------------------------*/

  CreateStack(&AStack);

  /* User Input -------------------------------------------------------------*/
  printf("EISAGETE MIA PARASTASI: ");
  scanf("%s",str);

  found=TRUE;

  for (i = 0; i <= strlen(str); i++) {
    if (str[i] == '{' || str[i] == '(' || str[i] == '[') {
      //printf("i=%d char=%c\n", i, str[i]);
      AnItem = str[i];
      Push(&AStack, AnItem);
    } else if (str[i] == '}' || str[i] == ')' || str[i] == ']') {
      if (EmptyStack(AStack)) {
        found = FALSE;
        break;
      } else {
        Pop(&AStack, &TopItem);
        if (TopItem == '(' && str[i] != ')') {
          found = FALSE;
          break;
        } else if (TopItem == '{' && str[i] != '}') {
          found = FALSE;
          break;
        } else if (TopItem == '[' && str[i] != ']') {
          found = FALSE;
          break;
        }
      }
    }
  }

  if (found==FALSE || !EmptyStack(AStack)) {
    printf("WRONG\n");
  }
  else {
    printf("CORRECT\n");
  }
}
