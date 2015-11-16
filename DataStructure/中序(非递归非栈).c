#include <stdio.h>
typedef struct NODE{
    int data, left, right, parent, rtag;
}node;
//创建表
void create(node tree[]);
//遍历
void InOrder(node tree[], int curNode);
int main(){
    node tree[128];
    create(tree);
    InOrder(tree, 1);
    return 0;
}

void create(node tree[]){
    printf("请输入结点个数:");
    int i, count;
    char child;
    scanf("%d",&count);
    printf("依次输入各结点D P l/r:\n");
    for(i = 1; i <= count; i++){
        scanf("%d %d %c", &tree[i].data, &tree[i].parent, &child);
        if(child == 'l')
            tree[tree[i].parent].left = i;
        else if(child == 'r')
            tree[tree[i].parent].right = i;
        tree[i].left = tree[i].right = 0;
        tree[i].rtag = 0;
    }
    tree[1].parent = 0;
}
void InOrder(node tree[], int curNode){
    while(curNode != 0){
        //查找未访问的最左结点
        while(tree[curNode].left != 0 && tree[tree[curNode].left].rtag == 0)
            curNode = tree[curNode].left;
        if(tree[curNode].rtag == 0)
            printf("%d ",tree[curNode].data);
        tree[curNode].rtag = 1;
        if(tree[curNode].right != 0 && tree[tree[curNode].right].rtag == 0){
            curNode = tree[curNode].right;
            continue;
        }
        else
            curNode = tree[curNode].parent;
    }

}
