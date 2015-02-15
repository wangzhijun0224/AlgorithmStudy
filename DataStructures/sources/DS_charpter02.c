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