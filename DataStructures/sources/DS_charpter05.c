#include "DS_charpter04.h"  // stack, queue

#include "DS_charpter05.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*************************************************************************************************/
/***********************************************************************************
������ڵ����
***********************************************************************************/
// ����ȫ����,����ڵ�Ŀռ�����Ҫ����item�Ĵ�С
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

tlink* tlink_get_lchild_addr(tlink p)
{
	return &(p->left);
}
tlink* tlink_get_rchild_addr(tlink p)
{
	return &(p->right);
}

/*************************************************************************************************/
// ����������
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

static int btree_create(tlink *root, void* pitem, int* pindex, int item_size, void* enditem)
{
	void* pcuritem = (char*)pitem + (*pindex)*item_size;

	if (0 == memcmp(pcuritem, enditem, item_size))
	{
		return 0;
	}

	*root = tlink_new_tnode(item_size, pcuritem);
	if (NULL == *root)  return 0;

	(*pindex)++;
	btree_create(tlink_get_lchild_addr(*root), pitem, pindex, item_size, enditem);
	(*pindex)++;
	btree_create(tlink_get_rchild_addr(*root), pitem, pindex, item_size, enditem);
	return 1;
}

void btree_make_btree(btree bt, void *pitem, void* penditem)
{
	int index = 0;
	btree_create(&(bt->root), pitem, &index, bt->item_size, penditem);
}

