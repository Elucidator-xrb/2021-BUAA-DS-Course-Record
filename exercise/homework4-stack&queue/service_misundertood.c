#include<stdio.h>
#include<ctype.h>
#define M 500
/*  错误理解，主要原因是题目太拉！
1.周期伊始，人来入队
2.队中前三位离队接受服务
3.判断平均人数：
    a）若≥7（根据样例，调整为>6）则增开窗口，1人离队，再次计算平均人数；
    b）重复操作，直至<7或窗口数为5
4.等待时间，队中元素等待周期+1
5.直至队空
*/

int queue[M];
int front,rear;
int time[1000];

void doService() //2.3.4步的操作
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
    while(T--) //模拟服务周期伊始，一波人来
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


