#include "DS_charpter03.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#if (!USE_DEQUEUE_FOR_STACK_AND_QUEUE)
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
#endif

/***********************************************************************************
	栈的应用: 迷宫搜索算法
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
	maze:			迷宫，值为0表示联通，值为1表示阻断;
	col,row:		迷宫的行数和列数
	startx,starty:	迷宫的开始位置
	endx,endy:		要到达的迷宫位置
	path:			输出参数，找到的移动路径
	返回值: -1：搜索失败(有参数错误或者系统无内存);
			0:	未搜索到有效路径;
			path_len:	搜索到的有效路径长度;
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

	// 8个移动方向,依次对应方向(dir)为: 0, 1, 2, 3, 4, 5, 6, 7
	offsets move[8] = { 
		{ -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 },
		{ 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }
	};

	// 1. 迷宫扩展:在迷宫的边缘全加上墙，以简化边缘上的迷宫移动方向检查
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

	// mark数组，用于记录已经检查过的迷宫位置
	unsigned char *mark = (unsigned char *)malloc(col2*row2*sizeof(unsigned char));
	if (NULL == mark)
	{
		free(maze2);
		return -1;
	}
	memset(mark, 0, col2*row2*sizeof(unsigned char));


	// 迷宫搜索
	stack *stk = stack_open(col2*row2, sizeof(elements));
	if (NULL == stk)	return -1;
	startx++, starty++, endx++, endy++;	// 由于迷宫扩展，因此坐标都要加1
	elements pos;
	pos.dir = 0, pos.x = startx, pos.y = starty;
	mark[pos.y*row2 + pos.x] = 1;
	stk->add(stk, &pos);
	int found = 0;	// 0:未找到合适的路径, 1:已经找到合适的路径
	int x, y, dir;
	int nextx, nexty;
	while (0 == stk->empty(stk) && 0 == found)
	{
		stk->del(stk, &pos);
		x = pos.x, y = pos.y, dir = pos.dir;
		while (dir < 8 && 0 == found)
		{
			// 移动到下一个方向
			nextx = x + move[dir].x;
			nexty = y + move[dir].y;
			if (nextx == endx && nexty == endy)
			{
				// 查找到时将当前节点以及最终节点压栈
				pos.x = x, pos.y = y, pos.dir;
				stk->add(stk, &pos);
				pos.x = nextx, pos.y = nexty;
				stk->add(stk, &pos);
				found = 1;
			}
			// 连通并且未走过
			else if (0 == maze2[nexty*row2 + nextx] && 0 == mark[nexty*row2 + nextx])
			{
				mark[nexty*row2 + nextx] = 1;
				pos.x = x, pos.y = y, pos.dir = ++dir; // 当前方向已检查，因此方向要先加1
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

		// 倒序
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
	迷宫搜索检查函数: 用于检查path中的路径是否为有效
*/
int maze_search_check(unsigned char *maze, int col, int row,
	int startx, int starty, int endx, int endy, unsigned int *path, int path_len)
{
	int index, x, y, nextx, nexty;

	// 参数检查
	if (NULL == maze || col < 1 || row < 1
		|| (startx < 0 || startx >= col) || (starty < 0 || starty >= row)
		|| (endx < 0 || endx >= row) || (endy < 0 || endy >= col)
		|| NULL == path || path_len < 4)
	{
		return 0;
	}
	
	// 出口检查
	index = path_len - 2;
	x = path[index], y = path[index+1];
	if (x != endx || y != endy)
	{
		return 0;
	}
	// 入口检查
	index = 0;
	x = path[index], y = path[index+1];
	if (x != startx || y != starty
		|| 0 != maze[y*row + x])
	{
		return 0;
	}
	// 路径检查
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

/***********************************************************************************
栈的应用: 后缀表达式求值
***********************************************************************************/
// 左括号，右括号，加，减，乘，除，求余，操作数
typedef enum{lparen, rparen, plus, minus, times, divide, mod, eos, operand}en_precedence;

// 获取一个词元
static en_precedence get_token(const char* expr, int *location, char** symbol)
{
	static char words[100] = { 0 };
	int index = 1;
	en_precedence ret;

	while (' ' == expr[(*location)]) // 过滤掉多余的空格
	{
		(*location)++;
	}

	words[0] = expr[(*location)++];
	switch (words[0])
	{
	case '(':  ret = lparen; break;
	case ')':   ret = rparen; break;
	case '+':  ret = plus;  break;
	case '-':  ret = minus; break;
	case '*':  ret = times; break;
	case '/':  ret = divide; break;
	case '%':  ret = mod;  break;
	case '\0':  ret = eos;  break;
	default: ret = operand; break; // 默认为操作数,无错误检查
	}

	if (operand == ret)
	{
		while (expr[(*location)] >= '0' && expr[(*location)] <= '9')
		{
			words[index++] = expr[(*location)++];
		}
	}

	words[index] = '\0';
	*symbol = words;

	return ret;
}


/* 
	后缀表达式求值: (仅支持'+''-' '*' '/' '%'操作,要求操作数之间以' '隔开)
	返回值: 1表示成功，0表示失败
*/
int postfix_expr_eval(const char* postfix_expr, int *pvalue)
{
	if (NULL == postfix_expr || NULL == pvalue)
	{
		return 0;
	}

	stack *stk = stack_open(100, sizeof(int));
	if (NULL == stk)
	{
		return 0;
	}

	int op1, op2;
	int symbol;
	char* chsymbol;
	en_precedence token;
	int index = 0;

	token = get_token(postfix_expr, &index, &chsymbol);
	while (eos != token)
	{
		if (operand == token)
		{
			symbol = atoi(chsymbol);
			stk->add(stk, &symbol);
		}
		else
		{
			stk->del(stk, &op2);
			stk->del(stk, &op1);
			switch (token)
			{
			case plus:		symbol = op1 + op2;	break;
			case minus:		symbol = op1 - op2;	break;
			case times:		symbol = op1 * op2;	break;
			case divide:	symbol = op1 / op2;	break;
			case mod:		symbol = op1 % op2;	break;
			}
			stk->add(stk, &symbol);
		}
		token = get_token(postfix_expr, &index, &chsymbol);
	}

	stk->del(stk, pvalue);

	stack_close(stk);
	return 1;
}

/*
	中缀表达式转后缀表达式:
	运算符入栈和出栈基于运算符优先级。每当在表达式中遇到左括号，就将其入栈，直到遇到
	相应的右括号时，才将其出栈(左括号在栈中时，表现为一个低优先级的运算符，而不在栈中
	时，是一个高优先级的运算符)。因此，有两种优先级：栈内优先级(isp)和引入优先级(icp)。
		返回值: 1表示成功，0表示失败
*/
int middlefix_to_postfix(const char* middlefix_expr, char* postfix_expr)
{
	// 栈内优先级和引入优先级，依次是en_precedence的优先级
	static const int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
	static const int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
	static const char* token_str[] = {
		"( ", ") ", "+ ", "- ", "* ", "/ ", "% ", "", ""
	};

	if (NULL == middlefix_expr || NULL == postfix_expr)
	{
		return 0;
	}

	

	stack *stk = stack_open(100, sizeof(int));
	if (NULL == stk)
	{
		return 0;
	}

	char* chsymbol;
	en_precedence token, token2;
	int index = 0, postfix_index = 0;
	
	token = eos;
	stk->add(stk, &token);

	for (token = get_token(middlefix_expr, &index, &chsymbol);
		token != eos; 
		token = get_token(middlefix_expr, &index, &chsymbol))
	{
		if (operand == token)
		{
			strcpy(&postfix_expr[postfix_index], chsymbol);	
			postfix_index += strlen(chsymbol);
			postfix_expr[postfix_index++] = ' ';  // 操作数之后加空格，以保证操作数之间以空格隔开
		}
		else if (rparen == token)
		{
			for (stk->del(stk, &token2); token2 != lparen; stk->del(stk, &token2))
			{
				strcpy(&postfix_expr[postfix_index], token_str[token2]);	
				postfix_index += strlen(token_str[token2]);	
			}
		}
		else
		{
			for (stk->del(stk, &token2); isp[token2] >= icp[token]; stk->del(stk, &token2))
			{
				strcpy(&postfix_expr[postfix_index], token_str[token2]);	
				postfix_index += strlen(token_str[token2]);	
			}
			stk->add(stk, &token2);	// 归还获取的小于当前token的运算符
			stk->add(stk, &token);
		}
	}

	for (stk->del(stk, &token2); token2 != eos; stk->del(stk, &token2))
	{
		strcpy(&postfix_expr[postfix_index], token_str[token2]);	
		postfix_index += strlen(token_str[token2]);	
	}

	postfix_expr[postfix_index] = '\0';
	
	stack_close(stk);

	return 1;

}

#if (!USE_DLIST_FOR_DEQUEUE)
/***********************************************************************************
双端队列之数组实现
***********************************************************************************/
static int dequeue_full(void* handle)
{
	dequeue *dq = (dequeue*)handle;

	return (dq->_cnt == dq->_dequeue_size);
}

static int dequeue_empty(void * handle)
{
	dequeue *dq = (dequeue*)handle;

	return (dq->_cnt == 0);
}

static int dequeue_add_front(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->full(handle))
	{
		return 0;
	}


	char *dst = (char *)dq->_dequeue;
	dst += dq->_front * dq->_element_size;
	memcpy(dst, pitem, dq->_element_size);

	dq->_front = (dq->_front + 1) % (dq->_dequeue_size);
	dq->_cnt++;

	return 1;
}

