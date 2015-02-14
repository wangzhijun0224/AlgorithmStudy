#include "DS_charpter02_test.h"

#include "DS_charpter02.h"

void poly1_sum_test0(void)
{
	polynomial1 poly;

	poly.degree = 2;
	poly.coef[0] = 1;
	poly.coef[1] = 0;
	poly.coef[2] = 0;

	CU_ASSERT_DOUBLE_EQUAL(polynomial1_sum(&poly, 2.0), 4.0, 0.0001);
}

void poly1_sum_test1(void)
{
	polynomial1 poly;

	poly.degree = 3;
	poly.coef[0] = 2;
	poly.coef[1] = 1;
	poly.coef[2] = 3;
	poly.coef[3] = 4;

	CU_ASSERT_DOUBLE_EQUAL(polynomial1_sum(&poly, 0.0), 4.0, 0.0001);
}


/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter02[] = {
	{ "poly1_sum_test0", poly1_sum_test0 },
	{ "poly1_sum_test1", poly1_sum_test1 },
	CU_TEST_INFO_NULL,
};