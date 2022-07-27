#include<stdio.h>
#include<stdlib.h>


//十字链表中链接点类型
typedef struct node {
    int row, col;
    union {
        int val;
        struct node *ptr;
    };             //value域包括两种类型
    struct node *right, *down;
}CNode, *CrossLink;

//十字链表的总头结点类型
typedef struct {
    int m, n, t, nil;
    CrossLink link;
}HNode, *HLink;

#define MaxN 100

/*创建一个十字链表*/
HLink makeCrossLink(  ){
    HLink head;
    CrossLink p, last, hdnode[MaxN];
    int m, n, t, k, i, current_row;
    int rrow, ccol, val;
    scanf( "%d %d %d", &m, &n, &t );  /*读入矩阵总的行数，列数和非零元素的个数*/
    if( t <= 0 )
        return NULL;
    k = ( m > n ) ? m : n;  /*取矩阵行数和列数中值较大者作为表头结点的个数*/

    for( i = 0; i < k; i++ ){            /* 生成k个表头结点,并初始化表头结点中各个元素 */
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
    for( i = 1; i <= t; i++ ){       /* 以三元组表的形式输入元素 */
        scanf( "%d %d %d", &rrow, &ccol, &val );
        if( rrow > current_row ){           /* 当一行的非零元素读取完毕，则立刻将链表封闭成一个循环链表*/
            last->right = hdnode[current_row-1];
            last = hdnode[rrow-1];
            current_row = rrow;
        }

        p = ( CrossLink )malloc( sizeof( CNode ) );    /* 申请一个新的链接点来存储新的非零值 */
        p->row = rrow;
        p->col = ccol;
        p->val = val;                 /* 生成一个新结点 */

        last->right = p;              /* 将新的链接点链接到相应行链表中 */
        last = p;
        hdnode[ccol-1]->ptr->down = p;
        hdnode[ccol-1]->ptr = p;          /* 将新的链接点链接到相应的列链表中 */
    }

    last->right = hdnode[current_row-1];   /* 将最后一个行链表封闭成循环链表 */
    for( i = 0; i < k; i++ ){                 /* 将所有列链表封闭成循环链表 */
        hdnode[i]->ptr->down = hdnode[i];
    }

    head = ( HLink )malloc( sizeof( HNode ) );  /* 申请一个总的头结点 */
    head->m = m;
    head->n = n;
    head->t = t;

    for( i = 0; i < k-1; i++ ){           /* 利用value域将头结点链接成一个循环链表 */
        hdnode[i]->ptr = hdnode[i+1];
    }

    if( k == 0 )
        head->link = ( CrossLink )head;
    else{
        head->link = hdnode[0];              /* 将总头结点的link域指向头结点链表的第1个头结点 */
        hdnode[k-1]->ptr = ( CrossLink )head;          /* 将头结点链表的最后一个头结点的ptr域指向总的头结点 */
    }

    return head;
}

/* 打印十字链表 */
void printLink( HLink alink ){
    CrossLink p, q;      /* p用来遍历头结点链表，q用来遍历每个行链表 */
    if( alink != NULL ){
        printf( "(%d, %d, %d)\n", alink->m, alink->n, alink->t );    /* 打印总头结点信息 */
        p = alink->link;               /* p指向头结点链表的第1个链接点 */
        while( p != (CrossLink)alink ){
            q = p->right;           /* q指向行链表的第1个元素 */
            while( q != p ){
                printf( "(%d, %d, %d)\n", q->row, q->col, q->val );
                q = q->right;
            }
            p = p->ptr;         /* p指向下一个头结点链表中的元素 */
        }
    }
}

/* 销毁一个十字链表 */
void deleteLink( HLink *alink ){
    CrossLink p = ( *alink )->link;
    CrossLink q, r;
    while( p != ( CrossLink )*alink ){
        q = p->right;              /* 将q指向行链表的第1个元素 */
        while( q != p ){  /* 销毁一个行链表 */
            r = q;
            q = q->right;
            free( r );
        }

        r = p;      /* 销毁该行链表的表头结点，将p指向下一个行链表的表头结点 */
        p = p->ptr;
        free( r );
    }

    free( *alink );    /* 释放总头结点的空间 */
}
