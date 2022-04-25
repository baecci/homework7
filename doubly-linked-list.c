#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* llink;  //후방리스트를 가리키는 링크
	struct Node* rlink;  //전방리스트를 가리키는 링크
} listNode;


typedef struct Head {
	struct Node* first;  //헤더노드 
}headNode;

int initialize(headNode** h);
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;  //헤더노드 선언

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {  
		case 'z': case 'Z':
			initialize(&headnode);  //헤더노드의 메모리 할당
			break;
		case 'p': case 'P':
			printList(headnode);  //현재 리스트와 노드개수 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");  //key를 기준으로 리스트에 새로운 노드를 삽입
			scanf("%d", &key);
			insertNode(headnode, key);  
			break;
		case 'd': case 'D':
			printf("Your Key = ");  //원하는 key에 따라 노드를 삭제
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");  //리스트에 맨 뒤에 노드를 삽입
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);  //맨 뒤 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);  //리스트 맨 앞에 노드를 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);  //맨 앞 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);  //리스트 노드 역순으로 뒤집기 
			break;
		case 'q': case 'Q':
			freeList(headnode);  //리스트에 할당된 메모리를 전부 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if(*h != NULL)  //헤더노드가 공백인지 확인, 아니면 freeList호출하여 할당 메모리 전체 해제
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));  //헤더노드 메모리를 동적할당 후 리턴
	(*h)->first = NULL;
	return 1;
}


int freeList(headNode* h){
	
	listNode* p = h->first;  //처음부터 끝까지 메모리가 할당된 리스트를 해제

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);  //마지막으로 헤더노드까지 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //헤더노드가 공백인지 확인, 맞다면 문구 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;  //처음부터 생성된 리스트 끝까지 출력

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);  
}


int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //새로운 메모리를 할당하고 노드를 구성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)  //헤더노드가 링크한 노드가 없다면 처음에 삽입
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {  //맨 뒤 노드로 이동하여 링크를 연결
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}


int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;  
	listNode* trail = NULL;

	if(n->rlink == NULL) {  //노드가 하나인 경우 해당 노드 메모리 해제
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink != NULL) {  //맨 뒤 노드로 이동 후 해당 노드 메모리 해제
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;  //삭제되는 노드를 가리키는 앞의 노드 링크 NULL
	free(n);

	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //새로운 메모리를 할당하고 노드를 구성
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)  //헤더노드가 링크한 노드가 없다면 처음에 삽입
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}


int deleteFirst(headNode* h) {

	if (h->first == NULL)  //헤더노드가 링크한 노드가 없다면 문구 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;  //맨 앞 노드를 해제하기 앞서 연결 처리 후 해제
	h->first = n->rlink;

	free(n);

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) {  //헤더노드가 링크한 노드가 없다면 문구 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){  //trail과 middle 노드를 이용해 연결 리스트를 역순으로 뒤집기
		trail = middle;  //?
		middle = n;  //헤더노드 시작 링크를 middle에 
		n = n->rlink;  //n은 헤더노드가 가리키는 앞 노드로 이동 
		middle->rlink = trail;  //middle이 가리키는 후방 링크를 트레일로 초기는 널
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //새로운 메모리를 할당하고 노드를 구성
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)  //헤더노드가 링크한 노드가 없다면 처음에 삽입
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) {  //key보다 큰 key를 가진 노드 앞에 삽입
		if(n->key >= key) {
			if(n == h->first) {  //맨 앞에 삽입해야 할 경우 insertFirst함수 호출
				insertFirst(h, key);
			} else {  //삽입 위치에 따른 전, 후방 링크 변경
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);  //key가 가장 큰 경우 insertLast함수 호출로 맨 뒤에 삽입
	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)  //헤더노드가 링크한 노드가 없다면 문구 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {  //맨 앞 노드일 경우의 메모리 해제
				deleteFirst(h);
			} else if (n->rlink == NULL){  //맨 뒤 노드일 경우의 메모리 해제
				deleteLast(h);
			} else { //그 외의 경우엔, 해당 노드 메모리 해제 전 전, 후방 연결을 처리
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);  //해당 key의 노드를 발견하지 못하면 문구 출력
	return 1;
}


