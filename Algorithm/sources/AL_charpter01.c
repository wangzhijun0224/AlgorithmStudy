#include "AL_charpter01.h"

#include <stdlib.h>
#include <stdio.h>
/*
	注意此问题中用数组表示树和森林的方法
*/
/***************************************************************
连通性问题之快速查找运算:
数组具有如下性质： 当且仅当第p个和第q个数组想相等时,p与q连通。
算法: 将第i个元素初始化为i，其中0<=i<N。为了对p与q实现并集运算,
遍历数组，将所有和第p个元素值相等的元素的值更改为第q个元素的值.
性能: 对于具有N个对象，每个对象包括M个并集运算的连通性问题，
该算法的性能为O(M*N)
参数: m: 连通对的个数, n: n个对象, out: 若当前的对不在集合中，这输出到out中
返回值: 添加的连通对个数
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
连通性问题之快速并集运算:
每个对象指向同一个集合中的另一个对象。为了判断两个对象是否位于
同一个集合，跟踪这两个对象的指针，直到到达指向自身的对象。当且仅当
这个过程得到同一个对象时，这些对象才位于相同的集合中。
这数组实际是M颗树，每个元素中存储的是它的父节点，具有如下性质：
当且仅当对象在输入中连通时，树中的两个对象连通。沿着树上移，
容易找到每个对象的根(root)，根相同的对象则是连通。
当树排成一条线时，性能最差,解决一个拥有N个对象、M个对的连通问题
可能需要O(M*N/2)
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
加权快速并集算法：
对快速并集的改进：利用另一个数组来保存节点节点数，并的时候
不再是任意连通第二棵树与第一棵树，而是连通较小树与较大树。
判断N个对象的其中两个是否连通，最多要跟踪2*lgN个指针。
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
带对分路径压缩的加权快速并集算法：
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

		// 对分路径压缩
		for (i = p; i != id[i]; i = id[i])
		{
			id[i] = id[id[i]];
		}

		for (j = q; j != id[j]; j = id[j])
		{
			id[i] = id[id[i]];
		}

		if (i == j) continue;

		// 并集
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