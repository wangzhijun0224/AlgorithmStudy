#include "AL_charpter03.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>

/****************************************************************
求对数函数
这个函数更重要的意义在于：若用a进制表示n, 则函数的返回值为表示n所需要的位数
复杂度: O(lgn)
****************************************************************/
int loga(int n, int a)
{
	assert(n > 0);
	assert(a > 1);

	int i;

	for (i = 0; n > 0; i++, n /= a)
		;

	return i;
}


/****************************************************************
筛选法求小于等于n的所有素数:
算法：
	首先，将所有数组元素设置为1，表示没有已知的非素数；
	然后将已知为非素数(即为已知素数的倍数)的索引对应的数组元素设置为0；
	如果所有较小素数的倍数都设置为0之后,a[i]仍然保持为1,则可判断它是素数
复杂度：
	显然，程序的运行时间与下式成正比:
		N + N/2 + N/3 + N/7 + N/11 +  ...
	  < N + N/2 + N/3 + N/4 + ... = NH(N) (约为NlnN)
	  (H(n): 调和函数)
****************************************************************/
int get_prime(int n, int* primearray)
{
	assert(n>1);
	assert(NULL != primearray);

	char *a = (char *)malloc(n+1);
	assert(a != NULL);

	int i, j;
	int cnt = 0;

	for (i = 2; i <= n; i++)
	{
		a[i] = 1;
	}

	for (i = 2; i <= n; i++)
	{
		if (1 == a[i])
		{
			for (j = i; j <= n / i; j++)
			{
				a[i*j] = 0;
			}
		}
	}

	for (i = 2; i <= n; i++)
	{
		if (1 == a[i])
		{
			primearray[cnt++] = i;
		}
	}

	free(a);

	return cnt;
}

/****************************************************************
	基本法求素数
	复杂度: Nsqrt(N)
****************************************************************/
int get_prime2(int n, int* primearray)
{
	assert(n>1);
	assert(NULL != primearray);

	int cnt = 0;
	int i, j;
	for (i = 2; i <= n; i++)
	{
		for (j = 2; j <= sqrt(i); j++)
		{
			if (0 == (i%j)) break;
		}

		if (j > sqrt(i))
		{
			primearray[cnt++] = i;
		}
	}

	return cnt;
}

/****************************************************************
抛硬币模拟：
	抛一个硬币N次，期望得到N/2次正面，但从0~N次的每一种情况都可能发生。
	k次朝上的次数近似为正态分布
	做抛硬币实验(即抛硬币N次,记录正面朝上的次数)M次,记录i次(0 <= i <=N)
	正面出现的次数,rlt数组的大小应为n+1
****************************************************************/
static int heads()
{
	return rand() < RAND_MAX / 2;
}
void throw_coin(int m, int n, int* rlt)
{
	assert(m > 1);
	assert(n > 1);
	assert(NULL != rlt);

	int cnt = 0;

	for (int i = 0; i <= n; i++)
		rlt[i] = 0;

	for (int i = 0; i < m; i++)
	{
		cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (heads())	cnt++;
		}

		rlt[cnt]++;
	}
}

/************************************** begin ***********************************************/
/***************************************************************
约瑟夫环问题：
	n个人围成一圈，从1编号到n，沿着这个圈每次数M个人就排除对应者,
    每当有人出列后，剩下的人靠拢，仍然保持一个完整的圆周，找出最后
    剩下的人
****************************************************************/
int josephus_circle(int n, int m)
{
	assert(n>1);
	assert(m >= 1);

	link head;

	head = (link)malloc(n*sizeof(*head));
	assert(head != NULL);

	for (int i = 0; i < n; i++)
	{
		head[i].item = i + 1;
		head[i].next = &head[i + 1];
	}
	head[n - 1].next = &head[0];

	link x = &head[n - 1];
	while (x != x->next)
	{
		for (int i = 1; i < m; i++)
		{
			x = x->next;
		}

		x->next = x->next->next;
	}

	int rlt = x->item;

	free(head);

	return rlt;
}

