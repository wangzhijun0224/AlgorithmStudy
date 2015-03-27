#ifndef _DS_CHARPTER05_1_H_
#define _DS_CHARPTER05_1_H_

#include "DS_charpter05.h"

// ����������ֻ���ұؿ�����֮һ
#define THREAD_INORDER      1
#define THREAD_PREORDER     0

/*************************************************************************************************/
// ����������
typedef struct thread_treenode* thread_tlink;
typedef struct thread_binary_tree* thread_btree;

thread_btree thread_btree_open(int item_size); // ����һ������
void thread_btree_create(thread_btree bt, void *pitem, void* penditem);
thread_btree thread_btree_create_by_btree(btree src_bt);
int thread_btree_order(thread_btree bt, void* pitem);
void thread_btree_close(thread_btree bt);
#endif

