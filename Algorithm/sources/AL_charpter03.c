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

/****************************************************************
�����Եļ��㣺
	����N����������ĵ�λ�������еĵ�,ͳ�ƿ��Ա�����С��d��ֱ������
    �ĵ�Ķ�����
���Ӷ�: O(N*N)
****************************************************************/
typedef struct{ double x, y; }point;
static double rand_float(void)
{
	return 1.0*rand() / RAND_MAX;
}
static double point_distance(point a, point b)
{
	double x = a.x - b.x, y = a.y - b.y;

	return x*x + y*y;
}
int near_point(int n, double d)
{
	assert(n > 1);
	assert(d > 0 && d < 1.0);

	point *a = (point *)malloc(n * sizeof(point));
	assert(NULL != a);

	int cnt = 0;

	for (int i = 0; i < n; i++)
	{
		a[i].x = rand_float();
		a[i].y = rand_float();
	}

	d = d*d;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (point_distance(a[i], a[j]) < d)	cnt++;
		}
	}

	free(a);

	return cnt;
}