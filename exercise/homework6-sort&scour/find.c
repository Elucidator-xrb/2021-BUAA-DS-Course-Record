#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define HashNum 3001
#define MULT 37

char wordslist[4000][25];
int num;

typedef struct node
{
    char word[25];
    struct node *link;
} LNode, *Linklist;

Linklist HT[HashNum];

unsigned int hash(char *str);
void search(char aim[]);
void binSearch(char aim[]);
void indexSearch(char aim[]);
void hashSearch(char aim[]);

int main()
{
    FILE *fp;
    char aim[25];
    int i=0,opt;
    fp=fopen("dictionary3000.txt","r");
    while(fgets(wordslist[i],25,fp)!=NULL)
    {
        wordslist[i][strlen(wordslist[i])-2]=0;//在judge上，文件每行结尾是\r\n,所以是-2而不是-1；本地只有\n
        i++;
    }
    num=i-1;    //for(i=0;i<strlen(wordslist[1]);i++)printf("%d ",wordslist[1][i]);
    scanf("%s%d",aim,&opt);
    switch(opt)
    {
    case 1:search(aim);break;
    case 2:binSearch(aim);break;
    case 3:indexSearch(aim);break;
    case 4:hashSearch(aim);break;
    }

    fclose(fp);
    return 0;
}

void search(char aim[])
{
    int i;
    for(i=0;i<num;i++)
    {//if(aim[0]==wordslist[i][0]) printf("%s:%d\n",wordslist[i],strcmp(aim,wordslist[i]));
        if(strcmp(aim,wordslist[i])==0)
        {
            printf("1 %d",i+1);
            return;
        }
        else if(strcmp(aim,wordslist[i])<0)
        {
            i++;
            break;
        }
    }
    printf("0 %d",i);
    return;
}

void binSearch(char aim[])
{
    int cnt=0;
    int low=0,high=num,mid;
    while(low<=high)
    {
        cnt++;
        mid=(low+high)/2;
        if(strcmp(aim,wordslist[mid])==0)
        {
            printf("1 %d",cnt);
            return;
        }
        else if(strcmp(aim,wordslist[mid])>0) low=mid+1;
        else high=mid-1;
    }
    printf("0 %d",cnt);
    return;
}

void indexSearch(char aim[])
{
    int index[27];
    int i,cur_alpha;
    for(i=1;i<=26;i++) index[i]=-1;
    for(i=0;i<num;i++)
    {
        cur_alpha=wordslist[i][0]-96;
        if(index[cur_alpha]==-1) index[cur_alpha]=i;
    }
    index[27]=num;//（如果有）z后一个字母起始位置
    for(i=26;i>1;i--)//处理索引无内容情况
        if(index[i]==-1) index[i]=index[i+1];
    //构建索引表

    int key=aim[0]-96;
    int low=index[key],high=index[key+1]-1;
    int cnt=0,mid;

    while(low<=high)
    {
        cnt++;
        mid=(low+high)/2;
        if(strcmp(aim,wordslist[mid])==0)
        {
            printf("1 %d",cnt);
            return;
        }
        else if(strcmp(aim,wordslist[mid])>0) low=mid+1;
        else high=mid-1;
    }
    printf("0 %d",cnt);
    return;
}

unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str;*p!='\0';p++) h=MULT*h+*p;
    return h % HashNum;
}

void hashSearch(char aim[])
{
    int i;
    unsigned int d;
    Linklist p,q,pre;

    for(i=0;i<num;i++)
    {
        p=(Linklist)malloc(sizeof(LNode));
        strcpy(p->word,wordslist[i]);
        p->link=NULL;

        d=hash(wordslist[i]);
        if(HT[d]==NULL || strcmp(HT[d]->word,p->word)>0)
            p->link=HT[d],
            HT[d]=p;
        else
        {
            q=HT[d];
            while(q!=NULL && strcmp(q->word,p->word)<0)
            {
                pre=q;
                q=q->link;
            }
            p->link=q;
            pre->link=p;
        }
    }//构建哈希表

    unsigned int key=hash(aim);
    int cnt=0;
    p=HT[key];
    while(p!=NULL)
    {
        cnt++;
        if(strcmp(aim,p->word)==0)
        {
            printf("1 %d",cnt);
            return;
        }
        else if(strcmp(aim,p->word)<0) break;
        p=p->link;
    }
    printf("0 %d",cnt);
    return;
}
