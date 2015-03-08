#ifndef _DS_CHARPTER05_H_
#define _DS_CHARPTER05_H_

/*************************************************************************************************/
// �������Ľ�����
typedef struct treenode* tlink;
tlink  tlink_new_tnode(int item_size, void* pitem);	// ��ȡһ���ڵ㣬����pitem��ָ���item�������ڵ���
void   tlink_get_item(tlink p, int item_size, void *pitem);	// ��ȡ�ڵ��item����
void   tlink_insert_left(tlink p, tlink newnode);			// ��newnode���뵽p���������
void   tlink_insert_right(tlink p, tlink newnode);			// ��newnode���뵽p���Ҷ�����
void   tlink_insert_both(tlink p, tlink left, tlink right);
tlink  tlink_get_lchild(tlink p);
tlink  tlink_get_rchild(tlink p);

/*************************************************************************************************/
// ����������
typedef struct binary_tree* btree;

btree btree_open(int item_size);	// ����һ������
void btree_close(btree bt);	
int btree_is_empty(btree bt);		// �ж����Ƿ�Ϊ��
// ���������,������ӡ����ڵ㡢�Ҷ��ӵ����ݷֱ�Ϊbtleft��*pitem��btright������ֵΪ����õ����ĸ��ڵ�
tlink btree_make_btree(btree bt, tlink left, void *pitem, tlink right);
void btree_get_item(btree bt, tlink root, void *pitem);	// ��ȡ��rootΪ�����ĸ��ڵ�����
tlink btree_get_lchild(btree bt, tlink root);	// ��ȡ��rootΪ���ڵ��������
tlink btree_get_rchild(btree bt, tlink root);	// ��ȡ��rootΪ���ڵ��������
#endif
