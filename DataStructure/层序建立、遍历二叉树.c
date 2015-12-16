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
	printf("先序遍历：\n");
	PreOrder(root);
	printf("\n");
	printf("中序遍历：\n");
	InOrder(root);
	printf("\n");
	printf("后序遍历：\n");
	PostOrder(root);
	printf("\n");
	printf("层序遍历：\n");
	LevelOrder(root);
	printf("\n");
	return 0;
}

//创建并初始化二叉树
void CreateBt(BT *root)
{
	int number, data, parent;
	char child;
	int i = 1;
	BT queue[256];
	printf("请输入节点个数：");
	scanf("%d", &number);
	printf("请依次输入各节点的三元组D P L/R:\n");
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
//先根遍历
void PreOrder(BT root)
{
	if(root == NULL)
		return;
	printf("%d ",root->data);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}
//中根遍历
void InOrder(BT root)
{
	if(root == NULL)
		return;
	InOrder(root->lchild);
	printf("%d ", root->data);
	InOrder(root->rchild);
}
//后根遍历
void PostOrder(BT root)
{
	if(root == NULL)
		return;
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	printf("%d ", root->data);
}
//层序遍历
void LevelOrder(BT root)
{
	BT queue[SIZE_OF_QUEUE];
	//队列内数据总数
	int length;
	//当前扫描元素在队列中的位置
	int local;
	local = 0;
	queue[0] = root;
	length = 1;
	//执行输出元素、该元素左右孩子进队、操作
	//全程扫描，当当前扫描位置到达队尾时停止
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