#include<stdio.h>
#include<stdlib.h>

typedef SElemType int;

typedef struct node
{
    SElemType data;
    struct node *link;
} STNode, *STLink;

STLink top;

void initial(STLink top);
int isEmpty(STLink top);
SElemType getTop(STLink top);
SElemType push(STLink top);
SElemType pop(STLink top);
