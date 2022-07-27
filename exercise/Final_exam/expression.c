#include<stdio.h>
#include<string.h>
#include<ctype.h>

char buf[BUFSIZ];
char prior[48];

void clearSpace();
void In_to_Post();
void Post_to_In();

int main()
{
    int opt;
    scanf("%d\n",&opt);gets(buf); //注意缓冲区中的\n

    switch(opt)
    {
        case 1:In_to_Post();break;
        case 2:Post_to_In();break;
        case 3:Post_to_Tree();break;
    }
    return 0;
}

void clearSpace()
{
    int i,j;
    for(i=j=0;buf[i]!='\0';i++)
        if(buf[i]!=' ') buf[j++]=buf[i];
    buf[j]='\0';
    return;
}

void In_to_Post()
{
    prior['+']=prior['-']=1;
    prior['*']=prior['/']=2;
    prior['(']=prior[')']=2;
    int tmp=0,isnum=0;
    int stack[BUFSIZ],top=-1;

    clearSpace();
    for(int i=0;buf[i]!='=';i++)
    {
        if(isdigit(buf[i]))//读入数
        {
            tmp=(tmp<<1)+(tmp<<3)+(buf[i]&15);
            isnum=1;
        }
        else /* 所有printf的地方，可以改成其他操作，以便完成要求 */
        {
            if(isnum) printf("%d ",tmp);
            tmp=isnum=0;//处理数字

            while(top>=0 && stack[top]!='(' &&
                   prior[ stack[top] ]>=prior[ buf[i] ])
                printf("%c ",stack[top--]); //正常弹栈
            if(buf[i]==')'){               //遇')'弹栈
                while(stack[top]!='(') printf("%c ",stack[top--]);
                top--;
            }
            else stack[++top]=buf[i];      //符号入栈
        }
    }
    if(isnum) printf("%d ",tmp);//最后一个数！！
    while(top>=0) printf("%c ",stack[top--]);
}

void Post_to_In()
{

}
