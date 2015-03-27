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
struct treenode{ 
#if BTREE_HAVE_PARENT
tlink parent;
#endif
tlink left, right; 
};

tlink  tlink_new_tnode(int item_size, void* pitem)
{
	tlink newnode = (tlink)malloc(sizeof(*newnode) + item_size);
	void* dst;

	if (NULL != newnode)
	{
	#if BTREE_HAVE_PARENT
		newnode->parent = NULL;
	#endif
		newnode->left = newnode->right = NULL;
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
#if BTREE_HAVE_PARENT
	if (newnode != NULL) newnode->parent = p;
#endif
	p->left = newnode;
}

void*  _tlink_get_itemaddr(tlink p)
{
	return (char*)p + sizeof(*p);
}

void   tlink_insert_right(tlink p, tlink newnode)
{
#if BTREE_HAVE_PARENT
	if (newnode != NULL) newnode->parent = p;
#endif
	p->right = newnode;
}

void tlink_insert_both(tlink p, tlink left, tlink right)
{
#if BTREE_HAVE_PARENT
	if (left != NULL)	left->parent = p;
	if (right != NULL)	right->parent = p;
#endif

	p->left = left;
	p->right = right;


}
#if BTREE_HAVE_PARENT
tlink  tlink_get_parent(tlink p)
{
	return p->parent;
}
#endif
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

#if BTREE_HAVE_PARENT
static void btree_preorder_copy_recursion(tlink src_root, int item_size, tlink* root, tlink parent)
{
	char* src;
	
	if (NULL != src_root)
	{
		src = (char*)src_root + sizeof(*src_root);
		*root = tlink_new_tnode(item_size, src);
		assert(NULL != *root);
		(*root)->parent = parent;
		
		btree_preorder_copy_recursion(src_root->left, item_size, &((*root)->left), *root);
		btree_preorder_copy_recursion(src_root->right, item_size, &((*root)->right), *root);
	}
}
#else
static void btree_preorder_copy_recursion(tlink src_root, int item_size, tlink* root)
{
	char* src;
	
	if (NULL != src_root)
	{
		src = (char*)src_root + sizeof(*src_root);
		*root = tlink_new_tnode(item_size, src);
		assert(NULL != *root);

		btree_preorder_copy_recursion(src_root->left, item_size, &((*root)->left));
		btree_preorder_copy_recursion(src_root->right, item_size, &((*root)->right));
	}
}

#endif

btree btree_copy(btree src_btree)
{
	int item_size;
	btree new_btree;
	
	if (NULL == src_btree)	return NULL;
	
	item_size = src_btree->item_size;

	new_btree = btree_open(item_size);
	if (NULL == new_btree)	return NULL;

	#if BTREE_HAVE_PARENT
	btree_preorder_copy_recursion(src_btree->root, item_size, &(new_btree->root), NULL);
	#else
	btree_preorder_copy_recursion(src_btree->root, item_size, &(new_btree->root));
	#endif
	return new_btree;	
}

static int btree_equal(tlink first_root, tlink second_root, int item_size)
{
 return ((first_root == NULL && second_root == NULL)
  || (first_root != NULL && second_root != NULL &&
   0 == memcmp((char*)first_root+sizeof(*first_root), (char*)second_root+sizeof(*second_root), item_size)
   && btree_equal(first_root->left, second_root->left, item_size)
   && btree_equal(first_root->right, second_root->right, item_size))
   );
}

int btree_is_equal(btree bt1, btree bt2)
{
 if (bt1->item_size != bt2->item_size) return 0;

 return btree_equal(bt1->root, bt2->root, bt1->item_size);
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

int btree_get_itemsize(btree bt)
{
 	assert (NULL != bt);

	return bt->item_size;
}

int btree_is_empty(btree bt)
{
	assert(NULL != bt);

	return (bt->root == NULL);
}

#if BTREE_HAVE_PARENT
static int btree_create_p(tlink parent, tlink *root, void* pitem, int* pindex, int item_size, void* enditem)
{
	void* pcuritem = (char*)pitem + (*pindex)*item_size;

	if (0 == memcmp(pcuritem, enditem, item_size))
	{
		return 0;
	}

	*root = tlink_new_tnode(item_size, pcuritem);
	if (NULL == *root)  return 0;

	(*root)->parent = parent;
	
	(*pindex)++;
	btree_create_p(*root, tlink_get_lchild_addr(*root), pitem, pindex, item_size, enditem);
	(*pindex)++;
	btree_create_p(*root, tlink_get_rchild_addr(*root), pitem, pindex, item_size, enditem);
	return 1;
}
#else
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
#endif

void btree_make_btree(btree bt, void *pitem, void* penditem)
{
	int index = 0;
	#if BTREE_HAVE_PARENT
	btree_create_p(NULL, &(bt->root), pitem, &index, bt->item_size, penditem); // root's parent is NULL
	#else
	btree_create(&(bt->root), pitem, &index, bt->item_size, penditem);
	#endif
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

#if BTREE_HAVE_PARENT
tlink btree_get_parent(btree bt, tlink root)
{
	if (NULL == root)	return NULL;
	else	return tlink_get_parent(root);
}

#endif

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
#if (!BTREE_HAVE_PARENT)

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

#else
/***********************************************************************************
����parent���Ե�ǰ��ǵݹ����:
������һ���root��
1)���ʽ��root;
2)�ж�root�������Ƿ�Ϊ��,����Ϊ��,��root����������Ϊroot��ѭ����1);��Ϊ��,��ת��3);
3)ȡroot���Һ���,���root���Һ��Ӳ�Ϊ��,��root���Һ�������Ϊroot��ѭ����1);
  ��Ϊ��,����root��parent��������,ֱ��parentΪ��(���������)���ҵ�һ��parent���Һ��Ӳ�ΪrootΪֹ��
  ����parent���Һ�������Ϊroot��ѭ����1��
***********************************************************************************/
int btree_preorder_norecursion(btree bt, void* pitem)
{
	tlink root, left, right, parent;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	for (root = btree_get_root(bt); root != NULL; )
	{
        while (1)
		{
			dst = (char*)pitem + index*sizeof(char);
			btree_get_item(bt, root, dst);
			index++;

			left = btree_get_lchild(bt, root);
			if (NULL == left)	break;
			else	root = left;
		}

		right = btree_get_rchild(bt, root);
		if (NULL == right)	// �������������
		{
			// �ض�������������,ֱ��parentΪ�ջ��ҵ�һ��parent���ҽڵ㲻ΪrootΪֹ
			parent = tlink_get_parent(root);
			while (NULL != parent && root == btree_get_rchild(bt, parent))
			{
				root = parent;
				parent = tlink_get_parent(parent);
			}
			
			if (NULL != parent) root = btree_get_rchild(bt, parent);
			else break;
				
		}
		else	// ��������,����������
		{
			root = right;
		}
	}
	
	return index;
}
#endif

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

#if (!BTREE_HAVE_PARENT)

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
#else
/***********************************************************************************
����parent���Ե�����ǵݹ����:
������һ���root��
1)�ж�root�������Ƿ�Ϊ��,����Ϊ��,��root����������Ϊroot��ѭ��������;
  ��Ϊ��,��ת��2);
2)���ʽڵ�root,Ȼ���ж�root���Һ����Ƿ�Ϊ��,����Ϊ��,��root���Һ�������Ϊroot��ѭ����1);
  ��Ϊ��,����root��parent��������,ֱ��parentΪ��(���������)���ҵ�һ��parent���Һ��Ӳ�ΪrootΪֹ��
  ��ʱ�ȷ���parent��ֵ,�ٽ���parent���Һ�������Ϊroot��ѭ����1��
***********************************************************************************/
int btree_inorder_norecursion(btree bt, void* pitem)
{
	tlink root, parent, left, right;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	root = btree_get_root(bt);

	while (NULL != root)
	{
		while(1)
		{
			left = btree_get_lchild(bt, root);
			if (NULL == left)	break;	// �������������
			else root = left;
		}

		dst = (char*)pitem + index*sizeof(char);
		index++;
		btree_get_item(bt, root, dst);
			
		right = btree_get_rchild(bt, root);
		if (NULL == right)	
		{
			parent = tlink_get_parent(root);
			while (NULL != parent && root == btree_get_rchild(bt, parent))
			{
				root = parent;
				parent = tlink_get_parent(parent);
			}
			
			if (NULL != parent) 
			{	
				// ����p��������֮ǰ,�ȷ���p
				dst = (char*)pitem + index*sizeof(char);
				index++;
				btree_get_item(bt, parent, dst);
		
				root = btree_get_rchild(bt, parent);
			}
			else break;
				
		}
		else
		{	
			root = right;
		}
	}

	return index;
}
#endif

#if (!BTREE_HAVE_PARENT)
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
#else
/***********************************************************************************
����parent���Եĺ���ǵݹ����:
������һ���root��
1)�ж�root�������Ƿ�Ϊ��,����Ϊ��,��root����������Ϊroot��ѭ��������;
  ��Ϊ��,��ת��2);
2)Ȼ���ж�root���Һ����Ƿ�Ϊ��,����Ϊ��,��root���Һ�������Ϊroot��ѭ����1);
  ��Ϊ��,�ȷ���root��ֵ,����root��parent��������:
    ��rootΪparent���ҽڵ㣬�����parent�ڵ㲢������������;
  ��������ɺ�,parentΪ��,���������;����,��root����Ϊparent���ҽڵ㣬ѭ����1);
***********************************************************************************/
int btree_postorder_norecursion(btree bt, void* pitem)
{
	tlink root, parent, left, right;
	char* dst;
	int index = 0;

	assert(NULL != bt);
	assert(NULL != pitem);

	root = btree_get_root(bt);

	while (NULL != root)
	{
		while(1)
		{
			left = btree_get_lchild(bt, root);
			if (NULL == left)	break;	// �������������
			else root = left;
		}
			
		right = btree_get_rchild(bt, root);
		if (NULL == right)	
		{
			dst = (char*)pitem + index*sizeof(char);
			index++;
			btree_get_item(bt, root, dst);

			parent = tlink_get_parent(root);
			while (NULL != parent && root == btree_get_rchild(bt, parent))
			{
				dst = (char*)pitem + index*sizeof(char);
				index++;
				btree_get_item(bt, parent, dst);
			
				root = parent;
				parent = tlink_get_parent(parent);
			}
			
			if (NULL != parent) 
			{	
				root = btree_get_rchild(bt, parent);
			}
			else break;
				
		}
		else
		{	
			root = right;
		}
	}

	return index;
}

#endif

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
