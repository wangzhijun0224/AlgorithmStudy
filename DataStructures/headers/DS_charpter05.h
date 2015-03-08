#ifndef _DS_CHARPTER05_H_
#define _DS_CHARPTER05_H_

/*************************************************************************************************/
// 二叉树的结点抽象
typedef struct treenode* tlink;
tlink  tlink_new_tnode(int item_size, void* pitem);	// 获取一个节点，并将pitem所指向的item拷贝到节点中
void   tlink_get_item(tlink p, int item_size, void *pitem);	// 获取节点的item数据
void   tlink_insert_left(tlink p, tlink newnode);			// 将newnode插入到p的左儿子上
void   tlink_insert_right(tlink p, tlink newnode);			// 将newnode插入到p的右儿子上
void   tlink_insert_both(tlink p, tlink left, tlink right);
tlink  tlink_get_lchild(tlink p);
tlink  tlink_get_rchild(tlink p);

/*************************************************************************************************/
// 二叉树抽象
typedef struct binary_tree* btree;

btree btree_open(int item_size);	// 创建一个空树
void btree_close(btree bt);	
int btree_is_empty(btree bt);		// 判断树是否为空
// 构造二叉树,其左儿子、根节点、右儿子的数据分别为btleft、*pitem、btright，返回值为构造好的树的根节点
tlink btree_make_btree(btree bt, tlink left, void *pitem, tlink right);
void btree_get_item(btree bt, tlink root, void *pitem);	// 获取以root为根结点的根节点数据
tlink btree_get_lchild(btree bt, tlink root);	// 获取以root为根节点的左子树
tlink btree_get_rchild(btree bt, tlink root);	// 获取以root为根节点的右子树
#endif
