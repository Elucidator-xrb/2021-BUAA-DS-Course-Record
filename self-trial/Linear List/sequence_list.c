#include<stdio.h>

//顺序表基本操作
typedef int ElemType;

void insertList(ElemType A[],int &size,int i,ElemType item);
void deleteList(ElemType A[],int &size,int i);
int locateItem(ElemType A[],int size,ElemType item);
void purgeSame(ElemType A[],int &size);
void deleteItem(ElemType a[],int &size,ElemType item);
