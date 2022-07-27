#include<stdio.h>

#define MAXN 100007

int fa[3*MAXN];/* 同层并查集中为同类，异层并查集中为食物链 */
/* 顺序为 x > x+N > x+2*N > x */
int N,K;

int read()
{
    char ch=getchar();
    int n=0;
    while(ch<48 || ch>57) getchar();
    while(48<=ch && ch<=57)
    {
        n=(n<<1)+(n<<3)+(ch&15); /* 好妙 */
        ch=getchar();
    }
    return n;
}

//inline int read(){//读入优化，可以加快数字的输入
//    char p=0;
//    int r=0,o=0;
//    for(;p<'0'||p>'9';o|=p=='-',p=getchar());
//    for(;p>='0'&&p<='9';r=(r<<1)+(r<<3)+(p^48),p=getchar());
//    return o?(~r)+1:r;
//}

int find(int x)
{
    return  (fa[x]==x) ? x : (fa[x]=find(fa[x])) ;
}

int main()
{
    int i,fakenum=0;
    int type,a,b;
    N=read();K=read();
    for(i=1;i<=3*N;i++) fa[i]=i; //初始化并查集

    while(K--)
    {
        type=read();a=read();b=read();
        if(a>N || b>N) fakenum++;
        else if(type==1) /* 同物种 */
        {
            if(find(a)==find(b+N) || find(a+N)==find(b)) //有异层并查集关系
                fakenum++;
            else //同层并查集相连
            {
                fa[find(a)]=find(b);
                fa[find(a+N)]=find(b+N);
                fa[find(a+2*N)]=find(b+2*N);
            }
        }
        else if(type==2) /* 捕食关系 */
        {
            if(find(a)==find(b) || find(b)==find(a+N)) //有同层并查集关系 或 反向捕食关系
                fakenum++;
            else//b被食者 合并到 a捕食者
            {
                fa[find(b+N)]=find(a);
                fa[find(b+2*N)]=find(a+N);
                fa[find(b)]=find(a+2*N);
            }
        }
    }
    printf("%d",fakenum);
    return 0;
}
