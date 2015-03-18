#include "DS_charpter05_1.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define true	1
#define	false	0

/*************************************************************************************************/
struct thread_treenode
{
	short int left_thread, right_thread;	// 0: 不是线索 1：是线索
	thread_tlink left, right;
};

struct thread_binary_tree
{
	thread_tlink guard;
	int item_size;
};

/*************************************************************************************************/
thread_tlink  thread_tlink_new_tnode(int item_size, void* pitem)
{
	thread_tlink newnode = (thread_tlink)malloc(sizeof(*newnode) + item_size);
	assert(NULL != newnode);

	void* dst;

	newnode->left_thread = newnode->right_thread = false;
	newnode->left = newnode->right = NULL;

	if (item_size > 0)
	{
		dst = (char *)newnode + sizeof(*newnode);
		memcpy(dst, pitem, item_size);
	}

	return newnode;
}

/*************************************************************************************************/
thread_btree thread_btree_open(int item_size)
{
	assert(item_size > 0);

	thread_btree bt = (thread_btree)malloc(sizeof(*bt));
	assert(NULL != bt);

	bt->item_size = item_size;
	
	thread_tlink guard = thread_tlink_new_tnode(0, NULL);	// 头结点不需要数据域
	guard->left_thread = true;
	guard->left = guard;
	guard->right_thread = false;
	guard->right = guard;

	bt->guard = guard;

	return bt;
}