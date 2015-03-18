#ifndef _DS_CHARPTER05_1_H_
#define _DS_CHARPTER05_1_H_

/*************************************************************************************************/
// 线索二叉树
typedef struct thread_treenode* thread_tlink;
typedef struct thread_binary_tree* thread_btree;

thread_btree thread_btree_open(int item_size);	// 创建一个空树

#endif