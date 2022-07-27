#include<stdio.h>
#include<string.h>
#include<ctype.h>

int stack[BUFSIZ],top=-1;
int postfix[BUFSIZ],p=0;
int w[48];

void in_to_post(char *equ) //�ܶ�ע���
{
    int i,tmp=0,iscal=0;
    w[43]=w[45]=1,w[42]=w[47]=w[37]=2,w[40]=w[41]=3;

    for(i=0;equ[i]!='=';i++)
    {
        if(isdigit(equ[i])) tmp=(tmp<<1)+(tmp<<3)+(equ[i]&15),iscal=1;
        else
        {
            if(iscal)postfix[p++]=tmp; //ֻ��ȡ�����ֲ��ܴ���,iscalν��
            tmp=iscal=0;
            while(top>=0 && stack[top]!='(' && w[stack[top]]>=w[equ[i]])
                postfix[p++]=-stack[top--]; //��ջ�е������ȼ����ڻ�����Լ����ַ���'('����

            if(equ[i]==')')
            {
                while(stack[top]!='(') postfix[p++]=-stack[top--];
                top--;
            }
            else stack[++top]=equ[i];
        }
    }
    if(iscal)postfix[p++]=tmp;//�ǵü��Ͽ��ܴ��ڵ����һ����
    while(top>=0) postfix[p++]=-stack[top--];//���ջ

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
//          stack[--top]=stack[top]%stack[top+1]; δ������Ϊ��--topʱ���������ᱣ��top��ֵ������������Ϊδ���壻top++����Ϳ���
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
