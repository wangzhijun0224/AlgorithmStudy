#include "DS_charpter02.h"

#include <stdio.h>

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

}