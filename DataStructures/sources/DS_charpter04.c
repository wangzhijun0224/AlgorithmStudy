#include "DS_charpter04.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*************************************************************************************************/
/***********************************************************************************
������ڵ����
***********************************************************************************/
// ����ȫ����,����ڵ�Ŀռ�����Ҫ����item�Ĵ�С
struct snode{ slink next;};

static slink slink_get_new_slink(int item_size)
{
	slink tmpnode = (slink)malloc(sizeof(*tmpnode) + item_size);

	if (NULL != tmpnode)
	{
		tmpnode->next = tmpnode;	// ����ѭ����,�Լ�insert��del�Ȳ���
	}

	return tmpnode;
}

slink slink_new_slink(void)
{
	return slink_get_new_slink(0);
}

slink slink_new_snode(int item_size, void* pitem)
{
	assert(item_size > 0);
	assert(pitem != NULL);

	slink node = slink_get_new_slink(item_size);

	// copy item to node
	if (NULL != node)
	{
		void *dst = (char *)node + sizeof(*node);
		memcpy(dst, pitem, item_size);
	}

	return node;
}

slink slink_next_slink(slink p)
{
	return p->next;
}

void slink_get_item(slink p, int item_size, void *pitem)
{
	assert(item_size > 0);
	assert(pitem != NULL);

	void *src = (char *)p + sizeof(*p);
	memcpy(pitem, src, item_size);
}

void slink_insert(slink p, slink newnode)
{
	newnode->next = p->next;
	p->next = newnode;
}

void slink_del(slink p)
{
	slink tmp = p->next;
	p->next = tmp->next;
	free(tmp);
}

/*************************************************************************************************/
// �õ�����ģ���ջ
struct stack_snode
{
	slink guard;	// �ڱ��ڵ�,gurad->nextָ��ջ��
	int item_size;
};

stack_slist stack_slist_open(int item_size)
{
	slink node;

	assert(item_size > 0);

	stack_slist stk = (stack_slist)malloc(sizeof(*stk));
	
	if (NULL == stk)	return stk;

	node = slink_new_slink();
	if (NULL == node)
	{
		free(stk);
		return NULL;
	}
	
	stk->guard		= node;
	stk->item_size	= item_size;

	return stk;
}

void stack_slist_close(stack_slist handle)
{
	slink guard = handle->guard;
	slink top = slink_next_slink(handle->guard);
	slink tmp;
	while (top != guard)
	{
		tmp = top;
		top = slink_next_slink(tmp);
		free(tmp);
	}
	free(guard);

	free(handle);
}

int stack_slist_insert(stack_slist handle, void* pitem)
{
	assert(NULL != pitem);

	slink newnode = slink_new_snode(handle->item_size, pitem);
	if (NULL == newnode)	return 0;

	slink_insert(handle->guard, newnode);
	return 1;
}

int stack_slist_del(stack_slist handle, void* pitem)
{
	slink top = slink_next_slink(handle->guard);
	if (top == handle->guard) return 0;

	slink_get_item(top, handle->item_size, pitem);

	slink_del(handle->guard);

	return 1;
}

int stack_slist_top(stack_slist handle, void* pitem)
{
	slink top = slink_next_slink(handle->guard);
	if (top == handle->guard) return 0;

	slink_get_item(top, handle->item_size, pitem);

	return 1;
}

int stack_slist_pop(stack_slist handle)
{
	slink top = slink_next_slink(handle->guard);
	if (top == handle->guard) return 0;

	slink_del(handle->guard);

	return 1;
}

/*************************************************************************************************/
// �õ�����ģ��Ķ���
struct queue_snode
{
	slink guard;	// �ڱ��ڵ�,gurad->nextָ�����β��
	slink rear;		// ����β,�Ӷ���β����ڵ�
	int item_size;
};

queue_slist queue_slist_open(int item_size)
{
	slink node;

	assert(item_size > 0);

	queue_slist q = (queue_slist)malloc(sizeof(*q));

	if (NULL == q)	return q;

	node = slink_new_slink();
	if (NULL == node)
	{
		free(q);
		return NULL;
	}

	q->guard = node;
	q->rear	 = node;
	q->item_size = item_size;

	return q;
}

void queue_slist_close(queue_slist handle)
{
	slink guard = handle->guard;
	slink head = slink_next_slink(handle->guard);
	slink tmp;
	while (head != guard)
	{
		tmp = head;
		head = slink_next_slink(tmp);
		free(tmp);
	}
	free(guard);

	free(handle);
}

