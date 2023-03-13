#include <stdio.h>
#define StackLimit 8   // �� ���� �������� ��� �������, ���������� ��� �� 50


typedef int StackElementType;   // � ����� ��� ���������  ��� �������
//���������� ����� int
typedef struct
{
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum
{
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void CreateStack(StackType *Stack)
/* ����������: ���������� ��� ���� ������.
   ����������: ���� ������.*
*/
{
    Stack -> Top = -1;
    // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ����.
   ����������: True �� � Stack ����� ����, False �����������
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ������.
   ����������: True �� � Stack ����� ������, False �����������
*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* �������: ��� ������ Stack ��� ��� �������� Item.
   ����������: ������� �� �������� Item ���� ������ Stack �� � Stack ��� ����� ������.
   ����������: ��� ������������� Stack.
   ������: ������ ������� �������, �� � ������ Stack ����� ������
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* �������: ��� ������ Stack.
   ����������: ��������� �� �������� Item ��� ��� ������ ��� ������� �� � ������ ��� ����� ����.
   ����������: �� �������� Item ��� ��� ������������� Stack.
   ������:  ������ ����� ������� �� � Stack ����� ����
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...\n");
}

void TraverseStack(StackType Stack)
{
    int i;
    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}



StackElementType minElement(StackType *Stack);
StackElementType maxElement(StackType *Stack);

int main()
{


    StackType S;
    StackElementType item;

    int i;

    CreateStack(&S);
    for(i=0; i<StackLimit; i++) {
        scanf("%d",&item);
        Push(&S,item);
    }
    TraverseStack(S);



    StackElementType min1 = minElement(&S);
    StackElementType max1 = maxElement(&S);

    printf("Min: %d\n",min1);
    printf("Max: %d\n",max1);

    TraverseStack(S);

    return 0;


}


StackElementType minElement(StackType *Stack)
{
    /*��������: ��������������� ��� ���� ��������� ������*/
    StackElementType min, item;
    StackType tempS;

    CreateStack(&tempS);

    //Pop(&(*Stack),(&min);
    Pop(&(*Stack),&min);

    Push(&tempS, min);
    //������� �� ������ Stack ��� ������ tempS ��� ��������� �� ��������� ��������
    while(!EmptyStack(*Stack)) {
        Pop(Stack, &item);
        Push(&tempS, item);


        if(min>item)
            min = item;
    }
//������� ��� tempS ��� ������ ���� Stack ���� �� �������� ��� ��� ����� ��� �� min
    while(!EmptyStack(tempS)) {
        Pop(&tempS, &item);
        if (item != min)
            Push(Stack, item);
    }
    return min;
}
StackElementType maxElement(StackType *Stack)
{
    StackElementType max, item;
    StackType tempS;
    CreateStack(&tempS);

    Pop(&(*Stack),&max);

    Push(&tempS, max);


//������� �� ������ Stack ��� ������ tempS ��� ��������� �� ���������� ��������
    while(!EmptyStack(*Stack)){

        Pop(Stack, &item);
        Push(&tempS, item);
        if(max<item)
            max = item;
    }

//������� ��� tempS ��� ������ ���� Stack ���� �� �������� ��� ��� ����� ��� �� max
          while(!EmptyStack(tempS)){
            Pop(&tempS,&item);
            if (item != max)
                Push(Stack,item);
          }
        return max;

    }






