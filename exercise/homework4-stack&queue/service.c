#include<stdio.h>
#define M 500

int queue[M];
int front,rear;
int time[1000];
int recept=3;

void checkAfter()
{
    int i;
    for(i=0;i<recept;i++)
    {
        if(front!=rear) front=(front+1)%M;
        else break;
    }
    while( recept>3 && (rear+M-front)%M < 7*recept ) recept--;
    for(i=1;i<=(rear+M-front)%M;i++)
        time[ queue[(front+i)%M] ]++;
}

int main()
{
    int T,num;
    int i,person=0;
    scanf("%d",&T);
    while(T--)
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
        while( recept<5 && (rear+M-front)%M >= 7*recept ) recept++;
        checkAfter();
    }
    while(front!=rear) checkAfter();
    for(i=1;i<=person;i++) printf("%d : %d\n",i,time[i]);

    return 0;
}
