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
	Horner���������ʽ��ֵ
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
	����ʽ���
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
����ʽ���
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
	ϡ������ת��:(������: O(columns*elements))
	��ϡ�����aת�õ�b��
***********************************************************************************/
void sparematrix_transpose(sparematrixitem a[], sparematrixitem b[])
{
	int n, i, j, currentb;
	n = a[0].value;			// Ԫ������

	b[0].row = a[0].col;	// b������ = a������	
	b[0].col = a[0].row;	// b������ = a������
	b[0].value = n;	

	if (n <= 0)	return;
	
	currentb = 1;
	for (i = 0; i < a[0].col; i++)	// iΪ�����к�
	{
		// �ҳ���ǰ������Ԫ��
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
ϡ�����Ŀ���ת��:(������: O(columns+elements))
	����ȷ��ԭ������ÿ��Ԫ�صĸ���,Ҳ��ת�þ�����ÿ��Ԫ�صĸ���;
	Ȼ��õ�ת�þ���ÿ�е���ʼλ��
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

	// ͳ��ԭ����ÿ��Ԫ�صĸ�����Ҳ��ת�þ���ÿ��Ԫ�صĸ���
	for (i = 1; i <= num_terms; i++)
	{
		row_terms[a[i].row]++;
	}

	// ����ת�þ���ÿ��Ԫ�ص���ʼλ��
	for (i = 1; i < num_cols; i++)
	{
		start_pos[i] = start_pos[i - 1] + row_terms[i - 1];
	}
	
	// ����ת�þ���
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
����˷���
	�Ƚ�bת��,�ٶ���ʽ���	
***********************************************************************************/
void sparematrix_mult(sparematrixitem a[], sparematrixitem b[], sparematrixitem d[])
{
	int count_a = a[0].value, count_b = b[0].value;
	int col, row;
	int indexd = 1;
	int col_begin = 1; // ��i�еĿ�ʼ����
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

	// �����ڱ������ڼ򻯱ȽϹ���
	a[count_a + 1].col = a[0].col;	// ע��,�˴�Ҫ��a���ٱ�ʵ�ʵľ��������1
	trans_b[count_b+1].col = b[0].row;

	col = a[1].col;
	for (int i = 1; i <= count_a; )	// ��ѭ��
	{
		row = trans_b[1].col;	// ת�þ�����к�,��ת��ǰ���к�
		for (int j = 1; j <= count_b+1;)	// ע��,ÿ�����һ��Ԫ��ʱ,j�ܵ���count_b+1
		{
			if (a[i].col != col)	// ��ʾ���˵�i+1��
			{
				storesum(d, &indexd, col, row, &sum);
				i = col_begin;
				for (; trans_b[j].col == row; j++)	// ע���ڱ��������
					;
				row = trans_b[j].col;	// ��i����һ��Ԫ��
			}
			else if (trans_b[j].col != row)	// ��i����һ��Ԫ��
			{
				storesum(d, &indexd, col, row, &sum);
				i = col_begin;
				for (; trans_b[j].col == row; j++) // ע���ڱ��������
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

		// ת����һ��
		for (; a[i].col == col; i++) // ע���ڱ��������
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