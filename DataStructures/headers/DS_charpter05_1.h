#ifndef _DS_CHARPTER05_1_H_
#define _DS_CHARPTER05_1_H_

#include "DS_charpter05.h"

// 下面两个宏只开且必开其中之一
#define THREAD_INORDER      1
#define THREAD_PREORDER     0

/*************************************************************************************************/
// 线索二叉树
typedef struct thread_treenode* thread_tlink;
typedef struct thread_binary_tree* thread_btree;

thread_btree thread_btree_open(int item_size); // 创建一个空树
void thread_btree_create(thread_btree bt, void *pitem, void* penditem);
thread_btree thread_btree_create_by_btree(btree src_bt);
int thread_btree_order(thread_btree bt, void* pitem);
void thread_btree_close(thread_btree bt);
#endif

