#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_QUEUE 256

typedef struct Btree
{
	int data;
	struct Btree *lchild;
	struct Btree *rchild;
}*BT;

void CreateBt(BT *root);
void PreOrder(BT root);
void InOrder(BT root);
void PostOrder(BT root);
void LevelOrder(BT root);

int main()
{
	BT root;
	CreateBt(&root);
	printf("���������\n");
	PreOrder(root);
	printf("\n");
	printf("���������\n");
	InOrder(root);
	printf("\n");
	printf("���������\n");
	PostOrder(root);
	printf("\n");
	printf("���������\n");
	LevelOrder(root);
	printf("\n");
	return 0;
}

//��������ʼ��������
void CreateBt(BT *root)
{
	int number, data, parent;
	char child;
	int i = 1;
	BT queue[256];
	printf("������ڵ������");
	scanf("%d", &number);
	printf("������������ڵ����Ԫ��D P L/R:\n");
	while(number-- > 0)
	{
		printf("Node %d: ", i);
		scanf("%d%d%*c%c", &data, &parent, &child);
		if(parent == 0)
		{
			queue[1] = (BT)malloc(sizeof(struct Btree));
			queue[1]->data = data;
			i++;
		}
		else
		{
			queue[i] = (BT)malloc(sizeof(struct Btree));
			queue[i]->data = data;
			queue[i]->lchild = queue[i]->rchild = NULL;
			if(child == 'L' || child == 'l')
				queue[parent]->lchild = queue[i];
			if(child == 'R' || child == 'r')
				queue[parent]->rchild = queue[i];
            i++;
		}
	}
	*root = queue[1];
}
//�ȸ�����
void PreOrder(BT root)
{
	if(root == NULL)
		return;
	printf("%d ",root->data);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}
//�и�����
void InOrder(BT root)
{
	if(root == NULL)
		return;
	InOrder(root->lchild);
	printf("%d ", root->data);
	InOrder(root->rchild);
}
//�������
void PostOrder(BT root)
{
	if(root == NULL)
		return;
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	printf("%d ", root->data);
}
//�������
void LevelOrder(BT root)
{
	BT queue[SIZE_OF_QUEUE];
	//��������������
	int length;
	//��ǰɨ��Ԫ���ڶ����е�λ��
	int local;
	local = 0;
	queue[0] = root;
	length = 1;
	//ִ�����Ԫ�ء���Ԫ�����Һ��ӽ��ӡ�����
	//ȫ��ɨ�裬����ǰɨ��λ�õ����βʱֹͣ
	while(local < length)
	{
        printf("%d ", queue[local]->data);
        if(queue[local]->lchild != NULL)
            queue[length++] = queue[local]->lchild;
        if(queue[local]->rchild != NULL)
            queue[length++] = queue[local]->rchild;
        local++;
	}
}