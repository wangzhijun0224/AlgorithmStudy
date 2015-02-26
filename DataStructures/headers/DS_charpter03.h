#ifndef _DS_CHARPTER03_H_
#define _DS_CHARPTER03_H_

/***********************************************************************************
***********************************************************************************/
//typedef int	stack_elements;

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

/***********************************************************************************
	ÃÔ¹¬ËÑË÷
***********************************************************************************/
int maze_search(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path);
int maze_search_check(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path, int path_len);
#endif