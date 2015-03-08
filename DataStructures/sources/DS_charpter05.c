#include "DS_charpter05.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*************************************************************************************************/
/***********************************************************************************
单链表节点抽象
***********************************************************************************/
// 不完全类型,申请节点的空间是需要加上item的大小
struct treenode{ tlink parent, left, right; };

tlink  tlink_new_tnode(int item_size, void* pitem)
{
	tlink newnode = (tlink)malloc(sizeof(*newnode) + item_size);
	void* dst;

	if (NULL != newnode)
	{
		newnode->parent = newnode->left = newnode->right = NULL;
		dst = (char *)newnode + sizeof(*newnode);
		memcpy(dst, pitem, item_size);
	}

	return newnode;
}

void   tlink_get_item(tlink p, int item_size, void *pitem)
{
	assert(NULL != p);
	assert(NULL != pitem);

	void *src = (char *)p + sizeof(*p);
	memcpy(pitem, src, item_size);
}

void   tlink_insert_left(tlink p, tlink newnode)
{
	if (newnode != NULL) newnode->parent = p;
	p->left = newnode;
}

void   tlink_insert_right(tlink p, tlink newnode)
{
	if (newnode != NULL) newnode->parent = p;
	p->right = newnode;
}

void tlink_insert_both(tlink p, tlink left, tlink right)
{
	if (left != NULL)	left->parent = p;
	p->left = left;

	if (right != NULL)	right->parent = p;
	p->right = right;


}

tlink  tlink_get_lchild(tlink p)
{
	return p->left;
}
tlink  tlink_get_rchild(tlink p)
{
	return p->right;
}

/*************************************************************************************************/
// 二叉树抽象
struct binary_tree
{
	tlink root;
	int item_size;
};

btree btree_open(int item_size)
{
	assert(item_size > 0);

	btree bt = (btree)malloc(sizeof(*bt));
	if (NULL == bt) return bt;

	bt->item_size = item_size;
	bt->root = NULL;

	return bt;
}

static void btree_del(tlink root)
{
	if (NULL != root)
	{
		btree_del(root->left);
		btree_del(root->right);
		free(root);
	}
}

void btree_close(btree bt)
{
	btree_del(bt->root);

	free(bt);
}

int btree_is_empty(btree bt)
{
	assert(NULL != bt);

	return (bt->root == NULL);
}

tlink btree_make_btree(btree bt, tlink left, void *pitem, tlink right)
{
	assert(bt != NULL);
	assert(pitem != NULL);

	bt->root = tlink_new_tnode(bt->item_size, pitem);
	if (NULL == bt->root)	return NULL;

	tlink_insert_both(bt->root, left, right);

	return bt->root;
}

void btree_get_item(btree bt, tlink root, void *pitem)
{
	assert(bt != NULL);
	assert(root != NULL);
	assert(pitem != NULL);

	tlink_get_item(root, bt->item_size, pitem);
}

tlink btree_get_lchild(btree bt, tlink root)
{
	if (NULL == root)	return NULL;
	else	return tlink_get_lchild(root);
}

tlink btree_get_rchild(btree bt, tlink root)
{
	if (NULL == root)	return NULL;
	else	return tlink_get_rchild(root);
}