/***************************************************************
约瑟夫环问题：
	用索引模拟链表
****************************************************************/
int josephus_circle2(int n, int m)
{
	typedef struct _element
	{
		int item;
		int next;
	}josephus_element;

	assert(n>1);
	assert(m >= 1);

	josephus_element *head;

	head = (josephus_element *)malloc(n*sizeof(josephus_element));
	assert(head != NULL);

	for (int i = 0; i < n; i++)
	{
		head[i].item = i + 1;
		head[i].next = i + 1;
	}
	head[n - 1].next = 0;

	int x = n - 1;
	while (x != head[x].next)
	{
		for (int i = 1; i < m; i++)
		{
			x = head[x].next;
		}
		head[x].next = head[(head[x].next)].next;
	}

	int rlt = head[x].item;

	free(head);

	return rlt;
}
/************************************** end ***********************************************/

/****************************************************************
单链表倒置
****************************************************************/
link list_reverse(link x)
{
	assert(NULL != x);

	link t, y = x, r = NULL;

	while (y != NULL)
	{
		t = y->next;
		y->next = r;
		r = y;
		y = t;
	}

	return r;
}


/************************************** begin ***********************************************/
/****************************************************************
邻近点对问题：
对于N个随机产生的单位正方形中的点,统计可以被长度小于d的直线连接
的点的对数。
****************************************************************/
typedef struct{ double x, y; }point;

static double point_distance(point a, point b)
{
	double x = a.x - b.x, y = a.y - b.y;

	return x*x + y*y;
}

/****************************************************************
方案一：
复杂度: O(N*N)
****************************************************************/
int near_point2(int n, double d, double *randdata)
{
	assert(n > 1);
	assert(d > 0 && d < 1.0);
	assert(randdata != NULL);

	point *a = (point *)malloc(n * sizeof(point));
	assert(NULL != a);

	int cnt = 0;
	int index = 0;

	for (int i = 0; i < n; i++)
	{
		a[i].x = randdata[index++];
		a[i].y = randdata[index++];
	}

	double d2 = d*d;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (point_distance(a[i], a[j]) < d2)	cnt++;
		}
	}

	free(a);

	return cnt;
}

typedef struct _node* _link;
struct _node{ point p; _link next; };
/****************************************************************
二维数组的申请：
	注意此种方法，用此方法可以在代码中使用类似a[i][j]的表达式
****************************************************************/
static _link** malloc2d(int m, int n)
{
	_link** t = (_link**)malloc(m * sizeof(*t));
	assert(t != NULL);

	for (int i = 0; i < m; i++)
	{
		t[i] = (_link *)malloc(n * sizeof(*(t[i])));
		assert(t[i] != NULL);
	}

	return t;
}

static void free2d(_link** t, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(t[i]);
	}

	free(t);
}

/****************************************************************
将点放入网格中:
	针对这个应用，可以将统计邻近点的动作也放入此函数中
****************************************************************/
static void grid_insert(_link** grid, _link node, int factor, int *cnt, double d)
{
	int X = (int)(node->p.x * factor) + 1;
	int Y = (int)(node->p.y * factor) + 1;

	// 当x或者y为1.0时,应该减1
	if (X == factor + 1)    X -= 1;
	if (Y == factor + 1)    Y -= 1;

	for (int i = X - 1; i <= X + 1; i++)
	{
		for (int j = Y - 1; j <= Y + 1; j++)
		{
			for (_link s = grid[i][j]; s != NULL; s = s->next)
			{
				if (point_distance(node->p, s->p) < d) (*cnt)++;
			}
		}
	}

	node->next = grid[X][Y];
	grid[X][Y] = node;
}

/****************************************************************
将单位正方形划分为大小相等的叫嚣的正方形网格。然后对每个正方形网格，
为所有其中的点生成一个链表。通过二维素族，可以立即访问已知点附近的
点集合。
空间复杂度： O(1/d*d + N)
时间复杂度： O(d*d*N*N) 对于小的d值,本算法执行很快
****************************************************************/
int near_point(int n, double d, double *randdata)
{

	int G = (int)(1 / d);

	// 生成网格
	_link** grid = malloc2d(G + 2, G + 2); // 周边加哨兵

	for (int i = 0; i < G + 2; i++)
	{
		for (int j = 0; j < G + 2; j++)
		{
			grid[i][j] = NULL;
		}
	}

	_link head = (_link)malloc(n*sizeof(*head));
	assert(head != NULL);

	double d2 = d*d;
	int cnt = 0;

	// 撒点(并计算)
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		head[i].p.x = randdata[index++];
		head[i].p.y = randdata[index++];

		grid_insert(grid, &head[i], G, &cnt, d2);	
	}

	free(head);
	free2d(grid, G + 2);

	return cnt;
}
/************************************** begin ***********************************************/