#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct NODE{
    int data;
    intptr_t next;
}*node;

int main(){
    node head1, head2, preNode1, preNode2,temp;
    head1 = (node)malloc(sizeof(struct NODE));
    head2 = (node)malloc(sizeof(struct NODE));
    preNode1 = head1;
    preNode2 = head2;
    int elem;
    printf("������һ�����֣��Է������ַ�����:\n");
    while(scanf("%d",&elem) == 1){
    	temp = (node)malloc(sizeof(struct NODE));
    	temp->data = elem;
    	preNode2->next = (intptr_t)preNode1 ^ (intptr_t)temp;
    	preNode1 = preNode2;
    	preNode2 = temp;
    }
    temp = (node)((intptr_t)head1 ^ head2->next);
    free(head2);
    free(head1);
    head1 = temp;
    head2 = (node)((intptr_t)head2 ^ temp->next);
    preNode2->next = (intptr_t)preNode1 ^ (intptr_t)temp;
    temp->next = (intptr_t)preNode2 ^ (intptr_t)head2;
    head2 = preNode2;
    printf("�˻��α�����˳ʱ�����˳��Ϊ��\n");
    do{
        printf("%d\t", temp->data);
        preNode1 = preNode2;
        preNode2 = temp;
        temp = (node)((intptr_t)preNode1 ^ preNode2->next);
    }while(temp != head2);
    printf("%d\n",temp->data);
    return 0;
}
