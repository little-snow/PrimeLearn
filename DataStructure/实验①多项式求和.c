#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct NODE
{
    double coef;         //系数
    int exp;             //指数
    struct NODE *next;   //指向下一项的指针
};
typedef struct NODE* poly;
typedef struct NODE* node;

//插入新的项，返回新项指针
node insert(node pre_node, node new_node);
//删除项，返回该项指针
node delete(node pre_node);
//创建多项式
void create(poly head);

int main()
{
    poly P = (poly)malloc(sizeof(struct NODE));
    poly Q = (poly)malloc(sizeof(struct NODE));
    printf("请依次输入多项式一中各项的系数及指数，以非数字字符结束：\n");
    create(P);
    printf("请依次输入多项式二中各项的系数及指数，以非数字字符结束：\n");
    create(Q);

    //多项式求和
    poly ptemp = P;
    poly qtemp = Q;
    while(ptemp->next != NULL && qtemp->next != NULL)
    {
        //如果P式当前节点指数大于Q式，仅移动p
        if(ptemp->next->exp > qtemp->next->exp)
            ptemp = ptemp->next;
        //P式当前节点指数小于Q式，移动q的节点到p中
        else if(ptemp->next->exp < qtemp->next->exp)
        {
            poly temp = delete(qtemp);
            ptemp = insert(ptemp, temp);
        }
        //两式指数相等，合并节点并删除系数为0的节点
        else
        {
            ptemp->next->coef += qtemp->next->coef;
            if(fabs(ptemp->next->coef)<= 1e-6)
                free(delete(ptemp));
            else
                ptemp = ptemp->next;
            free(delete(qtemp));
        }
    }
    if(ptemp->next == NULL)
    {
        ptemp->next = qtemp->next;
        free(qtemp);
    }
    else
        free(qtemp);

    ptemp = P->next;
    printf("多项式合并的结果为：\n");
    if(ptemp == NULL)
        printf("0\n");
    else
    {
        if(ptemp->exp == 0)
            printf("%f",ptemp->coef);
        else
            printf("%fx^%d",ptemp->coef, ptemp->exp);
        ptemp = ptemp->next;
        while(ptemp != NULL)
        {
            if(ptemp->exp == 0)
                printf("%+f",ptemp->coef);
            else
                printf("%+fx^%d",ptemp->coef, ptemp->exp);
            ptemp = ptemp->next;
        }
        printf("\n");
    }
    return 0;
}

//插入新节点
node insert(node pre_node, node new_node)
{
	new_node->next = pre_node->next;
	pre_node->next = new_node;
	return new_node;
}
//删除节点
node delete(node pre_node)
{
    node temp = pre_node->next;
    pre_node->next = pre_node->next->next;
    return temp;
}
//新建多项式,同时给链表排序
void create(poly head)
{
    node new_node;
    node local = head;
    local->next = (node)malloc(sizeof(struct NODE));
    local->next->coef = 0;
    local->next->exp = 0;
    local->next->next = NULL;
    double coef;
    int exp;
    while(scanf("%lf%d", &coef, &exp) == 2)
    {
        if(fabs(coef) <= 1e-6) continue;
        for(local = head; ; local = local->next)
        {
            if(local->next == NULL || exp > local->next->exp)
            {
                new_node = (poly)malloc(sizeof(struct NODE));
                new_node->coef = coef;
                new_node->exp = exp;
                insert(local, new_node);
                break;
            }
            else if(exp == local->next->exp)
            {
                local->next->coef += coef;
                break;
            }
        }
    }
    fflush(stdin);
}


