#ifndef _DS_CHARPTER04_H_
#define _DS_CHARPTER04_H_

/*************************************************************************************************/
// 单链表节点抽象
typedef struct snode*  slink;
slink  slink_new_slink(void);						// 获取一个单独的节点,不带item项
slink  slink_new_snode(int item_size, void* pitem);	// 获取一个节点，并将pitem所指向的item拷贝到节点中
slink  slink_next_slink(slink p);					// 获取p节点的下一个节点
void   slink_get_item(slink p, int item_size, void *pitem);	// 获取节点的item数据
void   slink_insert(slink p, slink newnode);			// 将newnode插入到p之后
void   slink_del(slink p);							// 将p节点的下一个节点删除

/*************************************************************************************************/
// 栈抽象(用单链表节点实现)
typedef struct stack_snode*	stack_slist;
stack_slist stack_slist_open(int item_size);
void        stack_slist_close(stack_slist handle);
int         stack_slist_insert(stack_slist handle, void* pitem);
int         stack_slist_del(stack_slist handle, void* pitem);	// 弹出并删除栈顶元素
int			stack_slist_top(stack_slist handle, void* pitem);
int			stack_slist_pop(stack_slist handle);	// 删除栈顶元素

/*************************************************************************************************/
// 队列抽象(用单链表节点实现)
typedef struct queue_snode*	queue_slist;
queue_slist queue_slist_open(int item_size);
void        queue_slist_close(queue_slist handle);
int         queue_slist_insert(queue_slist handle, void* pitem);
int         queue_slist_del(queue_slist handle, void* pitem);

/*************************************************************************************************/
// 双链表节点抽象
typedef struct dnode*  dlink;
dlink  dlink_new_dlink(void);						// 获取一个单独的节点,不带item项
dlink  dlink_new_dnode(int item_size, void* pitem);	// 获取一个节点，并将pitem所指向的item拷贝到节点中
dlink  dlink_next_dlink(dlink p);
dlink  dlink_prev_dlink(dlink p);
void   dlink_get_item(dlink p, int item_size, void *pitem);	// 获取节点的item数据
void   dlink_insert(dlink p, dlink newnode);			// 将newnode插入到p之后
void   dlink_del(dlink p);							// 将p节点删除

/*************************************************************************************************/
// 双端抽象(用双链表节点实现)
typedef struct dequeue_dnode* dequeue_dlist;
dequeue_dlist dequeue_dlist_open(int item_size);
void	dequeue_dlist_close(dequeue_dlist handle);
int		dequeue_dlist_insert(dequeue_dlist handle, void* pitem);	// 在头部添加
int		dequeue_dlist_append(dequeue_dlist handle, void* pitem);	// 在尾部添加
int		dequeue_dlist_pop(dequeue_dlist handle, void* pitem);		// 从头部删除
int		dequeue_dlist_del(dequeue_dlist handle, void* pitem);		// 从尾部删除
#endif