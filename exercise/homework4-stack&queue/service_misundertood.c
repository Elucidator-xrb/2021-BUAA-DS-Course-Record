#include<stdio.h>
#include<ctype.h>
#define M 500
/*  ������⣬��Ҫԭ������Ŀ̫����
1.������ʼ���������
2.����ǰ��λ��ӽ��ܷ���
3.�ж�ƽ��������
    a������7����������������Ϊ>6�����������ڣ�1����ӣ��ٴμ���ƽ��������
    b���ظ�������ֱ��<7�򴰿���Ϊ5
4.�ȴ�ʱ�䣬����Ԫ�صȴ�����+1
5.ֱ���ӿ�
*/

int queue[M];
int front,rear;
int time[1000];

void doService() //2.3.4���Ĳ���
{
    int i,recept;
    for(i=0;i<3;i++)
    {
        if(front!=rear) front=(front+1)%M;
        else break;
    }

    recept=3;
    while( (rear+M-front)%M > 6*recept && recept<5 )
    {
        front=(front+1)%M;
        recept++;
    }

    for(i=1;i<=(rear+M-front)%M;i++)
    {
        time[ queue[(front+i)%M] ]++;
    }
}

int main()
{
    int T,num;
    int i,person=0;
    scanf("%d",&T);
    while(T--) //ģ�����������ʼ��һ������
    {
        scanf("%d",&num);
        for(i=0;i<num;i++)
        {
            if((rear+1)%M==front) return -1;
            else
            {
                rear=(rear+1)%M;
                queue[rear]=++person;
            }
        }
        doService();
    }
    while(front!=rear) doService();
    for(i=1;i<=person;i++) printf("%d : %d\n",i,time[i]);

    return 0;
}


