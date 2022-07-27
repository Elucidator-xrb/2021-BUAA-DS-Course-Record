#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
/*�ƶ� �̶� ��� ���� ����״̬*/
/* Pseudocode
for(��ʼ��;��������;�ӳ�)
{
    ����();
    if(�ƶ�())
        if(Y==0) ����();
        if(����()) ����();
    ���();
}
*/

int Width=10,Height=20,Size;
int X,Y,T;
int daily,*map,node[]={
    51264, 12816, 21520, 21520, 25872, 34113, 21537, 38208, 25921, 38481,
	38484, 38209, 25922, 43345, 34388, 38160, 25920, 38177, 42580, 38993};
int i,x,y,cond,j,k;

int move(int *coord, int step)//�ж϶��������Ƿ�Ϸ�
{
    *coord+=step;
    for(i=node[T];i;i>>=4)
    {
        x=X+i%4, y=Y+i/4%4;
        (x<0 || x>=Width || y>=Height || map[y*Width+x]) && (cond=0);//���ö�·�߼���
        //cond=0 - ��Ч; cond=1 - ��Ч
    }
    return cond ? 1 : (*coord-=step,coord==&Y && (cond=-1));
    //��Ч��1
    //��Ч��״̬����
    //      ����ʱ�������˶�����˵�����ף�����"�̶�"״̬
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
    for(system("cls");cond-27;_sleep(50))//Esc�ļ�ֵ��27�����Խ���������cond-27
    {
        cond= _kbhit() ? _getch()&95 : 1 ;//���ռ�������
        for(i=node[T];i;i>>=4)//�ƶ�ǰ������ֵ����֮��moveʱ����
        {
            x=X+i%4, y=Y+i/4%4;
            map[y*Width+x]=0;
        }

        cond^65 || move(&X,-1);//'A'
        cond^68 || move(&X, 1);//'D'
        cond^83 || move(&Y, 1);//'S'
        cond^87 || (i= T<4?1:3, move(&T,T&i^i ? 1 : -i));//iȷ����2ѭ���黹��4ѭ����
        //       ��move(&T,T%4<3 ? 1 : -3)�ĸĽ�
        //         move(&T,T&3<3 ? 1 : -3)

        //daily++;
        ++daily-10 || (daily=0,cond=1,move(&Y,1));//�Զ����䣺ÿ500msһ��
        for(i=node[T];i;i>>=4)
        {
            x=X+i%4, y=Y+i/4%4;
            map[y*Width+x]=T/4*16+154;//upgrade 5����ɫ
        }

        //ֻ�н���"�̶�"״̬,�Ż�ִ�к���״̬���ж��Ƿ����+��ʼ��+"����"׼��
        if(cond==-1 && !(Y || (cond=27),T=rand()%20,Y=X=0))
        {   //����Կ���forд��һ�о���һ��֮��
            for(i=Size-1,j=Width; j-=!!map[i],i; i--%Width || (j=Width))//��for����while��if�Ľ����
                for(j || (k=i+=Width); !j&&(--k>=Width);map[k]=map[k-Width]);
        }

        SetConsoleCursorPosition(GetStdHandle((DWORD)-11),(COORD){0});
        while(i<Size)//��ӡ
        {
            SetConsoleTextAttribute(GetStdHandle((DWORD)-11),map[i]);
            _cputs("  ");
            ++i%Width || _cputs("\n");
        }
    }

    return 0;
}
