#include<stdio.h>
#include<stdlib.h>
#define MaxN 100

typedef int SElemType;
SElemType Stack[MaxN];
int top;  /* top��ָ��ǰ�Ѵ���Ԫ�ص� */

void initial(int *top) { *top=-1; }

int isEmpty(int top) { return top==-1; }

int isFull(int top)  { return top==M-1; }

SElemType getTop(SElemType stack[],int top)
{
    if(isEmpty(top)) return -1;
    else return stack[top];
}

int push(SElemType stack[],int top,SElemType item)
{
    if(isFull(top)) return -1;
    else
    {
        stack[++top]=item;
        return 1;
    }
}

SElemType pop(SElemType stack[],int top)
{
    if(isEmpty(top)) return -1;
    else return stack[top--];
}

//�����ջ���������ռ� -> ���������ջ���������ռ� �о�ʮ�ּ���

