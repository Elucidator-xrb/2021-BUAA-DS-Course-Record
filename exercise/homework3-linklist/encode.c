#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    char ch;
    struct node *link;
} CNode, *CLinklist;

CLinklist list;
int flag[127];

void getKey(char *dest);//获取字串并去重,加入剩余项
void createList(char *key);//使用处理后字串构成循环链表
void getEncryptMethod(char *dest);//获得加密对照表
void doEncrypt(char *encrypt);//对文件加密

int main()
{
    int i;
    char key[96]={0}; /* 95个可见字符 */
    char encrypt[128]={0};
    getKey(key);
    createList(key);
    getEncryptMethod(encrypt);
    doEncrypt(encrypt);
    return 0;
}

void getKey(char *dest)
{
    int i,j;
    gets(dest);
    for(i=j=0;dest[i]!='\0';i++)
    {
        if(flag[dest[i]]==0)
        {
            flag[dest[i]]=1;
            dest[j++]=dest[i];
        }
    }
    for(i=32;i<=126;i++)
        if(flag[i]==0) dest[j++]=i;
    dest[j]='\0';
}

void createList(char *key)
{
    CLinklist p,r;
    int i,len;
    len=strlen(key);
    for(i=0;i<len;i++)
    {
        p=(CLinklist)malloc(sizeof(CNode));
        p->ch=key[i];
        p->link=NULL;
        if(list==NULL) list=p;
        else r->link=p;
        r=p;
    }
    r->link=list;
}

void getEncryptMethod(char *dest)
{
    char head=list->ch;
    CLinklist p=list,pre=list->link;
    char tmp;
    int i;
    while(pre->link!=list) pre=pre->link; //pre就位

    while(p->link!=p)
    {
        tmp=p->ch;
        pre->link=p->link;
        p=pre->link;
        for(i=1;i<tmp;i++)
        {
            pre=p;
            p=p->link;
        }
        dest[tmp]=p->ch;
    }
    dest[p->ch]=head;
}

void doEncrypt(char *encrypt)
{
    FILE *fpi,*fpo;
    char c;
    fpi=fopen("in.txt","r");
    fpo=fopen("in_crpyt.txt","w");
    while((c=fgetc(fpi))!=EOF)
    {
        if(32<=c && c<=126) c=encrypt[c];
        fputc(c,fpo);
    }
    fclose(fpi);
    fclose(fpo);
}
