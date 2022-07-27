#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
/*移动 固定 溢出 消行 四种状态*/
/* Pseudocode
for(初始化;结束条件;延迟)
{
    输入();
    if(移动())
        if(Y==0) 结束();
        if(行满()) 消行();
    输出();
}
*/

int Width=10,Height=20,Size;
int X,Y,T;
int daily,*map,node[]={
    51264, 12816, 21520, 21520, 25872, 34113, 21537, 38208, 25921, 38481,
	38484, 38209, 25922, 43345, 34388, 38160, 25920, 38177, 42580, 38993};
int i,x,y,cond,j,k;

int move(int *coord, int step)//判断动作命令是否合法
{
    *coord+=step;
    for(i=node[T];i;i>>=4)
    {
        x=X+i%4, y=Y+i/4%4;
        (x<0 || x>=Width || y>=Height || map[y*Width+x]) && (cond=0);//利用短路逻辑！
        //cond=0 - 无效; cond=1 - 有效
    }
    return cond ? 1 : (*coord-=step,coord==&Y && (cond=-1));
    //有效：1
    //无效：状态回退
    //      若此时作下移运动，则说明触底，进入"固定"状态
}

int main()
{
    SetConsoleCursorInfo( GetStdHandle((DWORD)-11),&(CONSOLE_CURSOR_INFO){1} );

    printf("=================\n");
    printf("Welcome to Tetris\n");
    printf("=================\n");
    printf("Press any button to begin!\nPress Esc to end!\n");
    printf("'A' for left, 'D' for right, 'S' for accelerate, 'W' for shape changeing\n");
    system("pause");

    srand(map=calloc(Size=Width*Height,4));
    for(system("cls");cond-27;_sleep(50))//Esc的键值是27，所以结束条件是cond-27
    {
        cond= _kbhit() ? _getch()&95 : 1 ;//接收键盘输入
        for(i=node[T];i;i>>=4)//移动前消除旧值，已之后move时误判
        {
            x=X+i%4, y=Y+i/4%4;
            map[y*Width+x]=0;
        }

        cond^65 || move(&X,-1);//'A'
        cond^68 || move(&X, 1);//'D'
        cond^83 || move(&Y, 1);//'S'
        cond^87 || (i= T<4?1:3, move(&T,T&i^i ? 1 : -i));//i确定是2循环组还是4循环组
        //       对move(&T,T%4<3 ? 1 : -3)的改进
        //         move(&T,T&3<3 ? 1 : -3)

        //daily++;
        ++daily-10 || (daily=0,cond=1,move(&Y,1));//自动下落：每500ms一次
        for(i=node[T];i;i>>=4)
        {
            x=X+i%4, y=Y+i/4%4;
            map[y*Width+x]=T/4*16+154;//upgrade 5种颜色
        }

        //只有进入"固定"状态,才会执行后面状态：判断是否结束+初始化+"消行"准备
        if(cond==-1 && !(Y || (cond=27),T=rand()%20,Y=X=0))
        {   //万物皆可用for写：一切尽在一行之中
            for(i=Size-1,j=Width; j-=!!map[i],i; i--%Width || (j=Width))//把for当作while和if的结合用
                for(j || (k=i+=Width); !j&&(--k>=Width);map[k]=map[k-Width]);
        }

        SetConsoleCursorPosition(GetStdHandle((DWORD)-11),(COORD){0});
        while(i<Size)//打印
        {
            SetConsoleTextAttribute(GetStdHandle((DWORD)-11),map[i]);
            _cputs("  ");
            ++i%Width || _cputs("\n");
        }
    }

    return 0;
}
