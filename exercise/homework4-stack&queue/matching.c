#include<stdio.h>
#include<string.h>

char stack[201];
char print[201];/* ���մ�ӡ�� */
int cnt_line[201];/* ��¼���� */
int top=-1,ptop=-1;

int main()
{
    FILE *fp;
    char buf[202];
    int line=0;
    int i,len;

    fp=fopen("example.c","r");
    while(fgets(buf,200,fp)!=NULL)
    {
        line++;
        len=strlen(buf)-1;
        for(i=0;i<len;i++)
        {
            if(top>=0 && stack[top]==34)                /* ˫���ź��� */
            {
                if(buf[i]==34) top--;
                continue;
            }
            else if(top>=0 && stack[top]==39)
            {
                if(buf[i]==39) top--;
                continue;
            }
            else if(top>=0 && stack[top]==42)          /* ����ע�ͺ��� */
            {
                if(buf[i]==42 && buf[i+1]==47)
                    top--,i++;
                continue;
            }

            if(buf[i]==47 && buf[i+1]==47) break;       /* ����ע�� */
            else if(buf[i]==47 && buf[i+1]==42) stack[++top]=42,i++;/* ����ע�� */
            else if(buf[i]==34) stack[++top]=34;        /* ˫����  */
            else if(buf[i]==39) stack[++top]=39;        /* �յ����� */   //�Ե����ŵ���ʽ�뵱Ȼ�ˣ��ǵ�ת���ַ�
            else if(buf[i]=='(')
            {
                stack[++top]=print[++ptop]=buf[i];
                cnt_line[top]=line; //��¼��ǰ����������
            }
            else if(buf[i]=='{')
            {
                if(top>=0 && stack[top]=='(')
                {
                    printf("without maching '%c' at line %d",stack[top],cnt_line[top]);
                    return 0;
                }
                stack[++top]=print[++ptop]=buf[i];
                cnt_line[top]=line; //��¼��ǰ����������
            }
            else if(buf[i]==')')
            {
                if(top>=0 && stack[top]=='(')//�����Ų�����С����
                {
                    print[++ptop]=buf[i];
                    top--;
                }
                else
                {
                    printf("without maching '%c' at line %d",buf[i],line);
                    return 0;
                }
            }
            else if(buf[i]=='}')
            {
                if(top>=0 && stack[top]=='{')
                {
                    print[++ptop]=buf[i];
                    top--;
                }
                else
                {
                    printf("without maching '%c' at line %d",buf[i],line);
                    return 0;
                }
            }
        }
        //printf("stack_cur: line%d [%s]\n",line,stack);
    }
    if(top>=0) printf("without maching '%c' at line %d",stack[top],cnt_line[top]);
    else printf("%s",print);
    return 0;
}
