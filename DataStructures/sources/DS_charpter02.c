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

/***********************************************************************************
	魔方问题:
		一个魔方就是一个由1到n*n的整数构成的n*n矩阵,其中每行、每列以及两个主对角线上的数字
	之和相等。
		当n为奇数时，Coxeter给出了下列产生魔方的简单法则:
		把1放入第一行最中间的方格中。向左上方移动，并按照数字递增的顺序，把数字填入空方格。
	如果移出了魔方边界，这进入魔方对边的对应方格。继续填写方格。如果一个方格已被填数字，
	则向下继续填写方格。
***********************************************************************************/
void magic_square_create(int *square, int n)
{
	if (NULL == square || n < 1 || ((n%2)!= 1))
	{
		printf("input param is error.\n");
		return;
	}

	memset(square, 0x00, n*n*sizeof(int));

	int i = 0, j = n / 2;

	square[i*n + j] = 1;
	for (int data = 2; data <= n*n; data++)
	{
		i--;
		if (i < 0) i = n - 1;
		
		j--;
		if (j < 0) j = n - 1;

		while (square[i*n + j])
		{
			i = (i + 2) % n;
			j = (j + 1) % n;
		}

		square[i*n + j] = data;
	}

}

/***********************************************************************************
	魔方矩阵检查函数：
		检查了行，列及对角线的和，检查数组是否是由1-n*n的数字组成
***********************************************************************************/
int magic_square_check(int *square, int n)
{
	if (NULL == square || n < 1)
	{
		printf("input param is error.\n");
		return 0;
	}

	// 数字检查
	char *datacheck = (char *)malloc(n*n);
	if (NULL == datacheck)
	{
		printf("\nhave no enough memory.\n"); 
		return 0;
	}
	memset(datacheck, 0x00, n*n);
	for (int i = 0; i < n * n; i++)
	{
		if (square[i] <= n*n)
			datacheck[square[i]-1] = 1;
		else
		{
			free(datacheck);
			return 0;
		}
	}
	for (int i = 0; i < n*n; i++)
	{
		if (datacheck[i] != 1)
		{
			free(datacheck);
			return 0;
		}
			
	}
	free(datacheck);

	// 计算第一行的和
	int sum1 = 0, sum2 = 0;
	int *p = square;

	for (int i = 0; i < n; i++)
	{
		sum1 += square[i];
	}

	// 每行和检查
	p += n;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum2 += p[j];
		}

		if (sum2 != sum1)
		{
			return 0;
		}
		else
		{
			sum2 = 0;
			p += n;
		}
	}

	// 每列和检查
	p = square;
	for (int i = 0; i < n; i++)	// 列
	{
		sum2 = 0;
		for (int j = 0; j < n; j++)	// 行
		{
			sum2 += p[j*n + i];
		}

		if (sum2 != sum1)
		{
			return 0;
		}
	}

	// 对角线1检查
	sum2 = 0;
	for (int i = 0; i < n; i++)
	{
		sum2 += p[i*n + i];
	}
	if (sum2 != sum1)
	{
		return 0;
	}

	// 对角线2检查
	sum2 = 0;
	for (int i = 0; i < n; i++)
	{
		sum2 += p[i*n + (n-i-1)];
	}
	if (sum2 != sum1)
	{
		return 0;
	}

	return 1;

}

/***********************************************************************************
KMP模式匹配算法：
	当发生失配时，期望根据模式中字符和失配在模式中出现的位置，来确定继续进行搜索的位置。
	失配函数：
		令p=p0p1....pn是一个模式，则其失配函数f定义为：
		f(j) = i为满足i<j且使得p0p1...pi=pj-ipj-i+1...pj的最大整数 如果i>= 0， 否则
			   -1 
	失配函数的另一种表达形式：
		f(j) = -1         如果j=0
			   fm(j-1)+1  其中m是满足登上pfk(j-1)+1=pj的最小整数k
			   -1		  如果没有满足上式的k值
***********************************************************************************/
static void str_fail(char *pat, char* failure)
{
	int n = strlen(pat);

	failure[0] = -1;
	for (int j = 1; j < n; j++)
	{
		int i = failure[j - 1];
		while (pat[j] != pat[i + 1] && i >= 0)
		{
			i = failure[i];
		}
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else
			failure[j] = -1;
	}
}

int str_pmatch(char *string, char *pat)
{
	if (NULL == string || NULL == pat)
	{
		return -1;
	}

	int lens = strlen(string);
	int lenp = strlen(pat);

	char *failure = (char*)malloc(lenp);
	str_fail(pat, failure);

	int i = 0, j = 0;
	while (i < lens && j < lenp)
	{
		if (string[i] == pat[j])
		{
			i++;
			j++;
		}
		else if (j == 0)
		{
			i++;
		}
		else
		{
			j = failure[j - 1] + 1;
		}
	}

	free(failure);

	return ((j == lenp) ? (i - lenp) : -1);

}