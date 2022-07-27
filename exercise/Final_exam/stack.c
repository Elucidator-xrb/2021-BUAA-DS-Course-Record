#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FunMax 110
#define UseMax 15
#define NameMax 25

char stack[210][NameMax];
int top=-1;

char fun[FunMax][UseMax][NameMax];
int funN;
int useN[FunMax];

void popIn();
void popOut();
void printFun();

int main()
{
    int opt;
    do{
        scanf("%d",&opt);
        if(opt==5) popIn();
        else if(opt==0) popOut();
    }while(top>-1);
    printFun();
    return 0;
}

void popIn()
{
    int i,j;
    char cur[NameMax];
    char par[NameMax];
    scanf("%s",cur);
    if(top>-1)//栈非空，增添调用关系
    {
        strcpy(par,stack[top]);
        for(i=0;i<funN;i++)
        {
            if(strcmp(par,fun[i][0])==0)
            {
                for(j=1;j<useN[i];j++)
                {
                    if(strcmp(cur,fun[i][j])==0)
                        break;
                }
                if(j==useN[i])strcpy(fun[i][ useN[i]++ ],cur);

                break;
            }
        }
    }
    strcpy(stack[++top],cur);//入栈
    for(i=0;i<funN;i++)
    {
        if(strcmp(cur,fun[i][0])==0)
            break;
    }
    if(i==funN)
    {
        strcpy(fun[funN++][0],cur); //增添函数列
        useN[funN-1]=1;
    }
    //printf("--[%s]\n",fun[funN-1][0]);
    return;
}

void popOut()
{
    if(top>-1) stack[top][0]='\0';
    top--;
}

void printFun()
{
    int i,j;
    for(i=0;i<funN;i++)
    {
        if(useN[i]>1)
        {
            printf("%s:",fun[i][0]);
            for(j=1;j<useN[i]-1;j++)
            {
                printf("%s;",fun[i][j]);
            }
            printf("%s\n",fun[i][ useN[i]-1 ]);
        }
    }
}
