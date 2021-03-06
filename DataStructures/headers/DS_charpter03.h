#ifndef _DS_CHARPTER03_H_
#define _DS_CHARPTER03_H_

#define USE_DEQUEUE_FOR_STACK_AND_QUEUE	1
#define USE_DLIST_FOR_DEQUEUE			1

#if (!USE_DEQUEUE_FOR_STACK_AND_QUEUE)
/***********************************************************************************
栈和队列的一般实现
***********************************************************************************/
#define DEFAULT_STACK_SIZE	100

typedef struct
{	
	int _top, _stk_size, _element_size;
	void *_stack;

	int (*full)(void* handle);
	int (*empty)(void * handle);
	int (*add)(void *handle, void* pitem);
	int (*del)(void *handle, void* pitem);
}stack;

stack* stack_open(int stk_size, int element_size);
void stack_close(stack* handle);

/***********************************************************************************
***********************************************************************************/
typedef int	queue_elements;

#define DEAFULT_QUEUE_SIZE	101

typedef struct
{
	int _rear, _front, _queue_size;
	queue_elements *_queue;

	int (*full)(void* handle);
	int (*empty)(void* handle);
	int (*add)(void* handle, queue_elements item);
	int(*del)(void* handle, queue_elements *pitem);
}queue;

queue *queue_open(int queue_size);
void queue_close(queue* handle);
#endif

/***********************************************************************************
	迷宫搜索
***********************************************************************************/
int maze_search(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path);
int maze_search_check(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path, int path_len);

/***********************************************************************************
中缀转后缀表达式及后缀表达式求值
***********************************************************************************/
int postfix_expr_eval(const char* postfix_expr, int *pvalue);
int middlefix_to_postfix(const char* middlefix_expr, char* postfix_expr);

typedef struct _node* dlink;

#if USE_DLIST_FOR_DEQUEUE
/***********************************************************************************
双链表实现双端队列
***********************************************************************************/
typedef struct
{
	dlink _guard;	// 哨兵的next指向头,prev指向尾
	int _element_size;
	int _size;		// 为0表示个数无限制
	int _cnt;

	int(*full)(void* handle);
	int(*empty)(void * handle);
	int(*add_front)(void *handle, void* pitem);
	int(*add_rear)(void *handle, void* pitem);
	int(*del_front)(void *handle, void* pitem);
	int(*del_rear)(void *handle, void* pitem);
}dequeue;
#else
/***********************************************************************************
数组实现双端队列
***********************************************************************************/
#define DEFAULT_DEQUEUE_SIZE 100
typedef struct
{
	int _rear, _front, _dequeue_size, _element_size, _cnt;
	void *_dequeue;

	int(*full)(void* handle);
	int(*empty)(void * handle);
	int(*add_front)(void *handle, void* pitem);
	int(*add_rear)(void *handle, void* pitem);
	int(*del_front)(void *handle, void* pitem);
	int(*del_rear)(void *handle, void* pitem);
}dequeue;
#endif

dequeue* dequeue_open(int dequeue_size, int element_size);
void dequeue_close(dequeue* handle);

#if (USE_DEQUEUE_FOR_STACK_AND_QUEUE)
// 用双端队列实现的栈
typedef struct
{
	dequeue *_dq;
	int(*full)(void* handle);
	int(*empty)(void * handle);
	int(*add)(void *handle, void* pitem);
	int(*del)(void *handle, void* pitem);
}stack;
stack* stack_open(int stk_size, int element_size);
void stack_close(stack* handle);
// // 用双端队列实现的队列
typedef struct
{
	dequeue *_dq;
	int(*full)(void* handle);
	int(*empty)(void * handle);
	int(*add)(void *handle, void* pitem);
	int(*del)(void *handle, void* pitem);
}queue;
queue *queue_open(int queue_size, int element_size);
void queue_close(queue* handle);
#endif


#endif