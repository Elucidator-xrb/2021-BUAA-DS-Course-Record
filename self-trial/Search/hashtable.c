#include<stdio.h>
#define HashMax 100
#define Empty -1

typedef int Hashlist[HashMax]; //������ʹ��typedef

Hashlist HT;

//1.���루����hashtable��,��ϣ���ɺ��� H(key)  + ������ɢ��
int hashInsert(int m,int key)
{
    int i,d;
    d=i=H(key);
    while(HT[d]!=Empty && HT[d]!=key) /* HT��Ϊ���Ҳ����Լ������Լ�˵���Ѵ��룩*/
    {
        d=(d+1)%m;
        if(d==i) return -1; /* ת��һȦ�ص�ͷ����˵�������� */
    }
    if(HT[d]!=key) HT[d]=key;
    return d;
}

//2.���� + ������ɢ��
int hashSearch(int m,int key)
{
    int i,d,di=1;
    d=i=H(key);
    while(HT[d]!=Empty && HT[d]!=key)
    {
        d=(i+di*di++)%M;
        if(d==i) return -1;
    }
    if(HT[d]==k) return d;
    return -1;
}

//3.ɾ�� + ��ʽ��ַ��
