#include<stdio.h>
#define HashMax 100
#define Empty -1

typedef int Hashlist[HashMax]; //对数组使用typedef

Hashlist HT;

//1.插入（生成hashtable）,哈希生成函数 H(key)  + 线性再散列
int hashInsert(int m,int key)
{
    int i,d;
    d=i=H(key);
    while(HT[d]!=Empty && HT[d]!=key) /* HT不为空且不是自己（是自己说明已存入）*/
    {
        d=(d+1)%m;
        if(d==i) return -1; /* 转了一圈回到头来，说明表已满 */
    }
    if(HT[d]!=key) HT[d]=key;
    return d;
}

//2.查找 + 二次再散列
int hashSearch(int m,int key)
{
    int i,d,di=1;
    d=i=H(key);
    while(HT[d]!=Empty && HT[d]!=key)
    {
        d=(i+di*di++)%M;
        if(d==i) return -1;
    }
    if(HT[d]==k) return d;
    return -1;
}

//3.删除 + 链式地址法
