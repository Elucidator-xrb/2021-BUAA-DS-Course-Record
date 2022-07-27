#include<stdio.h>
#define M 1000

typedef int QElemtype;
int front,rear;
QElemtype queue[M];


//循环队列的插入
int addQueue(QElemtype queue[],int front,int &rear, QElemtype item) //苟且的C++写法
{
    if((rear+1)%M==front) return 0; /* 队列真溢出，插入失败 */
    else
    {
        rear=(rear+1)%M;
        queue[rear]=item;
        return 1;
    }
}

//循环队列的删除
int delQueue(QElemtype queue[],int &front,int rear, QElemtype &item) //观察&的位置
{
    if(front==rear) return 0;
    else
    {
        front=(front+1)%M;
        item=queue[front];
        return 1;
    }
}
