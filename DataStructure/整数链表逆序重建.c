#include <stdio.h>
#include <stdlib.h>
#define INPUT(x) {if(scanf("%d",&x) == 0){printf("��ȷ�ϲ����Ƿ���ȷ��\n");fflush(stdin);break;}}
struct NODE
{
    int number;
    struct NODE *next;
};

typedef struct NODE *position;
typedef struct NODE *LIST;

int length;

//����,��������Ԫ�ص�ǰ��
position search(LIST head, int number,int *location);
//����
void insert(position preNode, position newNode);
//ɾ��,���ر�ɾ���ڵ�λ��
position delete(position preNode);
//��������
void sort(LIST head);
//�������
void display(LIST head);
//�����ؽ�
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
        printf("��¼���ļ�data.in�е����ݲ��ѽ�����������.\n");
    }

    int op;
    int number;
    int location;
    do
    {
        printf("��ѡ����Ӧ���ֽ��в�����\n");
        printf("1:����      2:����      3:ɾ��      4:���� \n");
        printf("5:�������  6.�������  7:��ת����  8:�˳�\n");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            printf("��������Ҫ���ҵ����֣�");
            //��ֹ����Ĳ�������
            INPUT(number);
            if(search(numSet, number,&location)->next == NULL)
                printf("%d ���������У�\n", number);
            else
                printf("%d �������еĵ� %d λ.\n", number, location);
            break;
        case 2:
            printf("����������������֣�");
            //��ֹ����Ĳ�������
            INPUT(number);
            position temp1 = (position)malloc(sizeof(struct NODE));
            temp1->number = number;
            insert(numSet, temp1);
            printf("�����ɹ���%d �Ѳ��룡\n",number);
            break;
        case 3:
            printf("��������ɾ�������֣�");
            //��ֹ����Ĳ�������
            INPUT(number);
            position temp2 = delete(search(numSet, number, &location));
            if(temp2 == NULL)
                printf("����ʧ�ܣ���ɾ���ֲ��������У�\n");
            else
            {
                free(temp2);
                printf("�����ɹ���%d ��ɾ����\n", number);
            }
            break;
        case 4:
            sort(numSet);
            printf("�����ɹ����Ѱ��������У�\n");
            break;
        case 5:
            printf("�����ܸ���Ϊ %d.\n", length);
            break;
        case 6:
            printf("������������Ϊ��");
            display(numSet);
            break;
        case 7:
            reverse(numSet);
            printf("�����ɹ����������������ţ�\n");
            break;
        case 8: break;
        default:
            printf("��������ȷָ�\n");
            fflush(stdin);
            break;
        }
    printf("\n");
    }while(op != 8);

    return 0;
}


position search(LIST head, int number, int *location)//����
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

void insert(position preNode, position newNode)//����
{
    newNode->next = preNode->next;
    preNode->next = newNode;
    length++;

}

position delete(position preNode)//ɾ��
{
    if(preNode->next == NULL)
        return NULL;
    position temp = preNode->next;
    preNode->next = temp->next;
    length--;
    return temp;
}

void sort(LIST head)//����
{
    //���ź�Ԫ������β�ڵ�
    position preNode;
    //���ڱ��preNode��ʣ��Ԫ������СԪ��(��ǰ��)
    position target;
    //����ɨ��
    position scanner;

    preNode = head;
    target = preNode;
    //�� preNode->next->next ��Ϊ��ʱѭ��
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

void display(LIST head)//�������
{
    position temp = head->next;
    while(temp != NULL)
    {
        printf("%d%c", temp->number, temp->next != NULL ? ' ' : '\n');
        temp = temp->next;
    }
}

void reverse(LIST head)//�����ؽ�
{
    position restHead = head->next;
    while(restHead->next != NULL)
        insert(head, delete(restHead));
}
