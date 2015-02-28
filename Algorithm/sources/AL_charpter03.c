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
