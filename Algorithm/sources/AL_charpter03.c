#include "AL_charpter03.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>

/****************************************************************
���������
�����������Ҫ���������ڣ�����a���Ʊ�ʾn, �����ķ���ֵΪ��ʾn����Ҫ��λ��
���Ӷ�: O(lgn)
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
ɸѡ����С�ڵ���n����������:
�㷨��
	���ȣ�����������Ԫ������Ϊ1����ʾû����֪�ķ�������
	Ȼ����֪Ϊ������(��Ϊ��֪�����ı���)��������Ӧ������Ԫ������Ϊ0��
	������н�С�����ı���������Ϊ0֮��,a[i]��Ȼ����Ϊ1,����ж���������
���Ӷȣ�
	��Ȼ�����������ʱ������ʽ������:
		N + N/2 + N/3 + N/7 + N/11 +  ...
	  < N + N/2 + N/3 + N/4 + ... = NH(N) (ԼΪNlnN)
	  (H(n): ���ͺ���)
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
	������������
	���Ӷ�: Nsqrt(N)
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
��Ӳ��ģ�⣺
	��һ��Ӳ��N�Σ������õ�N/2�����棬����0~N�ε�ÿһ����������ܷ�����
	k�γ��ϵĴ�������Ϊ��̬�ֲ�
	����Ӳ��ʵ��(����Ӳ��N��,��¼���泯�ϵĴ���)M��,��¼i��(0 <= i <=N)
	������ֵĴ���,rlt����Ĵ�СӦΪn+1
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
Լɪ�����⣺
	n����Χ��һȦ����1��ŵ�n���������Ȧÿ����M���˾��ų���Ӧ��,
    ÿ�����˳��к�ʣ�µ��˿�£����Ȼ����һ��������Բ�ܣ��ҳ����
    ʣ�µ���
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
Լɪ�����⣺
	������ģ������
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
��������
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
�ڽ�������⣺
����N����������ĵ�λ�������еĵ�,ͳ�ƿ��Ա�����С��d��ֱ������
�ĵ�Ķ�����
****************************************************************/
typedef struct{ double x, y; }point;

static double point_distance(point a, point b)
{
	double x = a.x - b.x, y = a.y - b.y;

	return x*x + y*y;
}

/****************************************************************
����һ��
���Ӷ�: O(N*N)
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
��ά��������룺
	ע����ַ������ô˷��������ڴ�����ʹ������a[i][j]�ı��ʽ
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
�������������:
	������Ӧ�ã����Խ�ͳ���ڽ���Ķ���Ҳ����˺�����
****************************************************************/
static void grid_insert(_link** grid, _link node, int factor, int *cnt, double d)
{
	int X = (int)(node->p.x * factor) + 1;
	int Y = (int)(node->p.y * factor) + 1;

	// ��x����yΪ1.0ʱ,Ӧ�ü�1
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
����λ�����λ���Ϊ��С��ȵĽ���������������Ȼ���ÿ������������
Ϊ�������еĵ�����һ������ͨ����ά���壬��������������֪�㸽����
�㼯�ϡ�
�ռ临�Ӷȣ� O(1/d*d + N)
ʱ�临�Ӷȣ� O(d*d*N*N) ����С��dֵ,���㷨ִ�кܿ�
****************************************************************/
int near_point(int n, double d, double *randdata)
{

	int G = (int)(1 / d);

	// ��������
	_link** grid = malloc2d(G + 2, G + 2); // �ܱ߼��ڱ�

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

	// ����(������)
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