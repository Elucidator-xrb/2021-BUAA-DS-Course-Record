#include<stdio.h>
#include<stdlib.h>
#define MaxNode 201

int value[MaxNode];
int par[MaxNode];
int lchild[MaxNode],rchild[MaxNode];
int height[MaxNode];
int sort[MaxNode/2][2];

int compar(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}

int main()
{
    int i,t,p;
    int j=0;

    scanf("%d",&t);
    scanf("%d",&value[1]);
    height[1]=1;
    for(i=2;i<=t;i++)
    {
        scanf("%d",&value[i]);
        p=1;
        while(1)
        {
            if(value[p]>value[i])
            {
                if(lchild[p]==0)
                {
                    lchild[p]=i;
                    par[i]=p;
                    height[i]=height[p]+1;
                    break;
                }
                p=lchild[p];
            }
            else
            {
                if(rchild[p]==0)
                {
                    rchild[p]=i;
                    par[i]=p;
                    height[i]=height[p]+1;
                    break;
                }
                p=rchild[p];
            }
        }
    }
    for(i=1;i<=t;i++)  //注意考虑只有根结点的情况，所以i从1开始
    {
        if(lchild[i]==0 && rchild[i]==0)
            sort[j][0]=value[i],
            sort[j++][1]=height[i];
    }
    qsort(sort,j,sizeof(sort[0]),compar);
    for(i=0;i<j;i++)
        printf("%d %d\n",sort[i][0],sort[i][1]);

    return 0;
}


