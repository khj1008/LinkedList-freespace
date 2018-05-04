#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX = 50; //������������Ʈ ��� ����

typedef struct ListNode {
	char data[10];
	struct ListNode* link;
}listNode;

typedef struct Dnode {
	struct Dnode* llink;
	char data[10];
	struct Dnode* rlink;
}Dnode;

typedef struct {
	listNode* head;
}linkedList_h;

listNode* free_space_list();
linkedList_h* createLinkedList_h();
listNode* getNode();
listNode* count;
Dnode* getdNode();
Dnode* free_space_list_d();
void printList(linkedList_h* L);
void addLastNode(linkedList_h* L, char* x);
void returnNode(listNode* old);
void insertMiddleNode(linkedList_h* L, listNode* pre, char* x);
void deleteNode(linkedList_h* L, listNode* pre);
void deleteLastNode(linkedList_h* L);
void addfirstNode(linkedList_h* L, char* str);
void reverse(linkedList_h* L);
void freelinkedlist(linkedList_h* L);
void circlelist(linkedList_h* L);
void printcircle(linkedList_h* L, int num);
void delcircle(linkedList_h* L);
void display_menu();

listNode* free_s;// �������� ������������
Dnode* free_d;
int main()
{
	
	linkedList_h* L;
	char str[10];
	int c;
	int num, i;
	free_s = free_space_list();//�������� ����Ʈ �Ҵ�
	free_d = free_space_list_d();
	L = createLinkedList_h();
	display_menu();
	while (1) {
		printf("\n");
		printf("������ �޴��� �Է� : ");
		scanf("%d", &c);
		switch (c) {
		case 1:
			printf("������ ������ �Է� : ");
			scanf("%s", str);
			addLastNode(L, str);
			printList(L);
			break;
		case 2:
			count = L->head;
			if (count != NULL) {
				printf("���° ������ �ڿ� �����Ͻðڽ��ϱ�?");
				scanf("%d", &num);
				if (num == 0){
					printf("������ �����͸� �Է� : ");
					scanf("%s", str);
					addfirstNode(L, str);
				}
				else{
				for (i = 0; i < num - 1; i++) {
					count = count->link;
				}
				printf("������ �����͸� �Է� : ");
				scanf("%s", str);
				insertMiddleNode(L, count, str);
				}
				printList(L);
			}
			else {
				printf("����� �����Ͱ� �����ϴ�.\n");
			}
			break;
		case 3:
			printf("���° �����͸� �����Ͻðڽ��ϱ�?");
			scanf("%d", &num);
			count = L->head;
			for (i = 0; i < num-2; i++) {
				count = count->link;
			}
			deleteNode(L, count);
			printList(L);
			break;
		case 4:
			deleteLastNode(L);
			printList(L);
			break;
		case 5:
			printf("������ �����͸� �Է� : ");
			scanf("%s", str);
			addfirstNode(L, str);
			printList(L);
			break;
		case 6:
			reverse(L);
			printList(L);
			break;
		case 7:
			freelinkedlist(L);
			printList(L);
			break;
		case 8:
			circlelist(L);
			printf("��� �ݺ�����Ͻðڽ��ϱ�?");
			scanf("%d", &num);
			printcircle(L, num);
			break;
		case 9:
			delcircle(L);
			printList(L);
			break;
		case 0:
			return 0;
		default:
			printf("�߸� �Է��ߴ�\n");
			break;
		}
	}
	
	/*
	scanf("%s", str);
	addLastNode(L, str);
	printList(L);
	scanf("%s", str);
	addLastNode(L, str);
	printList(L);
	scanf("%s", str);
	addLastNode(L, str);
	printList(L);
	scanf("%s", str);
	printList(L);
	deleteNode(L, pre2);
	printList(L);
	return;
	*/
		
}


//������������Ʈ ���� �Լ�
listNode* free_space_list()
{
	listNode* free = NULL;
	free = (listNode*)malloc(MAX * sizeof(listNode));
	for (int i = 0; i < MAX - 1; i++) {
		free[i].link = &free[i + 1];
	}
	free[MAX - 1].link = NULL;
	return free;
}

//������������ ����Ʈ �����Լ�
Dnode* free_space_list_d()
{
	Dnode* free = NULL;
	free = (Dnode*)malloc(MAX * sizeof(Dnode));
	free[0].llink = NULL;
	for (int i = 0; i < MAX - 1; i++) {
		free[i].rlink = &free[i + 1];
		free[i + 1].llink = &free[i];
	}
	free[MAX - 1].rlink = NULL;
	return free;
}

//���鿬�� ����Ʈ ����
linkedList_h* createLinkedList_h()
{
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}

//������������Ʈ���� ��� �Ҵ�
listNode* getNode()
{
	listNode* newNode;
	if (free_s == NULL)printf("�Ҵ����\n");
	newNode = free_s;
	free_s = free_s->link;
	return newNode;
}

