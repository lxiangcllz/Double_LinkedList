#ifndef _DOUBLE_LIST_H_
#define _DOUBLE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node *prev;
	struct node *next;
};

//创建双向链表
void init_list(struct node **phead, struct node **ptail);

//创建节点
struct node *make_node(int data);

//销毁节点
void free_node(struct node *pnode);

//从链表头插入节点
void insert_from_head(struct node *head, struct node *pnode);

//从链表尾插入节点
void insert_to_tail(struct node *tail, struct node *pnode);

//顺序打印双向链表
void print_double_list_in_sequence(struct node *head, struct node *tail);

//逆序打印双向链表
void print_double_list_reversely(struct node *head, struct node *tail);

//查找一个节点
struct node *search_node(struct node *head, struct node *tail, int data);

//删除一个节点
void delete_node(struct node *pnode);

//销毁双向链表
void destroy_double_list(struct node **phead, struct node **ptail);
#endif
