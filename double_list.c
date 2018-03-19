#include "double_list.h"

//创建双向链表
void init_list(struct node **phead, struct node **ptail) {
	if (!phead && !ptail) {
		fprintf(stderr, "Invalid arguments in init_list\n");
		return;
	}
	struct node *head = *phead;
	struct node *tail = *ptail;

	head = (struct node *)malloc(sizeof(struct node));
	if (!head) {
		fprintf(stderr, "malloc error in head node allocation\n");
		return;
	}
	memset(head, 0, sizeof(struct node));

	tail = (struct node *)malloc(sizeof(struct node));
	if (!tail) {
		fprintf(stderr, "malloc error in tail node allocation\n");
		return;
	}
	memset(tail, 0, sizeof(struct node));

	head->data = 0;
	tail->data = 0;
	head->prev = tail->next = NULL;
	head->next = tail;
	tail->prev = head;

	*phead = head;
	*ptail = tail;
	printf("init_list succeeded\n");

	return;
}

//创建节点
struct node *make_node(int data) {
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	if (!new_node) {
		fprintf(stderr, "malloc error in new node allocation\n");
		return NULL;
	}
	new_node->data = data;
	new_node->prev = new_node->next = NULL;

	return new_node;
}

//销毁节点
void free_node(struct node *pnode) {
	if (pnode) {
		free(pnode);
	}
	return;
}

//从链表头插入节点
void insert_from_head(struct node *head, struct node *pnode) {
	if (!head && !pnode) {
		fprintf(stderr, "Invalid arguments in insert_from_head\n");
		return;
	}
	//先改变待插入节点的前驱和后继指针
	pnode->next = head->next;
	pnode->prev = head;
	//再把pnode赋给两边的指针
	pnode->next->prev = pnode;
	pnode->prev->next = pnode;
	//上面这两句也可换成下面两句写法，此时顺序不可颠倒，因此不推荐下面的写法
	/*head->next->prev = pnode;
	head->next = pnode;*/

	printf("%d insert from head succeeded\n", pnode->data);
	return;
}

void insert_to_tail(struct node *tail, struct node *pnode) {
	if (!tail && !pnode) {
		fprintf(stderr, "Invalid arguments in insert_to_tail\n");
		return;
	}
	pnode->prev = tail->prev;
	pnode->next = tail;

	pnode->prev->next = pnode;
	pnode->next->prev = pnode;
	//上面这两句也可换成下面两句写法，此时顺序不可颠倒，因此不推荐下面的写法
	/*tail->prev->next = pnode;
	tail->prev = pnode;*/

	printf("%d insert to tail succeeded\n", pnode->data);
	return;
}

//打印双向链表
void print_double_list_in_sequence(struct node *head, struct node *tail) {
	if (!head && !tail) {
		fprintf(stderr, "Invalid arguments in print_duoble_list\n");
		return;
	}
	struct node *p = NULL;
	for (p = head->next; p != tail; p = p->next) {
		printf("%d\n", p->data);
	}
	return;
}

//逆序打印双向链表
void print_double_list_reversely(struct node *head, struct node *tail) {
	if (!head && !tail) {
		fprintf(stderr, "Invalid arguments in print_duoble_list\n");
		return;
	}
	struct node *p = NULL;
	for (p = tail->prev; p != head; p = p->prev) {
		printf("%d\n", p->data);
	}
	return;
}

//查找一个节点
struct node *search_node(struct node *head, struct node *tail, int data) {
	if (!head && !tail) {
		fprintf(stderr, "Invalid arguments in print_duoble_list\n");
		return NULL;
	}
	struct node *p = head->next;
	while (p != tail) {
		if (p->data == data) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

//删除一个节点
void delete_node(struct node *pnode) {
	if (!pnode) {
		fprintf(stderr, "Invalid argument in delete_node\n");
		return;
	}
	pnode->prev->next = pnode->next;
	pnode->next->prev = pnode->prev;
	printf("%d is deleted\n", pnode->data);
	free_node(pnode);
	return;
}

//销毁双向链表
void destroy_double_list(struct node **phead, struct node **ptail) {
	if (!phead && !ptail) {
		fprintf(stderr, "Invalid arguments in destroy_double_list\n");
		return;
	}
	struct node *head = *phead;
	struct node *tail = *ptail;

	struct node *p = NULL;
	for (p = head->next; p != tail;) { //释放除头、尾节点外的所有节点
	/*
		//注意，这样像单链表中的释放节点的做法是不对的
		//节点之间的指向关系丢失了，造成内存泄漏
		head = p->next;
		printf("%d is freed\n", p->data);
		free_node(p);
		p = head;
        */
    	//正确的做法
		delete_node(p);
		p = head->next;
	}
	free_node(head);
	free_node(tail);
	printf("tail is freed\n");
	*phead = NULL;
	*ptail = NULL;
	printf("The whole double list is freed\n");
	return;
}
