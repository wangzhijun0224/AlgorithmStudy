#include "DS_charpter03.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

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

static int stack_add(void *handle, void* pitem)
{
	stack* stk = (stack*)handle;

	if (1 == stk->full(handle))
	{
		return 0;
	}

	++stk->_top;
	char *dst = (char *)stk->_stack;
	dst += stk->_top * stk->_element_size;
	memcpy(dst, pitem, stk->_element_size);

	return 1;
}

static int stack_del(void *handle, void *pitem)
{
	stack* stk = (stack*)handle;

	if (1 == stk->empty(handle))
	{
		return 0;
	}

	char *src = (char *)stk->_stack;
	src += stk->_top * stk->_element_size;
	memcpy(pitem, src, stk->_element_size);
	stk->_top--;

	return 1;
}
/***********************************************************************************
***********************************************************************************/
stack* stack_open(int stk_size, int element_size)
{
	stack* stk = NULL;

	if (element_size < 1)	return stk;

	 stk = (stack*)malloc(sizeof(stack));
	if (NULL == stk)
	{
		return stk;
	}

	stk->_stk_size = (stk_size <= 0 ? DEFAULT_STACK_SIZE : stk_size);
	stk->_stack = malloc(stk->_stk_size * element_size);
	if (NULL == stk->_stack)
	{
		free(stk);
		return NULL;
	}

	stk->_top = -1;
	stk->_element_size = element_size;
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

	// Լ������Ϊsize�Ķ���������size-1��Ԫ��,�����Ա������ֶ����ǿն��л���������
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

/***********************************************************************************
	ջ��Ӧ��: �Թ������㷨
***********************************************************************************/
typedef struct
{
	signed char y;
	signed char x;
}offsets;

typedef struct
{
	unsigned int x, y, dir;
}elements;

/***********************************************************************************
	maze:			�Թ���ֵΪ0��ʾ��ͨ��ֵΪ1��ʾ���;
	col,row:		�Թ�������������
	startx,starty:	�Թ��Ŀ�ʼλ��
	endx,endy:		Ҫ������Թ�λ��
	path:			����������ҵ����ƶ�·��
	����ֵ: -1������ʧ��(�в����������ϵͳ���ڴ�);
			0:	δ��������Ч·��;
			path_len:	����������Ч·������;
	***********************************************************************************/
int maze_search(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path)
{
	if (NULL == maze || col < 1 || row < 1
		|| (startx < 0 || startx >= col) || (starty < 0 || starty >= row)
		|| (endx < 0 || endx >= row) || (endy < 0 || endy >= col)
		|| NULL == path)
	{
		return -1;
	}

	if (0 != maze[starty*row + startx] || 0 != maze[endy*row + endx])
	{
		return -1;
	}

	// 8���ƶ�����,���ζ�Ӧ����(dir)Ϊ: 0, 1, 2, 3, 4, 5, 6, 7
	offsets move[8] = { 
		{ -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 },
		{ 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }
	};

	// 1. �Թ���չ:���Թ��ı�Եȫ����ǽ���Լ򻯱�Ե�ϵ��Թ��ƶ�������
	int col2 = col + 2, row2 = row + 2;
	unsigned char *maze2 = (unsigned char *)malloc(col2*row2*sizeof(unsigned char));
	if (NULL == maze2)	return -1;
	unsigned char *src = maze, *dst = maze2;
	memset(dst, 1, row2);
	dst += row2;

	for (int i = 0; i < col; ++i)
	{
		*dst++ = 1;
		for (int j = 0; j < row; ++j)
		{
			*dst++ = *src++;
		}
		*dst++ = 1;
	}
	memset(dst, 1, row2);

	// mark���飬���ڼ�¼�Ѿ��������Թ�λ��
	unsigned char *mark = (unsigned char *)malloc(col2*row2*sizeof(unsigned char));
	if (NULL == mark)
	{
		free(maze2);
		return -1;
	}
	memset(mark, 0, col2*row2*sizeof(unsigned char));


	// �Թ�����
	stack *stk = stack_open(col2*row2, sizeof(elements));
	if (NULL == stk)	return -1;
	startx++, starty++, endx++, endy++;	// �����Թ���չ��������궼Ҫ��1
	elements pos;
	pos.dir = 0, pos.x = startx, pos.y = starty;
	mark[pos.y*row2 + pos.x] = 1;
	stk->add(stk, &pos);
	int found = 0;	// 0:δ�ҵ����ʵ�·��, 1:�Ѿ��ҵ����ʵ�·��
	int x, y, dir;
	int nextx, nexty;
	while (0 == stk->empty(stk) && 0 == found)
	{
		stk->del(stk, &pos);
		x = pos.x, y = pos.y, dir = pos.dir;
		while (dir < 8 && 0 == found)
		{
			// �ƶ�����һ������
			nextx = x + move[dir].x;
			nexty = y + move[dir].y;
			if (nextx == endx && nexty == endy)
			{
				// ���ҵ�ʱ����ǰ�ڵ��Լ����սڵ�ѹջ
				pos.x = x, pos.y = y, pos.dir;
				stk->add(stk, &pos);
				pos.x = nextx, pos.y = nexty;
				stk->add(stk, &pos);
				found = 1;
			}
			// ��ͨ����δ�߹�
			else if (0 == maze2[nexty*row2 + nextx] && 0 == mark[nexty*row2 + nextx])
			{
				mark[nexty*row2 + nextx] = 1;
				pos.x = x, pos.y = y, pos.dir = ++dir; // ��ǰ�����Ѽ�飬��˷���Ҫ�ȼ�1
				stk->add(stk, &pos);
				x = nextx, y = nexty, dir = 0;
			}
			else
			{
				++dir;
			}
		}

	}

	unsigned int index1 = 0, index2 = 0, tmp = 0;
	int path_len;
	if (1 == found)
	{
		while (stk->del(stk, &pos))
		{
			path[index1++] = pos.x - 1;
			path[index1++] = pos.y - 1;
		}

		path_len = index1;

		// ����
		index1 -= 2;
		while (index2 < index1)
		{	
			tmp = path[index2], path[index2] = path[index1], path[index1] = tmp;
			tmp = path[index2+1], path[index2+1] = path[index1+1], path[index1+1] = tmp;
			index2 += 2, index1 -= 2;
		}

	}
	stack_close(stk);
	free(maze2);
	free(mark);

	if (1 == found)
	{
		return path_len;
	}
	
	return 0;
}

/*
	�Թ�������麯��: ���ڼ��path�е�·���Ƿ�Ϊ��Ч
*/
int maze_search_check(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path, int path_len)
{
	int index, x, y, nextx, nexty;

	// �������
	if (NULL == maze || col < 1 || row < 1
		|| (startx < 0 || startx >= col) || (starty < 0 || starty >= row)
		|| (endx < 0 || endx >= row) || (endy < 0 || endy >= col)
		|| NULL == path || path_len < 4)
	{
		return 0;
	}
	
	// ���ڼ��
	index = path_len - 2;
	x = path[index], y = path[index+1];
	if (x != endx || y != endy)
	{
		return 0;
	}
	// ��ڼ��
	index = 0;
	x = path[index], y = path[index+1];
	if (x != startx || y != starty
		|| 0 != maze[y*row + x])
	{
		return 0;
	}
	// ·�����
	index += 2;
	while (index < path_len)
	{
		nextx = path[index], nexty = path[index + 1];
		if (0 != maze[nexty*row + nextx]
			|| abs(x-nextx) > 1 || abs(y-nexty) > 1)
		{
			return 0;
		}

		x = nextx, y = nexty;
		index += 2;
	}

	return 1;
}