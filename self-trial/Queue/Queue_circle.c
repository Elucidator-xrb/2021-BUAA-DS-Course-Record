#include<stdio.h>
#define M 1000

typedef int QElemtype;
int front,rear;
QElemtype queue[M];


//ѭ�����еĲ���
int addQueue(QElemtype queue[],int front,int &rear, QElemtype item) //���ҵ�C++д��
{
    if((rear+1)%M==front) return 0; /* ���������������ʧ�� */
    else
    {
        rear=(rear+1)%M;
        queue[rear]=item;
        return 1;
    }
}

//ѭ�����е�ɾ��
int delQueue(QElemtype queue[],int &front,int rear, QElemtype &item) //�۲�&��λ��
{
    if(front==rear) return 0;
    else
    {
        front=(front+1)%M;
        item=queue[front];
        return 1;
    }
}