static int dequeue_add_rear(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->full(handle))
	{
		return 0;
	}


	char *dst = (char *)dq->_dequeue;
	dst += dq->_rear * dq->_element_size;
	memcpy(dst, pitem, dq->_element_size);

	if (0 == dq->_rear)
	{
		dq->_rear = dq->_dequeue_size - 1;
	}
	else
	{
		dq->_rear--;
	}

	dq->_cnt++;

	return 1;
}

static int dequeue_del_front(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->empty(handle))
	{
		return 0;
	}

	if (dq->_front == 0)
	{
		dq->_front = dq->_dequeue_size - 1;
	}
	else
	{
		dq->_front -= 1;
	}

	char *src = (char *)dq->_dequeue;
	src += dq->_front * dq->_element_size;
	memcpy(pitem, src, dq->_element_size);

	dq->_cnt--;

	return 1;
}

static int dequeue_del_rear(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->empty(handle))
	{
		return 0;
	}

	dq->_rear = (dq->_rear + 1) % dq->_dequeue_size;

	char *src = (char *)dq->_dequeue;
	src += dq->_rear * dq->_element_size;
	memcpy(pitem, src, dq->_element_size);

	dq->_cnt--;

	return 1;
}

dequeue* dequeue_open(int dequeue_size, int element_size)
{
	assert(dequeue_size >= 0);
	assert(element_size >= 1);

	dequeue* dq = (dequeue*)malloc(sizeof(dequeue));
	assert(NULL != dq);

	dq->_dequeue_size = (dequeue_size == 0 ? DEFAULT_DEQUEUE_SIZE : dequeue_size);
	dq->_dequeue = malloc(dq->_dequeue_size * element_size);
	if (NULL == dq->_dequeue)
	{
		free(dq);
		return NULL;
	}

	dq->_rear = dq->_dequeue_size - 1;
	dq->_front = 0;
	dq->_element_size = element_size;
	dq->_cnt = 0;

	dq->full = dequeue_full;
	dq->empty = dequeue_empty;
	dq->add_front = dequeue_add_front;
	dq->del_front = dequeue_del_front;
	dq->add_rear = dequeue_add_rear;
	dq->del_rear = dequeue_del_rear;

	return dq;
}

