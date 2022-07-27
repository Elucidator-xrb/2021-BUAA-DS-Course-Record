#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MaxN 100
#define MaxMN 10000

void seekPath(int Maze[][MaxN],int m,int n)
{
    int stack[MaxMN][3],top=0;
    int move[8][2]={ {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
    int i,j,k; //记录当前状态信息
    int g,h;   //以当前状态为基础的行动设想，若合法则更新至当前状态

    stack[0][0]=1;
    stack[0][1]=1;
    stack[0][2]=1; //假设首次是向东北走不通而回溯，契合循环的设定
    Maze[1][1]=2;
    while(top>=0)
    {
        i=stack[top][0];
        j=stack[top][1];
        k=stack[top--][2]+1; //走法失败，弹栈回溯上次状态和走法，并将走法改变(+1)

        while(k<8)
        {
            g=i+move[k][0];
            h=j+move[k][1]; //移动

            if(g==m-2 && h==n-2 && Maze[g][h]==0)
            {
                printf("Find the path:\n");
                for(int l=0;l<=top;l++) printf("(%d,%d)->",stack[l][0],stack[l][1]);
                printf("(%d,%d)->(%d,%d)\n",i,j,g,h); //此时只是假设状态，(g,h)不在栈中；此时当前状态已弹出，(i,j)不在栈中
                return;
            }
            else if(Maze[g][h]==0)
            {
                Maze[g][h]=2;
                stack[++top][0]=i;
                stack[top][1]=j;
                stack[top][2]=k; //新走法合法，入栈记录
                i=g, j=h, k=0; // 更新当前状态
            }

            k++;  //新走法非法，尝试下一行动
        }

    }
    printf("Fail to find the path!\n");
    return;
}

int main()
{
    int Maze[MaxN][MaxN];
    int len;
    int i,j=0,k,m=0,n=0;
    char buf[BUFSIZ];
    FILE *fp;

    fp=fopen("Maze.txt","r");
    while(fgets(buf,BUFSIZ-1,fp)!=NULL)
    {
        k=0, len=strlen(buf);
        for(i=0;i<len;i++)
            if(isdigit(buf[i])) Maze[j][k++]=buf[i]-48;
        j++;
    }
    m=j, n=k;
    fclose(fp);

    for(i=0;i<m;i++) //打印读入的迷宫矩阵
    {
        for(j=0;j<n;j++) printf("%d ",Maze[i][j]);
        puts("");
    }


    seekPath(Maze,m,n);
    return 0;
}
