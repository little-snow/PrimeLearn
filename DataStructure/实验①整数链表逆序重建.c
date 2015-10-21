#include <stdio.h>
#include <stdlib.h>
#define INPUT(x) {if(scanf("%d",&x) == 0){printf("请确认操作是否正确！\n");fflush(stdin);break;}}
struct NODE
{
    int number;
    struct NODE *next;
};

typedef struct NODE *position;
typedef struct NODE *LIST;

int length;

//查找,返回所搜元素的前驱
position search(LIST head, int number,int *location);
//插入
void insert(position preNode, position newNode);
//删除,返回被删除节点位置
position delete(position preNode);
//升序排序
void sort(LIST head);
//输出链表
void display(LIST head);
//逆序重建
void reverse(LIST head);

int main()
{
    LIST numSet = (LIST)malloc(sizeof(struct NODE));
    {
        int temp;
        position preNode = numSet;
        freopen("data.in","r",stdin);
        while(scanf("%d",&temp) != EOF)
        {
            preNode->next = (position)malloc(sizeof(struct NODE));
            preNode->next->number = temp;
            length++;
            preNode = preNode->next;
        }
        preNode->next = NULL;
        freopen("con", "r", stdin);
        sort(numSet);
        printf("已录入文件data.in中的数据并已进行升序排列.\n");
    }

    int op;
    int number;
    int location;
    do
    {
        printf("请选择相应数字进行操作：\n");
        printf("1:查找      2:插入      3:删除      4:排序 \n");
        printf("5:输出链长  6.输出链表  7:逆转链表  8:退出\n");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            printf("请输入欲要查找的数字：");
            //防止输入的不是整数
            INPUT(number);
            if(search(numSet, number,&location)->next == NULL)
                printf("%d 不在链表中！\n", number);
            else
                printf("%d 在链表中的第 %d 位.\n", number, location);
            break;
        case 2:
            printf("请输入欲插入的数字：");
            //防止输入的不是整数
            INPUT(number);
            position temp1 = (position)malloc(sizeof(struct NODE));
            temp1->number = number;
            insert(numSet, temp1);
            printf("操作成功：%d 已插入！\n",number);
            break;
        case 3:
            printf("请输入欲删除的数字：");
            //防止输入的不是整数
            INPUT(number);
            position temp2 = delete(search(numSet, number, &location));
            if(temp2 == NULL)
                printf("操作失败：欲删数字不在链表中！\n");
            else
            {
                free(temp2);
                printf("操作成功：%d 已删除！\n", number);
            }
            break;
        case 4:
            sort(numSet);
            printf("操作成功：已按升序排列！\n");
            break;
        case 5:
            printf("数据总个数为 %d.\n", length);
            break;
        case 6:
            printf("表中数据依次为：");
            display(numSet);
            break;
        case 7:
            reverse(numSet);
            printf("操作成功：数据已逆向重排！\n");
            break;
        case 8: break;
        default:
            printf("请输入正确指令！\n");
            fflush(stdin);
            break;
        }
    printf("\n");
    }while(op != 8);

    return 0;
}


position search(LIST head, int number, int *location)//查找
{
    position preNode;
    *location = 0;
    for(preNode = head; preNode->next != NULL; preNode = preNode->next)
    {
        (*location)++;
        if(preNode->next->number == number)
            break;
    }
    return preNode;
}

void insert(position preNode, position newNode)//插入
{
    newNode->next = preNode->next;
    preNode->next = newNode;
    length++;

}

position delete(position preNode)//删除
{
    if(preNode->next == NULL)
        return NULL;
    position temp = preNode->next;
    preNode->next = temp->next;
    length--;
    return temp;
}

void sort(LIST head)//排序
{
    //已排好元素链的尾节点
    position preNode;
    //用于标记preNode后剩下元素中最小元素(的前驱)
    position target;
    //用于扫描
    position scanner;

    preNode = head;
    target = preNode;
    //当 preNode->next->next 不为空时循环
    while(target->next->next != NULL)
    {
        scanner = target->next;
        while(scanner->next != NULL)
        {
            if(target->next->number > scanner->next->number)
                target = scanner;
            scanner = scanner->next;
        }
        insert(preNode, delete(target));
        preNode = preNode->next;
        target = preNode;
    }
}

void display(LIST head)//输出链表
{
    position temp = head->next;
    while(temp != NULL)
    {
        printf("%d%c", temp->number, temp->next != NULL ? ' ' : '\n');
        temp = temp->next;
    }
}

void reverse(LIST head)//逆序重建
{
    position restHead = head->next;
    while(restHead->next != NULL)
        insert(head, delete(restHead));
}
