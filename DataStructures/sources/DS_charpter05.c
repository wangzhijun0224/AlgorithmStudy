#include "DS_charpter04.h"  // stack, queue

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

tlink* tlink_get_lchild_addr(tlink p)
{
	return &(p->left);
}
tlink* tlink_get_rchild_addr(tlink p)
{
	return &(p->right);
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
递归版前序遍历: 根节点-左孩子-右孩子的顺序遍历
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
递归版中序遍历: 左孩子-根节点-右孩子
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
递归版后序遍历: 左孩子-右孩子-根节点
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
非递归版前序遍历:
根据前序遍历访问的顺序，优先访问根节点，然后再分别访问左孩子和右孩子，即对于任一节点，其可看做是根节点，
因此可直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树;当访问完其左子树时，再访问它的右子树。

对于任一结点P：
1)访问结点P，并将结点P入栈;
2)判断结点P的左孩子是否为空，若为空，则从栈中取出栈顶元素，并将栈顶结点的右孩子置为当前的结点P，循环至1);
若不为空，则将P的左孩子置为当前的结点P;
3)直到栈为空，则遍历结束。
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

		if (0 == stack_slist_del(stk, &root)) break;    // 栈为空 

		root = btree_get_rchild(bt, root);
	}

	stack_slist_close(stk);

	return index;
}


/***********************************************************************************
非递归版前序遍历2:
***********************************************************************************/
int btree_preorder_norecursion2(btree bt, void* pitem)
{
	tlink root = btree_get_root(bt), tmplink;
	stack_slist stk;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	if (NULL == root)   return 0; // 空节点不入栈

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
非递归版中序遍历:
根据中序遍历的顺序，对于任一节点，优先访问其左孩子，而左孩子节点又可看做根节点，
然后继续访问其左孩子节点，直到遇到左孩子为空的节点才进行访问，然后按相同的规则访问其右子树。

对于任一结点P：
1)若结点P的左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后循环当前判断;
若P的左孩子为空，则从栈中取出栈顶元素，访问栈顶节点，然后将当前的P设为栈顶节点的右孩子;
3)直到栈为空，则遍历结束。
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
非递归版后序遍历1:
思路： 对于任一节点P，将其入栈，然后沿其左子树一直往下搜索，直到搜到到美欧左孩子的节点,
此时该节点出现在栈顶，但此时不能将其出栈并访问，因其右孩子还未被访问。所以，接下来
按相同的规则对其右子树进行处理，当访问完其右孩子时，该节点又出现在栈顶，此时
可以将其出栈并访问。
即：每个节点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。因此，多设置
一个变量标识该节点是否第一次出现在栈顶。
***********************************************************************************/
typedef struct pstorder_stack_item
{
	tlink link;
	int   flag; // 1: 第一次出现在栈顶 0:不是第一次出现在栈顶
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

		if (1 == stk_item.flag) // 第一次在栈顶
		{
			stk_item.flag = 0;
			stack_slist_insert(stk, &stk_item);
			root = btree_get_rchild(bt, stk_item.link); // 处理右子树
		}
		else   // 第二次在栈顶
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
非递归版后序遍历2:
思路：要保证根节点在左孩子和右孩子访问之后才能访问，因此对于任一节点P，先将其入栈。
如果P不存在左孩子和右孩子，则可以直接访问它;或者P存在左孩子或者右孩子，但是其
左孩子和右孩子都已被访问过了,则同样可以直接访问该节点。若非上述两种情况,则将P
的右孩子和左孩子依次入栈,这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面
被访问，左孩子和右孩子都在根节点前面被访问。
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
层序遍历二叉树:
一层一层从左向右遍历
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
层序遍历二叉树:
一层一层从右向左遍历
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
