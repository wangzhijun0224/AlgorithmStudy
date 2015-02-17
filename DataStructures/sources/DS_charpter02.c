#include "DS_charpter02.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void polynomial1_print(polynomial1* poly)
{
	for (int i = 0; i <= poly->degree; ++i)
	{
		printf("%f\t", poly->coef[i]);
	}
	printf("\n");
}

/***********************************************************************************
	Horner规则求多项式的值
***********************************************************************************/
double polynomial1_sum(polynomial1* poly, double x0)
{
	double sum = 0.0;

	for (int i = 0; i <= poly->degree; ++i)
	{
		sum = sum*x0 + poly->coef[i];
	}

	return sum;
}

/***********************************************************************************
	多项式相加
***********************************************************************************/
void polynomial1_add(polynomial1* a, polynomial1* b, polynomial1* c)
{
	int i = 0, j = 0;
	int degreea = a->degree + 1;
	int degreeb = b->degree + 1;

	while (i != degreea && i != degreeb)
	{
		c->coef[j++] = a->coef[i] + b->coef[i];
		i++;
	}

	while (i != degreea)
	{
		c->coef[j++] = a->coef[i++];
	}

	while (i != degreeb)
	{
		c->coef[j++] = b->coef[i++];
	}

	c->degree = j - 1;
}

/***********************************************************************************
多项式相加
***********************************************************************************/
void polynomial2_add(polynomial2* a, polynomial2* b, polynomial2* c)
{
	int i = 0, j = 0;
	int counta = a->count, countb = b->count, countc = 0;
	
	while (i != counta && j != countb)
	{
		if (a->poly[i].expon < b->poly[j].expon)
		{
			c->poly[countc].expon = a->poly[i].expon;
			c->poly[countc++].coef = a->poly[i++].coef;
		}
		else if (a->poly[i].expon > b->poly[j].expon)
		{
			c->poly[countc].expon = b->poly[j].expon;
			c->poly[countc++].coef = b->poly[j++].coef;
		}
		else
		{
			c->poly[countc].expon = a->poly[i].expon;
			c->poly[countc++].coef = a->poly[i++].coef + b->poly[j++].coef;
		}
	}

	while (i != counta)
	{
		c->poly[countc].expon = a->poly[i].expon;
		c->poly[countc++].coef = a->poly[i++].coef;
	}

	while (j != countb)
	{
		c->poly[countc].expon = b->poly[j].expon;
		c->poly[countc++].coef = b->poly[j++].coef;
	}

	c->count = countc;
}

void sparematrix_set(sparematrixitem a[], int col, int row)
{
	a[0].col = col;
	a[0].row = row;
	a[0].value = 0;
}

void sparematrix_additem(sparematrixitem a[], int col, int row, int value)
{
	int current = (++a[0].value);

	a[current].col = col;
	a[current].row = row;
	a[current].value = value;

}
/***********************************************************************************
	稀疏矩阵的转置:(复杂性: O(columns*elements))
	将稀疏矩阵a转置到b中
***********************************************************************************/
void sparematrix_transpose(sparematrixitem a[], sparematrixitem b[])
{
	int n, i, j, currentb;
	n = a[0].value;			// 元素总数

	b[0].row = a[0].col;	// b的列数 = a的行数	
	b[0].col = a[0].row;	// b的行数 = a的列数
	b[0].value = n;	

	if (n <= 0)	return;
	
	currentb = 1;
	for (i = 0; i < a[0].col; i++)	// i为矩阵行号
	{
		// 找出当前行所有元素
		for (j = 1; j <= n; j++)
		{
			if (a[j].row == i)
			{
				b[currentb].row = a[j].col;
				b[currentb].col = a[j].row;
				b[currentb++].value = a[j].value;
			}
		}
	}
}

