#include "DS_charpter02_test.h"

#include "DS_charpter02.h"

static void poly1_sum_test0(void)
{
	polynomial1 poly;

	poly.degree = 2;
	poly.coef[0] = 1;
	poly.coef[1] = 0;
	poly.coef[2] = 0;

	CU_ASSERT_DOUBLE_EQUAL(polynomial1_sum(&poly, 2.0), 4.0, 0.0001);
}

static void poly1_sum_test1(void)
{
	polynomial1 poly;

	poly.degree = 3;
	poly.coef[0] = 2;
	poly.coef[1] = 1;
	poly.coef[2] = 3;
	poly.coef[3] = 4;

	CU_ASSERT_DOUBLE_EQUAL(polynomial1_sum(&poly, 0.0), 4.0, 0.0001);
}

static void polynomial1_add_test0(void)
{
	polynomial1 poly1, poly2, poly3, poly4;

	poly1.degree = 2;
	poly1.coef[0] = 1;
	poly1.coef[1] = 0;
	poly1.coef[2] = 0;

	poly2.degree = 3;
	poly2.coef[0] = 2;
	poly2.coef[1] = 1;
	poly2.coef[2] = 3;
	poly2.coef[3] = 4;

	polynomial1_add(&poly1, &poly2, &poly3);

	poly4.degree = 3;
	poly4.coef[0] = 3;
	poly4.coef[1] = 1;
	poly4.coef[2] = 3;
	poly4.coef[3] = 4;

	int len = (int)&poly4.coef[4] - (int)&poly4;

	CU_ASSERT_PTR_DATA_EQUAL(&poly3, &poly4, len); // 可能会出问题,,浮点数比较
}

static void polynomial2_add_test0(void)
{

	polyitem item1, item2[4], item3[4], item4[4];
	polynomial2 poly1, poly2, poly3, poly4;

	item1.coef = 1, item1.expon = 0;
	poly1.count = 1, poly1.poly = &item1;

	item2[0].coef = 2, item2[0].expon = 0;
	item2[1].coef = 1, item2[1].expon = 1;
	item2[2].coef = 3, item2[2].expon = 2;
	item2[3].coef = 4, item2[3].expon = 3;
	poly2.count = 4, poly2.poly = item2;

	poly3.poly = item3;
	polynomial2_add(&poly1, &poly2, &poly3);

	item4[0].coef = 3, item4[0].expon = 0;
	item4[1].coef = 1, item4[1].expon = 1;
	item4[2].coef = 3, item4[2].expon = 2;
	item4[3].coef = 4, item4[3].expon = 3;
	poly4.count = 4, poly4.poly = item4;

	CU_ASSERT_EQUAL(poly3.count, poly4.count);
	CU_ASSERT_PTR_DATA_EQUAL(poly3.poly, poly4.poly, poly4.count*sizeof(polyitem)); // 可能会出问题,,有浮点数比较
}

/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter02[] = {
	{ "poly1_sum_test0", poly1_sum_test0 },
	{ "poly1_sum_test1", poly1_sum_test1 },
	{ "polynomial1_add_test0", polynomial1_add_test0 },
	{ "polynomial2_add_test0", polynomial2_add_test0 },
	CU_TEST_INFO_NULL,
};