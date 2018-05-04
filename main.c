#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX = 50; //자유공간리스트 노드 개수

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

listNode* free_s;// 자유공간 전역변수선언
Dnode* free_d;
int main()
{
	
	linkedList_h* L;
	char str[10];
	int c;
	int num, i;
	free_s = free_space_list();//자유공간 리스트 할당
	free_d = free_space_list_d();
	L = createLinkedList_h();
	display_menu();
	while (1) {
		printf("\n");
		printf("실행할 메뉴를 입력 : ");
		scanf("%d", &c);
		switch (c) {
		case 1:
			printf("삽입할 데이터 입력 : ");
			scanf("%s", str);
			addLastNode(L, str);
			printList(L);
			break;
		case 2:
			count = L->head;
			if (count != NULL) {
				printf("몇번째 데이터 뒤에 삽입하시겠습니까?");
				scanf("%d", &num);
				if (num == 0){
					printf("삽입할 데이터를 입력 : ");
					scanf("%s", str);
					addfirstNode(L, str);
				}
				else{
				for (i = 0; i < num - 1; i++) {
					count = count->link;
				}
				printf("삽입할 데이터를 입력 : ");
				scanf("%s", str);
				insertMiddleNode(L, count, str);
				}
				printList(L);
			}
			else {
				printf("저장된 데이터가 없습니다.\n");
			}
			break;
		case 3:
			printf("몇번째 데이터를 삭제하시겠습니까?");
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
			printf("삽입할 데이터를 입력 : ");
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
			printf("몇번 반복출력하시겠습니까?");
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
			printf("잘못 입력했다\n");
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


//자유공간리스트 생성 함수
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

//이중자유공간 리스트 생성함수
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

//공백연결 리스트 생성
linkedList_h* createLinkedList_h()
{
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}

//자유공간리스트에서 노드 할당
listNode* getNode()
{
	listNode* newNode;
	if (free_s == NULL)printf("할당실패\n");
	newNode = free_s;
	free_s = free_s->link;
	return newNode;
}

//이중자유공간리스트에서 노드 할당
Dnode* getdNode()
{
	Dnode* newd;
	if (free_d == NULL)printf("할당실패\n");
	newd = free_d;
	free_d = free_d->rlink;
	free_d->rlink->llink = NULL;
	return newd;
}

//리스트 출력하기
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

//리스트의 중간노드삽입
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

//리스트의 마지막 노드 삽입
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


//리스트로의 노드반환
void returnNode(listNode* old)
{
	old->link = free_s;
	free_s = old;
}

//리스트의 노드삭제 알고리즘
void deleteNode(linkedList_h* L, listNode* pre)
{
	listNode* old;
	if (L->head == NULL)printf("삭제할 데이터 없음\n");
	else {
		old = pre->link;
		if (old == NULL)return;
		pre->link = old->link;
	}
	returnNode(old);
}

//리스트 마지막노드 삭제 
void deleteLastNode(linkedList_h* L)
{
	listNode* pre;
	listNode* old;
	old = L->head;
	if (old == NULL) {
		printf("저장된 데이터가 없습니다.\n");
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


//리스트 첫번째에 노드 삽입
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

//리스트 전체 삭제
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


//원형리스트로 만들기
void circlelist(linkedList_h* L)
{
	listNode* p;
	p = L->head;
	while (p->link != NULL) {
		p = p->link;
	}
	p->link = L->head;
}

//원형리스트 출력
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

//원형리스트 해제
void delcircle(linkedList_h* L)
{
	listNode* p;
	p = L->head;
	while (p->link != L->head) {
		p = p->link;
	}
	p->link = NULL;
}

//이중연결로 만들기
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


//메뉴출력
void display_menu()
{
	printf("--------------메뉴--------------\n");
	printf("1.리스트 마지막에 노드 저장하기\n");
	printf("2.리스트 중간에 노드 삽입하기\n");
	printf("3.리스트 중간에 노드 삭제하기\n");
	printf("4.리스트 마지막 노드 삭제하기\n");
	printf("5.리스트 첫번째에 노드 삽입하기\n");
	printf("6.리스트 역순으로 저장하기\n");
	printf("7.리스트 전체 삭제\n");
	printf("8.원형리스트로 만든후 출력\n");
	printf("9.원형리스트 해제\n");
	printf("q.종료\n");
}