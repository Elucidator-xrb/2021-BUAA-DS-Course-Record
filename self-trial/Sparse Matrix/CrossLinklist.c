#include<stdio.h>
#include<stdlib.h>


//ʮ�����������ӵ�����
typedef struct node {
    int row, col;
    union {
        int val;
        struct node *ptr;
    };             //value�������������
    struct node *right, *down;
}CNode, *CrossLink;

//ʮ���������ͷ�������
typedef struct {
    int m, n, t, nil;
    CrossLink link;
}HNode, *HLink;

#define MaxN 100

/*����һ��ʮ������*/
HLink makeCrossLink(  ){
    HLink head;
    CrossLink p, last, hdnode[MaxN];
    int m, n, t, k, i, current_row;
    int rrow, ccol, val;
    scanf( "%d %d %d", &m, &n, &t );  /*��������ܵ������������ͷ���Ԫ�صĸ���*/
    if( t <= 0 )
        return NULL;
    k = ( m > n ) ? m : n;  /*ȡ����������������ֵ�ϴ�����Ϊ��ͷ���ĸ���*/

    for( i = 0; i < k; i++ ){            /* ����k����ͷ���,����ʼ����ͷ����и���Ԫ�� */
        p = ( CrossLink )malloc( sizeof( CNode ) );
        hdnode[i] = p;
        p->row = 0;
        p->col = 0;
        p->ptr = p;
        p->right = p;
        p->down = p;
    }

    current_row = 1;
    last = hdnode[0];
    for( i = 1; i <= t; i++ ){       /* ����Ԫ������ʽ����Ԫ�� */
        scanf( "%d %d %d", &rrow, &ccol, &val );
        if( rrow > current_row ){           /* ��һ�еķ���Ԫ�ض�ȡ��ϣ������̽������ճ�һ��ѭ������*/
            last->right = hdnode[current_row-1];
            last = hdnode[rrow-1];
            current_row = rrow;
        }

        p = ( CrossLink )malloc( sizeof( CNode ) );    /* ����һ���µ����ӵ����洢�µķ���ֵ */
        p->row = rrow;
        p->col = ccol;
        p->val = val;                 /* ����һ���½�� */

        last->right = p;              /* ���µ����ӵ����ӵ���Ӧ�������� */
        last = p;
        hdnode[ccol-1]->ptr->down = p;
        hdnode[ccol-1]->ptr = p;          /* ���µ����ӵ����ӵ���Ӧ���������� */
    }

    last->right = hdnode[current_row-1];   /* �����һ���������ճ�ѭ������ */
    for( i = 0; i < k; i++ ){                 /* �������������ճ�ѭ������ */
        hdnode[i]->ptr->down = hdnode[i];
    }

    head = ( HLink )malloc( sizeof( HNode ) );  /* ����һ���ܵ�ͷ��� */
    head->m = m;
    head->n = n;
    head->t = t;

    for( i = 0; i < k-1; i++ ){           /* ����value��ͷ������ӳ�һ��ѭ������ */
        hdnode[i]->ptr = hdnode[i+1];
    }

    if( k == 0 )
        head->link = ( CrossLink )head;
    else{
        head->link = hdnode[0];              /* ����ͷ����link��ָ��ͷ�������ĵ�1��ͷ��� */
        hdnode[k-1]->ptr = ( CrossLink )head;          /* ��ͷ�����������һ��ͷ����ptr��ָ���ܵ�ͷ��� */
    }

    return head;
}

/* ��ӡʮ������ */
void printLink( HLink alink ){
    CrossLink p, q;      /* p��������ͷ�������q��������ÿ�������� */
    if( alink != NULL ){
        printf( "(%d, %d, %d)\n", alink->m, alink->n, alink->t );    /* ��ӡ��ͷ�����Ϣ */
        p = alink->link;               /* pָ��ͷ�������ĵ�1�����ӵ� */
        while( p != (CrossLink)alink ){
            q = p->right;           /* qָ��������ĵ�1��Ԫ�� */
            while( q != p ){
                printf( "(%d, %d, %d)\n", q->row, q->col, q->val );
                q = q->right;
            }
            p = p->ptr;         /* pָ����һ��ͷ��������е�Ԫ�� */
        }
    }
}

/* ����һ��ʮ������ */
void deleteLink( HLink *alink ){
    CrossLink p = ( *alink )->link;
    CrossLink q, r;
    while( p != ( CrossLink )*alink ){
        q = p->right;              /* ��qָ��������ĵ�1��Ԫ�� */
        while( q != p ){  /* ����һ�������� */
            r = q;
            q = q->right;
            free( r );
        }

        r = p;      /* ���ٸ�������ı�ͷ��㣬��pָ����һ��������ı�ͷ��� */
        p = p->ptr;
        free( r );
    }

    free( *alink );    /* �ͷ���ͷ���Ŀռ� */
}