void dequeue_close(dequeue* handle)
{
	free(handle->_dequeue);
	free(handle);
}
#endif

#if (USE_DEQUEUE_FOR_STACK_AND_QUEUE)
/***********************************************************************************
栈之双端队列实现
***********************************************************************************/
static int stack_full(void *handle)
{
	stack* stk = (stack*)handle;

	return stk->_dq->full(stk->_dq);
}
static int stack_empty(void *handle)
{
	stack* stk = (stack*)handle;
	return stk->_dq->empty(stk->_dq);
}
static int stack_add(void *handle, void* pitem)
{
	stack* stk = (stack*)handle;
	return stk->_dq->add_front(stk->_dq, pitem);
}
static int stack_del(void *handle, void *pitem)
{
	stack* stk = (stack*)handle;
	return stk->_dq->del_front(stk->_dq, pitem);
}
// ======================================================
stack* stack_open(int stk_size, int element_size)
{
	assert(stk_size >= 0);
	assert(element_size >= 1);
	stack *stk = (stack *)malloc(sizeof(stack));
	assert(NULL != stk);
	stk->_dq = dequeue_open(stk_size, element_size);
	if (NULL == stk->_dq)
	{
		free(stk);
		return NULL;
	}
	stk->full = stack_full;
	stk->empty = stack_empty;
	stk->add = stack_add;
	stk->del = stack_del;
	return stk;
}
void stack_close(stack* handle)
{
	dequeue_close(handle->_dq);
	free(handle);
}
/***********************************************************************************
队列之双端队列实现
***********************************************************************************/
static int queue_full(void *handle)
{
	queue* q = (queue*)handle;
	return q->_dq->full(q->_dq);
}
static int queue_empty(void *handle)
{
	queue* q = (queue*)handle;
	return q->_dq->empty(q->_dq);
}
static int queue_add(void *handle, void* pitem)
{
	queue* q = (queue*)handle;
	return q->_dq->add_front(q->_dq, pitem);
}
static int queue_del(void *handle, void *pitem)
{
	queue* q = (queue*)handle;
	return q->_dq->del_rear(q->_dq, pitem);
}
// ======================================================
queue* queue_open(int queue_size, int element_size)
{
	assert(queue_size >= 0);
	assert(element_size >= 1);
	queue *q = (queue *)malloc(sizeof(queue));
	assert(NULL != q);
	q->_dq = dequeue_open(queue_size, element_size);
	if (NULL == q->_dq)
	{
		free(q);
		return NULL;
	}
	q->full = queue_full;
	q->empty = queue_empty;
	q->add = queue_add;
	q->del = queue_del;
	return q;
}
void queue_close(queue* handle)
{
	dequeue_close(handle->_dq);
	free(handle);
}
#endif