/***********************************************************************************
稀疏矩阵的快速转置:(复杂性: O(columns+elements))
	首先确定原矩阵中每列元素的个数,也即转置矩阵中每行元素的个数;
	然后得到转置矩阵每行的起始位置
***********************************************************************************/
void sparematrix_fast_transpose(sparematrixitem a[], sparematrixitem b[])
{
	int i, j, num_cols = a[0].row, num_terms = a[0].value;

	int *row_terms = (int *)malloc(num_cols*sizeof(int));
	int *start_pos = (int *)malloc(num_cols*sizeof(int));

	if (NULL == row_terms || NULL == start_pos)
	{
		printf("\n have no enough memory.\n");
	}

	memset(row_terms, 0x00, num_cols*sizeof(int));
	start_pos[0] = 1;


	b[0].col = num_cols, b[0].row = a[0].col, b[0].value = num_terms;

	if (num_terms <= 0)
	{
		printf("input data error.\n");
		return;
	}

	// 统计原矩阵每列元素的个数，也即转置矩阵每行元素的个数
	for (i = 1; i <= num_terms; i++)
	{
		row_terms[a[i].row]++;
	}

	// 计算转置矩阵每行元素的起始位置
	for (i = 1; i < num_cols; i++)
	{
		start_pos[i] = start_pos[i - 1] + row_terms[i - 1];
	}
	
	// 计算转置矩阵
	for (i = 1; i <= num_terms; i++)
	{
		j = start_pos[a[i].row]++;
		b[j].row = a[i].col;
		b[j].col = a[i].row;
		b[j].value = a[i].value;
	}

	free(row_terms);
	free(start_pos);
}

static void storesum(sparematrixitem d[], int * indexd, int col, int row, int *sum);
/***********************************************************************************
矩阵乘法：
	先将b转置,再多项式求和	
***********************************************************************************/
void sparematrix_mult(sparematrixitem a[], sparematrixitem b[], sparematrixitem d[])
{
	int count_a = a[0].value, count_b = b[0].value;
	int col, row;
	int indexd = 1;
	int col_begin = 1; // 第i行的开始坐标
	int sum = 0;

	if (a[0].row != b[0].col)
	{
		printf("Incompatible matrices.\n");
		return;
	}

	sparematrixitem *trans_b = (sparematrixitem *)malloc((count_b+2)* sizeof(sparematrixitem));
	if (NULL == trans_b)
	{
		printf("\nhave no enough memory.\n");
		return;
	}

	sparematrix_fast_transpose(b, trans_b);

	// 设置哨兵，用于简化比较过程
	a[count_a + 1].col = a[0].col;	// 注意,此处要求a至少比实际的矩阵个数多1
	trans_b[count_b+1].col = b[0].row;

	col = a[1].col;
	for (int i = 1; i <= count_a; )	// 行循环
	{
		row = trans_b[1].col;	// 转置矩阵的行号,即转置前的列号
		for (int j = 1; j <= count_b+1;)	// 注意,每行最后一个元素时,j能到达count_b+1
		{
			if (a[i].col != col)	// 表示到了第i+1行
			{
				storesum(d, &indexd, col, row, &sum);
				i = col_begin;
				for (; trans_b[j].col == row; j++)	// 注意哨兵项的作用
					;
				row = trans_b[j].col;	// 第i行下一个元素
			}
			else if (trans_b[j].col != row)	// 第i行下一个元素
			{
				storesum(d, &indexd, col, row, &sum);
				i = col_begin;
				for (; trans_b[j].col == row; j++) // 注意哨兵项的作用
					;
				row = trans_b[j].col;
			}
			else
			{
				if (a[i].row < trans_b[j].row)
				{
					i++;
				}
				else if (a[i].row > trans_b[j].row)
				{
					j++;
				}
				else
				{
					sum += (a[i++].value * trans_b[j++].value);
				}
			}
		}

		// 转到下一行
		for (; a[i].col == col; i++) // 注意哨兵项的作用
			;
		col_begin = i;
		col = a[i].col;
	}

	d[0].col = a[0].col;
	d[0].row = b[0].row;
	d[0].value = indexd-1;

	free(trans_b);
}


static void storesum(sparematrixitem d[], int * indexd, int col, int row, int *sum)
{
	if (0 != *sum)
	{
		d[*indexd].col = col;
		d[*indexd].row = row;
		d[*indexd].value = *sum;
		(*indexd)++;
		*sum = 0;
	}
}