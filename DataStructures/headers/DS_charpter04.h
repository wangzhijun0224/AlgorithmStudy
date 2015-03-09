#ifndef _DS_CHARPTER04_H_
#define _DS_CHARPTER04_H_

/*************************************************************************************************/
// ������ڵ����
typedef struct snode*  slink;
slink  slink_new_slink(void);						// ��ȡһ�������Ľڵ�,����item��
slink  slink_new_snode(int item_size, void* pitem);	// ��ȡһ���ڵ㣬����pitem��ָ���item�������ڵ���
slink  slink_next_slink(slink p);					// ��ȡp�ڵ����һ���ڵ�
void   slink_get_item(slink p, int item_size, void *pitem);	// ��ȡ�ڵ��item����
void   slink_insert(slink p, slink newnode);			// ��newnode���뵽p֮��
void   slink_del(slink p);							// ��p�ڵ����һ���ڵ�ɾ��

/*************************************************************************************************/
// ջ����(�õ�����ڵ�ʵ��)
typedef struct stack_snode*	stack_slist;
stack_slist stack_slist_open(int item_size);
void        stack_slist_close(stack_slist handle);
int         stack_slist_insert(stack_slist handle, void* pitem);
int         stack_slist_del(stack_slist handle, void* pitem);	// ������ɾ��ջ��Ԫ��
int			stack_slist_top(stack_slist handle, void* pitem);
int			stack_slist_pop(stack_slist handle);	// ɾ��ջ��Ԫ��

/*************************************************************************************************/
// ���г���(�õ�����ڵ�ʵ��)
typedef struct queue_snode*	queue_slist;
queue_slist queue_slist_open(int item_size);
void        queue_slist_close(queue_slist handle);
int         queue_slist_insert(queue_slist handle, void* pitem);
int         queue_slist_del(queue_slist handle, void* pitem);

/*************************************************************************************************/
// ˫����ڵ����
typedef struct dnode*  dlink;
dlink  dlink_new_dlink(void);						// ��ȡһ�������Ľڵ�,����item��
dlink  dlink_new_dnode(int item_size, void* pitem);	// ��ȡһ���ڵ㣬����pitem��ָ���item�������ڵ���
dlink  dlink_next_dlink(dlink p);
dlink  dlink_prev_dlink(dlink p);
void   dlink_get_item(dlink p, int item_size, void *pitem);	// ��ȡ�ڵ��item����
void   dlink_insert(dlink p, dlink newnode);			// ��newnode���뵽p֮��
void   dlink_del(dlink p);							// ��p�ڵ�ɾ��

/*************************************************************************************************/
// ˫�˳���(��˫����ڵ�ʵ��)
typedef struct dequeue_dnode* dequeue_dlist;
dequeue_dlist dequeue_dlist_open(int item_size);
void	dequeue_dlist_close(dequeue_dlist handle);
int		dequeue_dlist_insert(dequeue_dlist handle, void* pitem);	// ��ͷ�����
int		dequeue_dlist_append(dequeue_dlist handle, void* pitem);	// ��β�����
int		dequeue_dlist_pop(dequeue_dlist handle, void* pitem);		// ��ͷ��ɾ��
int		dequeue_dlist_del(dequeue_dlist handle, void* pitem);		// ��β��ɾ��
#endif