void btree_get_item(btree bt, tlink root, void *pitem)
{
	assert(bt != NULL);
	assert(root != NULL);
	assert(pitem != NULL);

	tlink_get_item(root, bt->item_size, pitem);
}
tlink btree_get_root(btree bt)
{
	return bt->root;
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

/*************************************************************************************************/
/***********************************************************************************
�ݹ��ǰ�����: ���ڵ�-����-�Һ��ӵ�˳�����
***********************************************************************************/
static void preorder_recursion(btree bt, tlink root, void* pitem, int* pindex)
{
	char *dst;

	if (NULL != root)
	{
		dst = (char*)pitem + (*pindex)*sizeof(char);
		btree_get_item(bt, root, dst);
		(*pindex)++;
		preorder_recursion(bt, btree_get_lchild(bt, root), pitem, pindex);
		preorder_recursion(bt, btree_get_rchild(bt, root), pitem, pindex);
	}
}

/***********************************************************************************
�ݹ���������: ����-���ڵ�-�Һ���
***********************************************************************************/
static void inorder_recursion(btree bt, tlink root, void* pitem, int* pindex)
{
	char *dst;

	if (NULL != root)
	{
		inorder_recursion(bt, btree_get_lchild(bt, root), pitem, pindex);
		dst = (char*)pitem + (*pindex)*sizeof(char);
		btree_get_item(bt, root, dst);
		(*pindex)++;
		inorder_recursion(bt, btree_get_rchild(bt, root), pitem, pindex);
	}
}

/***********************************************************************************
�ݹ��������: ����-�Һ���-���ڵ�
***********************************************************************************/
static void postorder_recursion(btree bt, tlink root, void* pitem, int* pindex)
{
	char *dst;

	if (NULL != root)
	{
		postorder_recursion(bt, btree_get_lchild(bt, root), pitem, pindex);
		postorder_recursion(bt, btree_get_rchild(bt, root), pitem, pindex);
		dst = (char*)pitem + (*pindex)*sizeof(char);
		btree_get_item(bt, root, dst);
		(*pindex)++;
	}
}

int btree_preorder_recursion(btree bt, void* pitem)
{
	tlink root = NULL;
	int index = 0;
	assert(NULL != bt);
	assert(NULL != pitem);

	root = btree_get_root(bt);

	preorder_recursion(bt, root, pitem, &index);

	return index;
}

int btree_inorder_recursion(btree bt, void* pitem)
{
	tlink root = NULL;
	int index = 0;
	assert(NULL != bt);
	assert(NULL != pitem);

	root = btree_get_root(bt);

	inorder_recursion(bt, root, pitem, &index);

	return index;
}

int btree_postorder_recursion(btree bt, void* pitem)
{
	tlink root = NULL;
	int index = 0;
	assert(NULL != bt);
	assert(NULL != pitem);

	root = btree_get_root(bt);

	postorder_recursion(bt, root, pitem, &index);

	return index;
}

/*************************************************************************************************/

/***********************************************************************************
�ǵݹ��ǰ�����:
����ǰ��������ʵ�˳�����ȷ��ʸ��ڵ㣬Ȼ���ٷֱ�������Ӻ��Һ��ӣ���������һ�ڵ㣬��ɿ����Ǹ��ڵ㣬
��˿�ֱ�ӷ��ʣ�������֮���������Ӳ�Ϊ�գ�����ͬ�����������������;����������������ʱ���ٷ���������������

������һ���P��
1)���ʽ��P���������P��ջ;
2)�жϽ��P�������Ƿ�Ϊ�գ���Ϊ�գ����ջ��ȡ��ջ��Ԫ�أ�����ջ�������Һ�����Ϊ��ǰ�Ľ��P��ѭ����1);
����Ϊ�գ���P��������Ϊ��ǰ�Ľ��P;
3)ֱ��ջΪ�գ������������
***********************************************************************************/
int btree_preorder_norecursion(btree bt, void* pitem)
{
	tlink root = btree_get_root(bt);
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	stack_slist stk = stack_slist_open(sizeof(root));

	while (1)
	{
		while (NULL != root)
		{
			dst = (char*)pitem + index*sizeof(char);
			btree_get_item(bt, root, dst);
			index++;
			stack_slist_insert(stk, &root);
			root = btree_get_lchild(bt, root);
		}

		if (0 == stack_slist_del(stk, &root)) break;    // ջΪ�� 

		root = btree_get_rchild(bt, root);
	}

	stack_slist_close(stk);

	return index;
}


/***********************************************************************************
�ǵݹ��ǰ�����2:
***********************************************************************************/
int btree_preorder_norecursion2(btree bt, void* pitem)
{
	tlink root = btree_get_root(bt), tmplink;
	stack_slist stk;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	if (NULL == root)   return 0; // �սڵ㲻��ջ

	stk = stack_slist_open(sizeof(root));

	stack_slist_insert(stk, &root);

	while (1)
	{
		if (0 == stack_slist_top(stk, &root))    break;

		dst = (char*)pitem + index*sizeof(char);
		btree_get_item(bt, root, dst);
		index++;

		stack_slist_pop(stk);

		tmplink = btree_get_rchild(bt, root);
		if (NULL != tmplink) stack_slist_insert(stk, &tmplink);

		tmplink = btree_get_lchild(bt, root);
		if (NULL != tmplink) stack_slist_insert(stk, &tmplink);
	}

	stack_slist_close(stk);

	return index;
}

/***********************************************************************************
�ǵݹ���������:
�������������˳�򣬶�����һ�ڵ㣬���ȷ��������ӣ������ӽڵ��ֿɿ������ڵ㣬
Ȼ��������������ӽڵ㣬ֱ����������Ϊ�յĽڵ�Ž��з��ʣ�Ȼ����ͬ�Ĺ����������������

������һ���P��
1)�����P�����Ӳ�Ϊ�գ���P��ջ����P��������Ϊ��ǰ��P��Ȼ��ѭ����ǰ�ж�;
��P������Ϊ�գ����ջ��ȡ��ջ��Ԫ�أ�����ջ���ڵ㣬Ȼ�󽫵�ǰ��P��Ϊջ���ڵ���Һ���;
3)ֱ��ջΪ�գ������������
***********************************************************************************/
int btree_inorder_norecursion(btree bt, void* pitem)
{
	tlink tmplink;
	stack_slist stk;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	tmplink = btree_get_root(bt);
	stk = stack_slist_open(sizeof(tmplink));

	while (1)
	{
		while (tmplink != NULL)
		{
			stack_slist_insert(stk, &tmplink);
			tmplink = btree_get_lchild(bt, tmplink);
		}

		if (0 == stack_slist_del(stk, &tmplink)) break;

		dst = (char*)pitem + index*sizeof(char);
		index++;
		btree_get_item(bt, tmplink, dst);

		tmplink = btree_get_rchild(bt, tmplink);
	}

	stack_slist_close(stk);

	return index;
}

/***********************************************************************************
�ǵݹ��������1:
˼·�� ������һ�ڵ�P��������ջ��Ȼ������������һֱ����������ֱ���ѵ�����ŷ���ӵĽڵ�,
��ʱ�ýڵ������ջ��������ʱ���ܽ����ջ�����ʣ������Һ��ӻ�δ�����ʡ����ԣ�������
����ͬ�Ĺ���������������д��������������Һ���ʱ���ýڵ��ֳ�����ջ������ʱ
���Խ����ջ�����ʡ�
����ÿ���ڵ㶼���γ�����ջ����ֻ���ڵڶ��γ�����ջ��ʱ�����ܷ���������ˣ�������
һ��������ʶ�ýڵ��Ƿ��һ�γ�����ջ����
***********************************************************************************/
typedef struct pstorder_stack_item
{
	tlink link;
	int   flag; // 1: ��һ�γ�����ջ�� 0:���ǵ�һ�γ�����ջ��
}pstorder_stack_item;

int btree_postorder_norecursion(btree bt, void* pitem)
{
	tlink root = btree_get_root(bt);
	pstorder_stack_item stk_item;
	stack_slist stk;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	stk = stack_slist_open(sizeof(stk_item));

	while (1)
	{
		while (root != NULL)
		{
			stk_item.flag = 1;
			stk_item.link = root;
			stack_slist_insert(stk, &stk_item);
			root = btree_get_lchild(bt, root);
		}

		if (0 == stack_slist_del(stk, &stk_item)) break;

		if (1 == stk_item.flag) // ��һ����ջ��
		{
			stk_item.flag = 0;
			stack_slist_insert(stk, &stk_item);
			root = btree_get_rchild(bt, stk_item.link); // ����������
		}
		else   // �ڶ�����ջ��
		{
			dst = (char*)pitem + index*sizeof(char);
			btree_get_item(bt, stk_item.link, dst);
			index++;
			root = NULL;
		}
	}

	stack_slist_close(stk);

	return index;
}


/***********************************************************************************
�ǵݹ��������2:
˼·��Ҫ��֤���ڵ������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ�ڵ�P���Ƚ�����ջ��
���P���������Ӻ��Һ��ӣ������ֱ�ӷ�����;����P�������ӻ����Һ��ӣ�������
���Ӻ��Һ��Ӷ��ѱ����ʹ���,��ͬ������ֱ�ӷ��ʸýڵ㡣���������������,��P
���Һ��Ӻ�����������ջ,�����ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ���������Һ���ǰ��
�����ʣ����Ӻ��Һ��Ӷ��ڸ��ڵ�ǰ�汻���ʡ�
***********************************************************************************/
int btree_postorder_norecursion2(btree bt, void* pitem)
{
	tlink root = btree_get_root(bt), tmplink;
	tlink pre = NULL;
	stack_slist stk;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	if (NULL == root)   return 0;

	stk = stack_slist_open(sizeof(root));


	stack_slist_insert(stk, &root);

	while (1)
	{
		if (0 == stack_slist_top(stk, &root))    break;

		if ((NULL == btree_get_lchild(bt, root) && NULL == btree_get_rchild(bt, root))
			|| (NULL != pre && (pre == btree_get_lchild(bt, root) || pre == btree_get_rchild(bt, root)))
			)
		{
			dst = (char*)pitem + index*sizeof(char);
			btree_get_item(bt, root, dst);
			index++;

			stack_slist_pop(stk);
			pre = root;
		}
		else
		{
			tmplink = btree_get_rchild(bt, root);
			if (NULL != tmplink) stack_slist_insert(stk, &tmplink);

			tmplink = btree_get_lchild(bt, root);
			if (NULL != tmplink) stack_slist_insert(stk, &tmplink);
		}
	}

	stack_slist_close(stk);

	return index;
}


/***********************************************************************************
�������������:
һ��һ��������ұ���
***********************************************************************************/
int btree_levelorder(btree bt, void* pitem)
{
	queue_slist qe;
	tlink root = btree_get_root(bt), tmplink;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	if (NULL == root)   return 0;

	qe = queue_slist_open(sizeof(root));

	queue_slist_insert(qe, &root);

	while (1)
	{
		if (0 == queue_slist_del(qe, &root))    break;

		dst = (char*)pitem + index*sizeof(char);
		btree_get_item(bt, root, dst);
		index++;

		tmplink = btree_get_lchild(bt, root);
		if (NULL != tmplink) queue_slist_insert(qe, &tmplink);

		tmplink = btree_get_rchild(bt, root);
		if (NULL != tmplink) queue_slist_insert(qe, &tmplink);
	}

	queue_slist_close(qe);

	return index;
}


/***********************************************************************************
�������������:
һ��һ������������
***********************************************************************************/
int btree_levelorderR(btree bt, void* pitem)
{
	queue_slist qe;
	tlink root = btree_get_root(bt), tmplink;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	if (NULL == root)   return 0;

	qe = queue_slist_open(sizeof(root));

	queue_slist_insert(qe, &root);

	while (1)
	{
		if (0 == queue_slist_del(qe, &root))    break;

		dst = (char*)pitem + index*sizeof(char);
		btree_get_item(bt, root, dst);
		index++;

		tmplink = btree_get_rchild(bt, root);
		if (NULL != tmplink) queue_slist_insert(qe, &tmplink);

		tmplink = btree_get_lchild(bt, root);
		if (NULL != tmplink) queue_slist_insert(qe, &tmplink);
	}

	queue_slist_close(qe);

	return index;
}
