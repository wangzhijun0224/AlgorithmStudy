#include "DS_charpter05_1.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define true 1
#define false 0

/*************************************************************************************************/
struct thread_treenode
{
	short int left_thread, right_thread; // 0: 不是线索 1：是线索
	thread_tlink left, right;
};

struct thread_binary_tree
{
	thread_tlink guard;
	int item_size;
};

/*************************************************************************************************/
static thread_tlink  thread_tlink_new_tnode(int item_size, void* pitem)
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

static int btree_create(thread_tlink *root, void* pitem, int* pindex, int item_size, void* enditem)
{
	void* pcuritem = (char*)pitem + (*pindex)*item_size;

	if (0 == memcmp(pcuritem, enditem, item_size))
	{
		return 0;
	}

	*root = thread_tlink_new_tnode(item_size, pcuritem);
	if (NULL == *root)  return 0;

	(*pindex)++;
	btree_create(&((*root)->left), pitem, pindex, item_size, enditem);
	(*pindex)++;
	btree_create(&((*root)->right), pitem, pindex, item_size, enditem);
	return 1;
}

#if (THREAD_INORDER)
static void inorder_thread(thread_tlink* prev, thread_tlink root)
{
 	if (NULL == root)   return;

	inorder_thread(prev, root->left);
	
 	if (NULL == root->left)
 	{
     	root->left_thread = true;
     	root->left = *prev;
 	}
 	if (NULL == (*prev)->right)
 	{
     	(*prev)->right_thread = true;
     	(*prev)->right = root;
 	}
 	*prev = root;
	
 	inorder_thread(prev, root->right);
}
#elif (THREAD_PREORDER)
static void preorder_thread(thread_tlink* prev, thread_tlink root)
{
 	if (NULL == root)   return;

	if (NULL == root->left)
 	{
     	root->left_thread = true;
     	root->left = *prev;
 	}
 	if (NULL == (*prev)->right)
 	{
     	(*prev)->right_thread = true;
     	(*prev)->right = root;
 	}
 	*prev = root;

	if (true != root->left_thread) preorder_thread(prev, root->left);
 	if (true != root->right_thread) preorder_thread(prev, root->right);
}
#endif

static void thread_btree_order_thread(thread_btree bt)
{
 	thread_tlink prev = bt->guard;

	#if (THREAD_INORDER)
 	inorder_thread(&prev, prev->left);
 	#elif (THREAD_PREORDER)
 	preorder_thread(&prev, prev->left);
 	#endif

	if (NULL == prev->right)
 	{
     	prev->right_thread = true;
     	prev->right = bt->guard;
 	}
}

static void thread_btree_preorder_copy(tlink src_root, int item_size, thread_tlink* root)
{
	char* src = _tlink_get_itemaddr(src_root);

	if (NULL != src_root)
	{
		*root = thread_tlink_new_tnode(item_size, src);
		assert(NULL != *root);

		thread_btree_preorder_copy(tlink_get_lchild(src_root), item_size, &((*root)->left));
		thread_btree_preorder_copy(tlink_get_rchild(src_root), item_size, &((*root)->right));
	}
}

/***********************************************************************************
对于任一结点P：
1) 如果p的right_thread为true,则根据线索的定义,ptr的中序后继是ptr->right;
2)否则,从ptr的右孩子开始,沿着左孩子一直走下去,
    直到一个节点的left_thread为true,则这个节点就是ptr的中序后继
***********************************************************************************/
#if (THREAD_INORDER)
static thread_tlink inorder_next(thread_tlink cur)
{
 	thread_tlink tmp = cur->right;

	if (false == cur->right_thread)
 	{
     	while (false == tmp->left_thread)
     	{
         	tmp = tmp->left;
     	}
 	}
 
 	return tmp;
}
#elif (THREAD_PREORDER)
static thread_tlink preorder_next(thread_tlink cur)
{
 	if (false == cur->left_thread)
 	{
     	return cur->left;
 	}

	return cur->right;
}
#endif

/*************************************************************************************************/
thread_btree thread_btree_open(int item_size)
{
	assert(item_size > 0);

	thread_btree bt = (thread_btree)malloc(sizeof(*bt));
	assert(NULL != bt);

	bt->item_size = item_size;

	thread_tlink guard = thread_tlink_new_tnode(0, NULL); // 头结点不需要数据域
	guard->left_thread = true;
	guard->left = guard;
	guard->right_thread = false;
	guard->right = guard;

	bt->guard = guard;

	return bt;
}

void thread_btree_create(thread_btree bt, void *pitem, void* penditem)
{
	assert(NULL != pitem);
	assert(NULL != penditem);

	// 1. create binary tree
	int index = 0;
	btree_create(&(bt->guard->left), pitem, &index, bt->item_size, penditem);

	// 2. set guard 's left_thread poriority
	if(bt->guard->left != bt->guard)    bt->guard->left_thread = false;

	// 3. thread
	thread_btree_order_thread(bt);
}

thread_btree thread_btree_create_by_btree(btree src_bt)
{
	assert(NULL != src_bt);

	int item_size = btree_get_itemsize(src_bt);

	thread_btree thread_bt = thread_btree_open(item_size);

	thread_btree_preorder_copy(btree_get_root(src_bt), item_size, &(thread_bt->guard->left));

	if(thread_bt->guard->left != thread_bt->guard)    thread_bt->guard->left_thread = false;

	thread_btree_order_thread(thread_bt);

	return thread_bt;
}

int thread_btree_order(thread_btree bt, void* pitem)
{
	 assert(NULL != bt);
	 assert (NULL != pitem);

	int count = 0;
	thread_tlink guard = bt->guard;
	char* src, *dst;
	int item_size = bt->item_size;

	dst = pitem;
	#if (THREAD_INORDER)
	for (thread_tlink tmp = inorder_next(guard); tmp != guard; tmp = inorder_next(tmp))
	#elif (THREAD_PREORDER)
	for (thread_tlink tmp = preorder_next(guard); tmp != guard; tmp = preorder_next(tmp))
	#endif
	{
	 src = (char*)tmp + sizeof(*tmp);
	 memcpy(dst, src, item_size);
	 dst += item_size;
	 count++;
	}

	return count;
}

void thread_btree_close(thread_btree bt)
{
	assert(NULL != bt);

	thread_tlink guard = bt->guard;
	#if (THREAD_INORDER)
	thread_tlink tmp = inorder_next(guard);
	#elif (THREAD_PREORDER)
	thread_tlink tmp = preorder_next(guard);
	#endif
	
	while (tmp != guard)
	{
		thread_tlink cur = tmp;
		 
	 	#if (THREAD_INORDER)
	 	tmp = inorder_next(tmp);
	 	#elif (THREAD_PREORDER)
		tmp = preorder_next(tmp);
	 	#endif
		 
		free(cur);
	}

	free(guard);

	free(bt);
}