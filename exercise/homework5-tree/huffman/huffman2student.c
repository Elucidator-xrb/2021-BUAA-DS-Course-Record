//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ;
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
int Step=0;						//实验步骤
FILE *Src, *Obj;

void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤

	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果

	fclose(Src);
	fclose(Obj);

    return 0;
}

//【实验步骤1】开始

void statCount()
{
    char ch;
    Ccount[0]=1;
    while((ch=fgetc(Src))!=EOF)
        if(ch!='\n') Ccount[ch]++;
    return;
}

//【实验步骤1】结束

//【实验步骤2】开始

typedef struct node{
    struct tnode *root;
    struct node *link;
} LNode, *Linklist;
Linklist Forest;

void insertInOrder(struct tnode* tmp)
{
    Linklist p=Forest,q,pre;
    q=(Linklist)malloc(sizeof(LNode));
    q->root=tmp;q->link=NULL;

    if(Forest==NULL ||
       tmp->weight  < p->root->weight ||
       tmp->weight == p->root->weight && tmp->c!=-1 && tmp->c < p->root->c)
       q->link=Forest,
       Forest=q;
    else
    {
        p=Forest;
        while(p!=NULL &&
              (tmp->weight  > p->root->weight ||
               tmp->weight == p->root->weight && tmp->c==-1 ||
               tmp->weight == p->root->weight && tmp->c!=-1 && tmp->c >p->root->c) )
        {
            pre=p;
            p=p->link;
        }
        q->link=p;
        pre->link=q;
    }
}

void createHTree()
{
    struct tnode *p;
    int i;

    for(i=0;i<128;i++)
    {
        if(Ccount[i]>0)
        {
            p=(struct tnode*)malloc(sizeof(struct tnode));
            p->c=i;p->weight=Ccount[i];
            p->left=p->right=NULL;
            insertInOrder(p);
        }
    }
    while(Forest->link!=NULL)
    {
        p=(struct tnode*)malloc(sizeof(struct tnode));
        Linklist pp=Forest,qq=Forest->link;
        p->c=-1;
        p->weight = pp->root->weight + qq->root->weight;
        p->left=pp->root;
        p->right=qq->root;

        Forest=qq->link;
        free(pp);free(qq);

        insertInOrder(p);
    }
    Root=Forest->root;
}

//【实验步骤2】结束

//【实验步骤3】开始

char path[BUFSIZ];
int len=-1;

void encoded(struct tnode* p)/* 对遍历的递归有了更好的理解：之前递归带栈/数组应该可以实现了 */
{
    if(p!=NULL)
    {
        if(p->left==NULL && p->right==NULL)
        {
            path[len+1]='\0';
            strcpy(HCode[p->c],path);
        }
        path[++len]='0';
        encoded(p->left);
        path[++len]='1';
        encoded(p->right);
    }
    len--;
}

void makeHCode() {encoded(Root);}

//【实验步骤3】结束

//【实验步骤4】开始
char Hstr[2000];//数组越界了600，int型hc却可以显示正确结果
void atoHZIP()
{
    char c;
    int i,hc;//用char型的hc会因为符号位混淆而出错，用unsigned比较好
    rewind(Src);
    while((c=fgetc(Src))!=EOF)
        strcat(Hstr,HCode[c]);
    strcat(Hstr,HCode[0]);
    for(i=0;Hstr[i]!='\0';i++)
    {
        hc=(hc<<1)|(Hstr[i]-48);
        if((i+1)%8==0)
        {
            fputc(hc,Obj);
            printf("%x",hc);
            hc=0;
        }
    }
    if(i%8!=0)
    {
        hc<<=(8-i%8);
        fputc(hc,Obj);
        printf("%x",hc);
    }
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL))
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;

	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
}

void print4()
{
	long int in_size, out_size;

	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