int queue_slist_insert(queue_slist handle, void* pitem)
{
	assert(NULL != pitem);

	slink newnode = slink_new_snode(handle->item_size, pitem);
	if (NULL == newnode)	return 0;

	slink_insert(handle->rear, newnode);
	handle->rear = newnode;	// ��¼�µ�β�ڵ�

	return 1;
}

int queue_slist_del(queue_slist handle, void* pitem)
{
	slink head = slink_next_slink(handle->guard);
	if (head == handle->guard) return 0;

	slink_get_item(head, handle->item_size, pitem);

	slink_del(handle->guard);

	return 1;
}

/*************************************************************************************************/
/***********************************************************************************
˫����ڵ����
***********************************************************************************/
// ���������ͳ�������ڵ��ʱ����Ҫ����sizeof(_node)+sizeof(item)��С
typedef struct dnode
{
	dlink prev;
	dlink next;
}node;

static dlink dlink_get_new_dlink(int item_size)
{
	dlink newnode = (dlink)malloc(sizeof(*newnode) + item_size);
	if (NULL == newnode) return newnode;

	newnode->prev = newnode->next = newnode;	// ѭ����

	return newnode;
}

dlink  dlink_new_dlink(void)
{
	return dlink_get_new_dlink(0);
}

dlink dlink_new_dnode(int item_size, void* pitem)
{
	assert(item_size > 0);
	assert(pitem != NULL);

	dlink node = dlink_get_new_dlink(item_size);

	// copy item to node
	if (NULL != node)
	{
		void *dst = (char *)node + sizeof(*node);
		memcpy(dst, pitem, item_size);
	}

	return node;
}

dlink  dlink_next_dlink(dlink p)
{
	return p->next;
}

dlink  dlink_prev_dlink(dlink p)
{
	return p->prev;
}

void   dlink_get_item(dlink p, int item_size, void *pitem)
{
	assert(item_size > 0);
	assert(pitem != NULL);

	void *src = (char *)p + sizeof(*p);
	memcpy(pitem, src, item_size);
}

void dlink_insert(dlink p, dlink newnode)
{
	newnode->prev = p;
	newnode->next = p->next;
	p->next->prev = newnode;
	p->next = newnode;
}

void dlink_del(dlink p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

/*************************************************************************************************/
// ��˫����ģ���˫�˶���
struct dequeue_dnode
{
	dlink guard;	// �ڱ���nextָ��ͷ,prevָ��β
	int item_size;
};

dequeue_dlist dequeue_dlist_open(int item_size)
{
	dlink node;

	assert(item_size > 0);

	dequeue_dlist dq = (dequeue_dlist)malloc(sizeof(*dq));

	if (NULL == dq)	return dq;

	node = dlink_new_dlink();
	if (NULL == node)
	{
		free(dq);
		return NULL;
	}

	dq->guard = node;
	dq->item_size = item_size;

	return dq;
}

void dequeue_dlist_close(dequeue_dlist handle)
{
	dlink guard = handle->guard;
	dlink next = dlink_next_dlink(guard);
	dlink tmp;
	while (next != guard)
	{
		tmp = next;
		next = dlink_next_dlink(tmp);
		free(tmp);
	}
	free(guard);

	free(handle);
}

int dequeue_dlist_insert(dequeue_dlist handle, void* pitem)
{
	assert(NULL != pitem);

	dlink newnode = dlink_new_dnode(handle->item_size, pitem);
	if (NULL == newnode)	return 0;

	dlink_insert(handle->guard, newnode);

	return 1;
}

int dequeue_dlist_append(dequeue_dlist handle, void* pitem)
{
	assert(NULL != pitem);

	dlink newnode = dlink_new_dnode(handle->item_size, pitem);
	if (NULL == newnode)	return 0;

	dlink_insert(dlink_prev_dlink(handle->guard), newnode);

	return 1;
}

int	dequeue_dlist_pop(dequeue_dlist handle, void* pitem)
{
	dlink head = dlink_next_dlink(handle->guard);
	if (head == handle->guard) return 0;

	dlink_get_item(head, handle->item_size, pitem);

	dlink_del(head);

	return 1;
}

int	dequeue_dlist_del(dequeue_dlist handle, void* pitem)
{
	dlink tail = dlink_prev_dlink(handle->guard);
	if (tail == handle->guard) return 0;

	dlink_get_item(tail, handle->item_size, pitem);

	dlink_del(tail);

	return 1;
}