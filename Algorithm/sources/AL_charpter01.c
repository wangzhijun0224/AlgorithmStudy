#include "AL_charpter01.h"

#include <stdlib.h>
#include <stdio.h>
/*
	ע����������������ʾ����ɭ�ֵķ���
*/
/***************************************************************
��ͨ������֮���ٲ�������:
��������������ʣ� ���ҽ�����p���͵�q�����������ʱ,p��q��ͨ��
�㷨: ����i��Ԫ�س�ʼ��Ϊi������0<=i<N��Ϊ�˶�p��qʵ�ֲ�������,
�������飬�����к͵�p��Ԫ��ֵ��ȵ�Ԫ�ص�ֵ����Ϊ��q��Ԫ�ص�ֵ.
����: ���ھ���N������ÿ���������M�������������ͨ�����⣬
���㷨������ΪO(M*N)
����: m: ��ͨ�Եĸ���, n: n������, out: ����ǰ�ĶԲ��ڼ����У��������out��
����ֵ: ��ӵ���ͨ�Ը���
***************************************************************/
int connectivity_quickfind(pair pairs[], int m, int id[], int n, int out[])
{
	int p, q, i, j, t;
	int index = 0;

	for (i = 0; i < n; ++i)
	{
		id[i] = i;
	}

	for (i = 0; i < m; ++i)
	{
		p = pairs[i].p;
		q = pairs[i].q;

		if (id[p] == id[q])   continue;

		for (t = id[p], j = 0; j < n; ++j)
		{
			if (id[j] == t) id[j] = id[q];
		}

		out[index++] = p;
		out[index++] = q;
	}

	return index;
}

/***************************************************************
��ͨ������֮���ٲ�������:
ÿ������ָ��ͬһ�������е���һ������Ϊ���ж����������Ƿ�λ��
ͬһ�����ϣ����������������ָ�룬ֱ������ָ������Ķ��󡣵��ҽ���
������̵õ�ͬһ������ʱ����Щ�����λ����ͬ�ļ����С�
������ʵ����M������ÿ��Ԫ���д洢�������ĸ��ڵ㣬�����������ʣ�
���ҽ�����������������ͨʱ�����е�����������ͨ�����������ƣ�
�����ҵ�ÿ������ĸ�(root)������ͬ�Ķ���������ͨ��
�����ų�һ����ʱ���������,���һ��ӵ��N������M���Ե���ͨ����
������ҪO(M*N/2)
***************************************************************/
int connectivity_quickunion(pair pairs[], int m, int id[], int n, int out[])
{
	int p, q, i, j, k;
	int index = 0;

	for (i = 0; i < n; ++i)
	{
		id[i] = i;
	}

	for (k = 0; k < m; ++k)
	{
		p = pairs[k].p;
		q = pairs[k].q;

		for (i = p; i != id[i]; i = id[i]);

		for (j = q; j != id[j]; j = id[j]);

		if (i == j) continue;

		id[i] = j;

		out[index++] = p;
		out[index++] = q;
	}

	return index;
}

/***************************************************************
��Ȩ���ٲ����㷨��
�Կ��ٲ����ĸĽ���������һ������������ڵ�ڵ���������ʱ��
������������ͨ�ڶ��������һ������������ͨ��С����ϴ�����
�ж�N����������������Ƿ���ͨ�����Ҫ����2*lgN��ָ�롣
***************************************************************/
int connectivity_weighted_quickunion(pair pairs[], int m, int id[], int n, int out[])
{
	int i, j, k, p, q;
	int index = 0;

	int *sz = (int *)malloc(n*sizeof(int));
	if (NULL == sz)
	{
		printf("\n No enough memory!!! \n");
		return -1;
	}

	for (i = 0; i < n; i++)
	{
		id[i] = i;
		sz[i] = 1;
	}

	for (k = 0; k < m; ++k)
	{
		p = pairs[k].p;
		q = pairs[k].q;

		for (i = p; i != id[i]; i = id[i]);

		for (j = q; j != id[j]; j = id[j]);

		if (i == j) continue;

		if (sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[i];
		}

		out[index++] = p;
		out[index++] = q;
	}

	free(sz);

	return index;
}

/***************************************************************
���Է�·��ѹ���ļ�Ȩ���ٲ����㷨��
***************************************************************/
int connectivity_pathcompression_weighted_quickunion(pair pairs[], int m, int id[], int n, int out[])
{
	int i, j, k, p, q;
	int index = 0;

	int *sz = (int *)malloc(n*sizeof(int));
	if (NULL == sz)
	{
		printf("\n No enough memory!!! \n");
		return -1;
	}

	for (i = 0; i < n; i++)
	{
		id[i] = i;
		sz[i] = 1;
	}

	for (k = 0; k < m; ++k)
	{
		p = pairs[k].p;
		q = pairs[k].q;

		// �Է�·��ѹ��
		for (i = p; i != id[i]; i = id[i])
		{
			id[i] = id[id[i]];
		}

		for (j = q; j != id[j]; j = id[j])
		{
			id[i] = id[id[i]];
		}

		if (i == j) continue;

		// ����
		if (sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[i];
		}

		out[index++] = p;
		out[index++] = q;
	}

	return index;
}