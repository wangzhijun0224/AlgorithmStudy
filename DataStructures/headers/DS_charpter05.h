#ifndef _DS_CHARPTER05_H_
#define _DS_CHARPTER05_H_

/*************************************************************************************************/
// �������Ľ�����
#define BTREE_HAVE_PARENT		0

typedef struct treenode* tlink;
tlink  tlink_new_tnode(int item_size, void* pitem);	        // ��ȡһ���ڵ㣬����pitem��ָ���item�������ڵ���
void   tlink_get_item(tlink p, int item_size, void *pitem);	// ��ȡ�ڵ��item����
void   tlink_insert_left(tlink p, tlink newnode);			// ��newnode���뵽p���������
void   tlink_insert_right(tlink p, tlink newnode);			// ��newnode���뵽p���Ҷ�����
void   tlink_insert_both(tlink p, tlink left, tlink right);
#if BTREE_HAVE_PARENT
tlink  tlink_get_parent(tlink p);
#endif
tlink  tlink_get_lchild(tlink p);
tlink  tlink_get_rchild(tlink p);
tlink* tlink_get_lchild_addr(tlink p);
tlink* tlink_get_rchild_addr(tlink p);

/*************************************************************************************************/
// ����������
typedef struct binary_tree* btree;

btree btree_open(int item_size);	// ����һ������
void btree_close(btree bt);
int btree_is_empty(btree bt);		// �ж����Ƿ�Ϊ��
void btree_make_btree(btree bt, void *pitem, void* penditem);
void btree_get_item(btree bt, tlink root, void *pitem);	// ��ȡ��rootΪ�����ĸ��ڵ�����
tlink btree_get_root(btree bt);
#if BTREE_HAVE_PARENT
tlink btree_get_parent(btree bt, tlink root);	// ��ȡroot�ڵ�ĸ��ڵ�
#endif
tlink btree_get_lchild(btree bt, tlink root);	// ��ȡ��rootΪ���ڵ��������
tlink btree_get_rchild(btree bt, tlink root);	// ��ȡ��rootΪ���ڵ��������

int btree_preorder_recursion(btree bt, void* pitem);     // �ݹ��ǰ�������,��������pitem������,����ֵΪ����Ԫ�ظ���
int btree_inorder_recursion(btree bt, void* pitem);      // �ݹ�����������,��������pitem������,����ֵΪ����Ԫ�ظ���
int btree_postorder_recursion(btree bt, void* pitem);    // �ݹ����������,��������pitem������,����ֵΪ����Ԫ�ظ���

int btree_preorder_norecursion(btree bt, void* pitem);   // �ǵݹ��ǰ�������,��������pitem������,����ֵΪ����Ԫ�ظ���
int btree_preorder_norecursion2(btree bt, void* pitem);  // �ǵݹ��ǰ�������,��һ�ַ���
int btree_inorder_norecursion(btree bt, void* pitem);    // �ǵݹ�����������,��������pitem������,����ֵΪ����Ԫ�ظ���
int btree_postorder_norecursion(btree bt, void* pitem);  // �ǵݹ����������,��������pitem������,����ֵΪ����Ԫ�ظ���
int btree_postorder_norecursion2(btree bt, void* pitem); // �ǵݹ����������,��һ�ַ���
int btree_levelorder(btree bt, void* pitem);             // �����������ͬ���������
int btree_levelorderR(btree bt, void* pitem);            // �����������ͬ���������
#endif
