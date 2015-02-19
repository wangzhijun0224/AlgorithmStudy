#ifndef _DS_CHARPTER03_H_
#define _DS_CHARPTER03_H_

typedef int	stack_elements;

typedef struct
{
#define DEFAULT_STACK_SIZE	100
	
	int _top;
	int _stk_size;
	stack_elements *_stack;

	int (*full)(void* handle);
	int (*empty)(void * handle);
	int (*add)(void *handle, stack_elements item);
	int (*del)(void *handle, stack_elements *pitem);
}stack;

stack* stack_open(int stk_size);
void stack_close(stack* stk);

#endif