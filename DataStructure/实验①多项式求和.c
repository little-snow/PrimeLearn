#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct NODE
{
    double coef;         //ϵ��
    int exp;             //ָ��
    struct NODE *next;   //ָ����һ���ָ��
};
typedef struct NODE* poly;
typedef struct NODE* node;

//�����µ����������ָ��
node insert(node pre_node, node new_node);
//ɾ������ظ���ָ��
node delete(node pre_node);
//��������ʽ
void create(poly head);

int main()
{
    poly P = (poly)malloc(sizeof(struct NODE));
    poly Q = (poly)malloc(sizeof(struct NODE));
    printf("�������������ʽһ�и����ϵ����ָ�����Է������ַ�������\n");
    create(P);
    printf("�������������ʽ���и����ϵ����ָ�����Է������ַ�������\n");
    create(Q);

    //����ʽ���
    poly ptemp = P;
    poly qtemp = Q;
    while(ptemp->next != NULL && qtemp->next != NULL)
    {
        //���Pʽ��ǰ�ڵ�ָ������Qʽ�����ƶ�p
        if(ptemp->next->exp > qtemp->next->exp)
            ptemp = ptemp->next;
        //Pʽ��ǰ�ڵ�ָ��С��Qʽ���ƶ�q�Ľڵ㵽p��
        else if(ptemp->next->exp < qtemp->next->exp)
        {
            poly temp = delete(qtemp);
            ptemp = insert(ptemp, temp);
        }
        //��ʽָ����ȣ��ϲ��ڵ㲢ɾ��ϵ��Ϊ0�Ľڵ�
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
    printf("����ʽ�ϲ��Ľ��Ϊ��\n");
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

//�����½ڵ�
node insert(node pre_node, node new_node)
{
	new_node->next = pre_node->next;
	pre_node->next = new_node;
	return new_node;
}
//ɾ���ڵ�
node delete(node pre_node)
{
    node temp = pre_node->next;
    pre_node->next = pre_node->next->next;
    return temp;
}
//�½�����ʽ,ͬʱ����������
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


