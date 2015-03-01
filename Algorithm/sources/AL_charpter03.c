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

/****************************************************************
最近点对的计算：
	对于N个随机产生的单位正方形中的点,统计可以被长度小于d的直线连接
    的点的对数。
复杂度: O(N*N)
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