//����������������Ʈ���� ��� �Ҵ�
Dnode* getdNode()
{
	Dnode* newd;
	if (free_d == NULL)printf("�Ҵ����\n");
	newd = free_d;
	free_d = free_d->rlink;
	free_d->rlink->llink = NULL;
	return newd;
}

//����Ʈ ����ϱ�
void printList(linkedList_h* L)
{
	listNode* p;
	printf("L = (");
	p = L->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->link;
		if (p != NULL)printf(",");
	}
	printf(") \n");
}

//����Ʈ�� �߰�������
void insertMiddleNode(linkedList_h* L, listNode* pre, char* x)
{
	listNode* newNode;
	newNode = getNode();
	strcpy(newNode->data, x);
	if (L == NULL) {
		L->head = newNode;
		newNode->link = NULL;
	}
	else {
		newNode->link = pre->link;
		pre->link = newNode;
	}
}

//����Ʈ�� ������ ��� ����
void addLastNode(linkedList_h* L, char* x)
{
	listNode* newNode;
	newNode = getNode();
	listNode* p;
	strcpy(newNode->data, x);
	newNode->link = NULL;
	if (L->head == NULL) {
		L->head = newNode;
		return;
	}
	p = L->head;
	while (p->link != NULL)p = p->link;
	p->link = newNode;
}


//����Ʈ���� ����ȯ
void returnNode(listNode* old)
{
	old->link = free_s;
	free_s = old;
}

//����Ʈ�� ������ �˰���
void deleteNode(linkedList_h* L, listNode* pre)
{
	listNode* old;
	if (L->head == NULL)printf("������ ������ ����\n");
	else {
		old = pre->link;
		if (old == NULL)return;
		pre->link = old->link;
	}
	returnNode(old);
}

//����Ʈ ��������� ���� 
void deleteLastNode(linkedList_h* L)
{
	listNode* pre;
	listNode* old;
	old = L->head;
	if (old == NULL) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return;
	}
	if (old->link == NULL) {
		L->head = NULL;
		returnNode(old);
	}
	else {
		while (old->link != NULL) {
			pre = old;
			old = old->link;
		}
		pre->link = NULL;
		returnNode(old);
	}
	
}


//����Ʈ ù��°�� ��� ����
void addfirstNode(linkedList_h* L, char* str)
{
	listNode* newNode;
	newNode = getNode();
	strcpy(newNode->data, str);
	newNode->link = NULL;
	if (L->head == NULL)
	{
		L->head = newNode;
	}
	else {
		newNode->link = L->head;
		L->head = newNode;
	}
}
//
void reverse(linkedList_h* L)
{
	listNode* p;
	listNode* q;
	listNode* r;

	p = L->head;
	q = NULL;
	r = NULL;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	L->head = q;
}

//����Ʈ ��ü ����
void freelinkedlist(linkedList_h* L)
{
	listNode* old;
	L->head = NULL;
	while (L->head != NULL) {
		old = L->head;
		L->head = L->head->link;
		returnNode(old);
	}
}


//��������Ʈ�� �����
void circlelist(linkedList_h* L)
{
	listNode* p;
	p = L->head;
	while (p->link != NULL) {
		p = p->link;
	}
	p->link = L->head;
}

//��������Ʈ ���
void printcircle(linkedList_h* L, int num)
{
	listNode* p;
	int i=0;
	p = L->head;
	printf("L=(");
	while (i < num) {
		if (p->link == L->head)i++;
		printf("%s", p->data);
		p = p->link;
		if (i < num)printf(",");
	}
	printf(")\n");
}

//��������Ʈ ����
void delcircle(linkedList_h* L)
{
	listNode* p;
	p = L->head;
	while (p->link != L->head) {
		p = p->link;
	}
	p->link = NULL;
}

//���߿���� �����
//void changedouble(linkedList_h* L)
//{
//	Dnode *newd;
//	listNode* p;
//	p = L->head;
//	while (1) {
//		newd = getdNode();
//		newd = p;
//		strcpy(newd->data, p->data);
//		newd->rlink = p->link;
//		newd->llink=
//	}
//}


//�޴����
void display_menu()
{
	printf("--------------�޴�--------------\n");
	printf("1.����Ʈ �������� ��� �����ϱ�\n");
	printf("2.����Ʈ �߰��� ��� �����ϱ�\n");
	printf("3.����Ʈ �߰��� ��� �����ϱ�\n");
	printf("4.����Ʈ ������ ��� �����ϱ�\n");
	printf("5.����Ʈ ù��°�� ��� �����ϱ�\n");
	printf("6.����Ʈ �������� �����ϱ�\n");
	printf("7.����Ʈ ��ü ����\n");
	printf("8.��������Ʈ�� ������ ���\n");
	printf("9.��������Ʈ ����\n");
	printf("q.����\n");
}