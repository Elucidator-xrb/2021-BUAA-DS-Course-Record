#include<stdio.h>
#define WS 1
#define S 2
#define ES 3
#define E 4

char map[19][19];

int isin(int i,int j)
{
    return 0<=i && i<=18 && 0<=j && j<=18;
}

int judge(int row,int col,int dir)
{
    int i,j;
    int cnt;
    if(dir==WS)
    {
        if(isin(row-1,col+1) && map[row][col]==map[row-1][col+1])
            return 0;
        for(i=row,j=col,cnt=1;isin(i+1,j-1) && map[i+1][j-1]==map[i][j];i++,j--,cnt++);
        if(cnt==4 && isin(i+1,j-1) && map[i+1][j-1]==0)
            return 1;
        else
            return 0;
    }
    else if(dir==S)
    {
        if(isin(row-1,col) && map[row][col]==map[row-1][col])
            return 0;
        for(i=row,j=col,cnt=1;isin(i+1,j) && map[i+1][j]==map[i][j];i++,cnt++);
        if(cnt==4 && isin(i+1,j) && map[i+1][j]==0)
            return 1;
        else
            return 0;
    }
    else if(dir==ES)
    {
        if(isin(row-1,col-1) && map[row][col]==map[row-1][col-1])
            return 0;
        for(i=row,j=col,cnt=1;isin(i+1,j+1) && map[i+1][j+1]==map[i][j];i++,j++,cnt++);
        if(cnt==4 && isin(i+1,j+1) && !map[i+1][j+1])
            return 1;
        else
            return 0;
    }
    else if(dir==E)
    {
        if(isin(row,col-1) && map[row][col]==map[row][col-1])
            return 0;
        for(i=row,j=col,cnt=1;isin(i,j+1) && map[i][j+1]==map[i][j];j++,cnt++);
        if(cnt==4 && isin(i,j+1) && !map[i][j+1])
            return 1;
        else
            return 0;
    }
}

int main()
{
    int i,j,k=0;
    for(i=0;i<19;i++)
        for(j=0;j<19;j++)
            scanf("%d",&map[i][j]);

    for(i=0;i<19 && !k;i++)
    {
        for(j=0;j<19 && !k;j++)
        {
            if(map[i][j])
            {
                (judge(i,j,WS) || judge(i,j,S) ||
                 judge(i,j,ES) || judge(i,j,E) ) && (k=1);
            }
        }
    }

    if(!k) puts("No");
    else printf("%d:%d,%d",map[i-1][j-1],i,j);

    return 0;
}
