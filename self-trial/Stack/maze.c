#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MaxN 100
#define MaxMN 10000

void seekPath(int Maze[][MaxN],int m,int n)
{
    int stack[MaxMN][3],top=0;
    int move[8][2]={ {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
    int i,j,k; //��¼��ǰ״̬��Ϣ
    int g,h;   //�Ե�ǰ״̬Ϊ�������ж����룬���Ϸ����������ǰ״̬

    stack[0][0]=1;
    stack[0][1]=1;
    stack[0][2]=1; //�����״����򶫱��߲�ͨ�����ݣ�����ѭ�����趨
    Maze[1][1]=2;
    while(top>=0)
    {
        i=stack[top][0];
        j=stack[top][1];
        k=stack[top--][2]+1; //�߷�ʧ�ܣ���ջ�����ϴ�״̬���߷��������߷��ı�(+1)

        while(k<8)
        {
            g=i+move[k][0];
            h=j+move[k][1]; //�ƶ�

            if(g==m-2 && h==n-2 && Maze[g][h]==0)
            {
                printf("Find the path:\n");
                for(int l=0;l<=top;l++) printf("(%d,%d)->",stack[l][0],stack[l][1]);
                printf("(%d,%d)->(%d,%d)\n",i,j,g,h); //��ʱֻ�Ǽ���״̬��(g,h)����ջ�У���ʱ��ǰ״̬�ѵ�����(i,j)����ջ��
                return;
            }
            else if(Maze[g][h]==0)
            {
                Maze[g][h]=2;
                stack[++top][0]=i;
                stack[top][1]=j;
                stack[top][2]=k; //���߷��Ϸ�����ջ��¼
                i=g, j=h, k=0; // ���µ�ǰ״̬
            }

            k++;  //���߷��Ƿ���������һ�ж�
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

    for(i=0;i<m;i++) //��ӡ������Թ�����
    {
        for(j=0;j<n;j++) printf("%d ",Maze[i][j]);
        puts("");
    }


    seekPath(Maze,m,n);
    return 0;
}
