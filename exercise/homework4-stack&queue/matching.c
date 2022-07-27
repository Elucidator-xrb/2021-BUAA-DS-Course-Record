#include<stdio.h>
#include<string.h>

char stack[201];
char print[201];/* 最终打印用 */
int cnt_line[201];/* 记录行数 */
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
            if(top>=0 && stack[top]==34)                /* 双引号忽略 */
            {
                if(buf[i]==34) top--;
                continue;
            }
            else if(top>=0 && stack[top]==39)
            {
                if(buf[i]==39) top--;
                continue;
            }
            else if(top>=0 && stack[top]==42)          /* 多行注释忽略 */
            {
                if(buf[i]==42 && buf[i+1]==47)
                    top--,i++;
                continue;
            }

            if(buf[i]==47 && buf[i+1]==47) break;       /* 单行注释 */
            else if(buf[i]==47 && buf[i+1]==42) stack[++top]=42,i++;/* 多行注释 */
            else if(buf[i]==34) stack[++top]=34;        /* 双引号  */
            else if(buf[i]==39) stack[++top]=39;        /* 闭单引号 */   //对单引号的形式想当然了，记得转义字符
            else if(buf[i]=='(')
            {
                stack[++top]=print[++ptop]=buf[i];
                cnt_line[top]=line; //记录当前符号所在行
            }
            else if(buf[i]=='{')
            {
                if(top>=0 && stack[top]=='(')
                {
                    printf("without maching '%c' at line %d",stack[top],cnt_line[top]);
                    return 0;
                }
                stack[++top]=print[++ptop]=buf[i];
                cnt_line[top]=line; //记录当前符号所在行
            }
            else if(buf[i]==')')
            {
                if(top>=0 && stack[top]=='(')//大括号不含于小括号
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
