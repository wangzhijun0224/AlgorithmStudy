#ifndef _DS_CHARPTER05_H_
#define _DS_CHARPTER05_H_

/*************************************************************************************************/
// 二叉树的结点抽象
#define BTREE_HAVE_PARENT		0

typedef struct treenode* tlink;
tlink  tlink_new_tnode(int item_size, void* pitem);	        // 获取一个节点，并将pitem所指向的item拷贝到节点中
void   tlink_get_item(tlink p, int item_size, void *pitem);	// 获取节点的item数据
void   tlink_insert_left(tlink p, tlink newnode);			// 将newnode插入到p的左儿子上
void   tlink_insert_right(tlink p, tlink newnode);			// 将newnode插入到p的右儿子上
void   tlink_insert_both(tlink p, tlink left, tlink right);
#if BTREE_HAVE_PARENT
tlink  tlink_get_parent(tlink p);
#endif
tlink  tlink_get_lchild(tlink p);
tlink  tlink_get_rchild(tlink p);
tlink* tlink_get_lchild_addr(tlink p);
tlink* tlink_get_rchild_addr(tlink p);

/*************************************************************************************************/
// 二叉树抽象
typedef struct binary_tree* btree;

btree btree_open(int item_size);	// 创建一个空树
void btree_close(btree bt);
int btree_is_empty(btree bt);		// 判断树是否为空
void btree_make_btree(btree bt, void *pitem, void* penditem);
void btree_get_item(btree bt, tlink root, void *pitem);	// 获取以root为根结点的根节点数据
tlink btree_get_root(btree bt);
#if BTREE_HAVE_PARENT
tlink btree_get_parent(btree bt, tlink root);	// 获取root节点的父节点
#endif
tlink btree_get_lchild(btree bt, tlink root);	// 获取以root为根节点的左子树
tlink btree_get_rchild(btree bt, tlink root);	// 获取以root为根节点的右子树

int btree_preorder_recursion(btree bt, void* pitem);     // 递归版前序遍历树,结果存放在pitem数组中,返回值为树中元素个数
int btree_inorder_recursion(btree bt, void* pitem);      // 递归版中序遍历树,结果存放在pitem数组中,返回值为树中元素个数
int btree_postorder_recursion(btree bt, void* pitem);    // 递归版后序遍历树,结果存放在pitem数组中,返回值为树中元素个数

int btree_preorder_norecursion(btree bt, void* pitem);   // 非递归版前序遍历树,结果存放在pitem数组中,返回值为树中元素个数
int btree_preorder_norecursion2(btree bt, void* pitem);  // 非递归版前序遍历树,另一种方法
int btree_inorder_norecursion(btree bt, void* pitem);    // 非递归版中序遍历树,结果存放在pitem数组中,返回值为树中元素个数
int btree_postorder_norecursion(btree bt, void* pitem);  // 非递归版后序遍历树,结果存放在pitem数组中,返回值为树中元素个数
int btree_postorder_norecursion2(btree bt, void* pitem); // 非递归版后序遍历树,另一种方法
int btree_levelorder(btree bt, void* pitem);             // 层序遍历树，同层从左至右
int btree_levelorderR(btree bt, void* pitem);            // 层序遍历树，同层从右至左
#endif