/***********************************************************************************
节点抽象
***********************************************************************************/
// 非完整类型抽象，申请节点的时候需要申请sizeof(_node)+sizeof(item)大小
typedef struct _node
{
	dlink prev;
	dlink next;
}node;

static dlink new_node(int item_size)
{
	dlink tmpnode = (dlink)malloc(sizeof(*tmpnode) + item_size);
	assert(NULL != tmpnode);
	tmpnode->prev = tmpnode->next = NULL;

	return tmpnode;
}

static void copy_item_to_node(dlink node, void *pitem, int item_size)
{
	void *dst = (char *)node + sizeof(*node);
	memcpy(dst, pitem, item_size);
}

static void link_get_item(dlink p, int item_size, void *pitem)
{
	void *src = (char *)p + sizeof(*p);
	memcpy(pitem, src, item_size);
}

// newnode插在p之后
static void link_insert_after(dlink p, dlink newnode)
{
	newnode->prev = p;
	newnode->next = p->next;
	p->next->prev = newnode;
	p->next = newnode;
}

static void link_insert_before(dlink p, dlink newnode)
{
	newnode->next = p;
	newnode->prev = p->prev;
	p->prev->next = newnode;
	p->prev = newnode;
}

static void link_del(dlink p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);

}

#if USE_DLIST_FOR_DEQUEUE
static int dequeue_full(void* handle)
{
	dequeue *dq = (dequeue*)handle;

	if (dq->_size == 0)
	{
		return 0;
	}

	return (dq->_size == dq->_cnt);
}

static int dequeue_empty(void * handle)
{
	dequeue *dq = (dequeue*)handle;

	return (dq->_cnt == 0);
}

static int dequeue_add_front(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->full(handle))
	{
		return 0;
	}

	dlink newnode = new_node(dq->_element_size);
	copy_item_to_node(newnode, pitem, dq->_element_size);

	link_insert_after(dq->_guard, newnode);

	dq->_cnt++;

	return 1;
}


static int dequeue_add_rear(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->full(handle))
	{
		return 0;
	}

	dlink newnode = new_node(dq->_element_size);
	copy_item_to_node(newnode, pitem, dq->_element_size);

	link_insert_before(dq->_guard, newnode);

	dq->_cnt++;

	return 1;
}

static int dequeue_del_front(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->empty(handle))
	{
		return 0;
	}

	dlink head = dq->_guard->next;
	link_get_item(head, dq->_element_size, pitem);
	link_del(head);

	dq->_cnt--;

	return 1;
}

static int dequeue_del_rear(void *handle, void* pitem)
{
	dequeue *dq = (dequeue*)handle;

	if (1 == dq->empty(handle))
	{
		return 0;
	}

	dlink tail = dq->_guard->prev;
	link_get_item(tail, dq->_element_size, pitem);
	link_del(tail);

	dq->_cnt--;

	return 1;
}

dequeue* dequeue_open(int dequeue_size, int element_size)
{
	assert(element_size >= 1);

	dequeue* dq = (dequeue*)malloc(sizeof(dequeue));
	assert(NULL != dq);

	dq->_element_size = element_size;
	dq->_size = dequeue_size < 0 ? 0 : dequeue_size;
	dq->_cnt = 0;

	dq->_guard = new_node(0);	// 哨兵节点不带数据域
	dq->_guard->next = dq->_guard->prev = dq->_guard;	// 循环链表

	dq->full = dequeue_full;
	dq->empty = dequeue_empty;
	dq->add_front = dequeue_add_front;
	dq->del_front = dequeue_del_front;
	dq->add_rear = dequeue_add_rear;
	dq->del_rear = dequeue_del_rear;

	return dq;
}

void dequeue_close(dequeue* handle)
{
	dlink tmp1, tmp2;

	tmp1 = handle->_guard->next;
	while (tmp1 != handle->_guard)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	
	free(handle->_guard);
	free(handle);
}
#endif