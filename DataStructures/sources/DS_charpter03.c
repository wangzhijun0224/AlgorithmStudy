#include "DS_charpter03.h"

#include <stdlib.h>

static int stack_full(void *handle)
{
	stack* stk = (stack*)handle;
	
	if (stk->_top >= (stk->_stk_size - 1))
	{
		return 1;
	}

	return 0;
}

static int stack_empty(void *handle)
{
	stack* stk = (stack*)handle;

	if (stk->_top <= -1)
	{
		return 1;
	}

	return 0;
}

static int stack_add(void *handle, stack_elements item)
{
	stack* stk = (stack*)handle;

	if (1 == stk->full(handle))
	{
		return 0;
	}

	stk->_stack[++stk->_top] = item;

	return 1;
}

static int stack_del(void *handle, stack_elements *pitem)
{
	stack* stk = (stack*)handle;

	if (1 == stk->empty(handle))
	{
		return 0;
	}

	*pitem = stk->_stack[stk->_top--];

	return 1;
}
/***********************************************************************************
***********************************************************************************/
stack* stack_open(int stk_size)
{
	stack* stk = (stack*)malloc(sizeof(stack));
	if (NULL == stk)
	{
		return stk;
	}

	stk->_stk_size = (stk_size <= 0 ? DEFAULT_STACK_SIZE : stk_size);
	stk->_stack = (stack_elements *)malloc(stk->_stk_size * sizeof(stack_elements));
	if (NULL == stk->_stack)
	{
		free(stk);
		return NULL;
	}

	stk->_top = -1;

	stk->full	= stack_full;
	stk->empty	= stack_empty;
	stk->add	= stack_add;
	stk->del	= stack_del;
	return stk;
}

void stack_close(stack* stk)
{
	free(stk->_stack);
	free(stk);
}



/******************************************************************************************************/
#if 0
typedef int	queue_elements;

#define DEAFULT_QUEUE_SIZE	100

typedef struct
{
	int _rear, _front;
	queue_elements *_queue;

	
	int(*empty)(queue* handle);
	int(*add)(queue* handle, queue_elements item);
	int(*del)(queue* handle, queue_elements *pitem);
}queue;

void queue_close(queue* handle);
#endif

int queue_full(void* handle)
{
	queue *q = (queue*)handle;

	if (((q->_rear + 1) % q->_queue_size) == q->_front)	return 1;

	return 0;
}

int queue_empty(void* handle)
{
	queue *q = (queue*)handle;

	if (q->_front == q->_rear)	return 1;

	return 0;
}

int queue_add(queue* handle, queue_elements item)
{
	queue *q = (queue*)handle;

	if (1 == q->full(handle))
	{
		return 0;
	}

	q->_queue[q->_rear] = item;

	q->_rear = (q->_rear+1) % (q->_queue_size);

	return 1;
}

int queue_del(queue* handle, queue_elements *pitem)
{
	queue *q = (queue*)handle;

	if (1 == q->empty(handle))
	{
		return 0;
	}

	*pitem = q->_queue[q->_front];
	
	q->_front = (q->_front + 1) % (q->_queue_size);

	return 1;
}
/***********************************************************************************
***********************************************************************************/
queue *queue_open(int queue_size)
{
	queue* q = (queue*)malloc(sizeof(queue));
	if (NULL == q)
	{
		return q;
	}

	// 约定容量为size的队列最多插入size-1个元素,这样以便于区分队列是空队列还是满队列
	q->_queue_size = (queue_size <= 0 ? DEAFULT_QUEUE_SIZE : (queue_size + 1));
	q->_queue = (queue_elements *)malloc(q->_queue_size * sizeof(queue_elements));
	if (NULL == q->_queue)
	{
		free(q);
		return NULL;
	}

	q->_rear = q->_front = 0;

	q->full = queue_full;
	q->empty = queue_empty;
	q->add = queue_add;
	q->del = queue_del;
	return q;
}

void queue_close(queue* handle)
{
	free(handle->_queue);
	free(handle);
}