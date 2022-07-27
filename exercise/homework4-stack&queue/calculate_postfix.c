#include<stdio.h>
#include<string.h>
#include<ctype.h>

int stack[BUFSIZ],top=-1;
int postfix[BUFSIZ],p=0;
int w[48];

void in_to_post(char *equ) //很多注意点
{
    int i,tmp=0,iscal=0;
    w[43]=w[45]=1,w[42]=w[47]=w[37]=2,w[40]=w[41]=3;

    for(i=0;equ[i]!='=';i++)
    {
        if(isdigit(equ[i])) tmp=(tmp<<1)+(tmp<<3)+(equ[i]&15),iscal=1;
        else
        {
            if(iscal)postfix[p++]=tmp; //只有取过数字才能存入,iscal谓此
            tmp=iscal=0;
            while(top>=0 && stack[top]!='(' && w[stack[top]]>=w[equ[i]])
                postfix[p++]=-stack[top--]; //在栈中弹出优先级高于或等于自己的字符，'('除外

            if(equ[i]==')')
            {
                while(stack[top]!='(') postfix[p++]=-stack[top--];
                top--;
            }
            else stack[++top]=equ[i];
        }
    }
    if(iscal)postfix[p++]=tmp;//记得加上可能存在的最后一个数
    while(top>=0) postfix[p++]=-stack[top--];//清空栈

//    for(i=0;i<p;i++) if(postfix[i]>=0) printf("%d ",postfix[i]);else printf("%c ",-postfix[i]);
//    puts("");
}

int postCal()
{
    int i,tmp;
    for(i=0;i<p;i++)
    {
        switch(postfix[i])
        {
        case -43:
            tmp=stack[top-1]+stack[top];
            stack[--top]=tmp;
            break;
        case -45:
            tmp=stack[top-1]-stack[top];
            stack[--top]=tmp;
            break;
        case -42:
            tmp=stack[top-1]*stack[top];
            stack[--top]=tmp;
            break;
        case -47:
            tmp=stack[top-1]/stack[top];
            stack[--top]=tmp;
            break;
        case -37:
            tmp=stack[top-1]%stack[top];
            stack[--top]=tmp;
//          stack[--top]=stack[top]%stack[top+1]; 未定义行为，--top时编译器不会保存top的值，所以其后的行为未定义；top++好像就可以
            break;
        default:
            stack[++top]=postfix[i];
        }
    }
    return stack[0];
}

int main()
{
    int i,j,res;
    char equ[BUFSIZ];

    gets(equ);
    for(i=j=0;equ[i]!='\0';i++)
    {
        if(equ[i]!=' ') equ[j++]=equ[i];
    }
    equ[j]='\0';

    in_to_post(equ);
    printf("%d",postCal());

    return 0;
}
