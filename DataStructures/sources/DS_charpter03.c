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
	stk = NULL;
}