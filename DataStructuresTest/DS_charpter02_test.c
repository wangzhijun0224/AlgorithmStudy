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

static void sparematrix_set_test(void)
{
	sparematrixitem a[9];
	int col = 6, row = 6;

	sparematrix_set(a, col, row);

	CU_ASSERT_EQUAL(a[0].col, col);
	CU_ASSERT_EQUAL(a[0].row, row);
	CU_ASSERT_EQUAL(a[0].value, 0);
}

static void sparematrix_additem_test(void)
{
	sparematrixitem a[9];
	sparematrixitem b[9] = { 
		{ 6, 6, 8 },
		{ 0, 0, 15 },
		{ 0, 3, 22 },
		{ 0, 5, -15 },
		{ 1, 1, 11 },
		{ 1, 2, 3 },
		{ 2, 3, -6 },
		{ 4, 0, 91 },
		{ 5, 2, 28 },
	};

	sparematrix_set(a, 6, 6);			// 6行6列
	sparematrix_additem(a, 0, 0, 15);
	sparematrix_additem(a, 0, 3, 22);
	sparematrix_additem(a, 0, 5, -15);
	sparematrix_additem(a, 1, 1, 11);
	sparematrix_additem(a, 1, 2, 3);
	sparematrix_additem(a, 2, 3, -6);
	sparematrix_additem(a, 4, 0, 91);
	sparematrix_additem(a, 5, 2, 28);
	
	CU_ASSERT_PTR_DATA_EQUAL(a, b, 8*sizeof(sparematrixitem));
}

static void sparematrix_transpose_test(void)
{
	
	sparematrixitem a[9] = {
		{ 6, 6, 8 },
		{ 0, 0, 15 },
		{ 0, 3, 22 },
		{ 0, 5, -15 },
		{ 1, 1, 11 },
		{ 1, 2, 3 },
		{ 2, 3, -6 },
		{ 4, 0, 91 },
		{ 5, 2, 28 },
	};

	sparematrixitem b[9] = {
		{ 6, 6, 8 },
		{ 0, 0, 15 },
		{ 0, 4, 91 },
		{ 1, 1, 11 },
		{ 2, 1, 3 },
		{ 2, 5, 28 },
		{ 3, 0, 22 },
		{ 3, 2, -6 },
		{ 5, 0, -15 },
	};

	sparematrixitem c[9];

	sparematrix_transpose(a, c);

	CU_ASSERT_PTR_DATA_EQUAL(b, c, 8 * sizeof(sparematrixitem));
}

static void sparematrix_fast_transpose_test(void)
{

	sparematrixitem a[9] = {
		{ 6, 6, 8 },
		{ 0, 0, 15 },
		{ 0, 3, 22 },
		{ 0, 5, -15 },
		{ 1, 1, 11 },
		{ 1, 2, 3 },
		{ 2, 3, -6 },
		{ 4, 0, 91 },
		{ 5, 2, 28 },
	};

	sparematrixitem b[9] = {
		{ 6, 6, 8 },
		{ 0, 0, 15 },
		{ 0, 4, 91 },
		{ 1, 1, 11 },
		{ 2, 1, 3 },
		{ 2, 5, 28 },
		{ 3, 0, 22 },
		{ 3, 2, -6 },
		{ 5, 0, -15 },
	};

	sparematrixitem c[9];

	sparematrix_transpose(a, c);

	CU_ASSERT_PTR_DATA_EQUAL(b, c, 8 * sizeof(sparematrixitem));
}

static void sparematrix_mult_test(void)
{
	// 注意,a必须至少比实际要求的多一项
	sparematrixitem a[5] = {
		{3, 3, 3},
		{0, 0, 1},
		{1, 0, 1},
		{2, 0, 1}
	};

	sparematrixitem b[4] = {
		{ 3, 3, 3 },
		{ 0, 0, 1 },
		{ 0, 1, 1 },
		{ 0, 2, 1 }
	};

	sparematrixitem c[10] = {
		{ 3, 3, 9 },
		{ 0, 0, 1 },
		{ 0, 1, 1 },
		{ 0, 2, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 2, 1 },
		{ 2, 0, 1 },
		{ 2, 1, 1 },
		{ 2, 2, 1 },
	};

	sparematrixitem d[10];

	sparematrix_mult(a, b, d);

	CU_ASSERT_PTR_DATA_EQUAL(c, d, sizeof(c));
}

static void magic_square_check_test(void)
{
	int a[5][5] = {
		{15, 8, 1, 24, 17},
		{16, 14, 7, 5, 23},
		{22, 20, 13, 6, 4},
		{3, 21, 19, 12, 10},
		{9, 2, 25, 18, 11}
	};

	CU_ASSERT_EQUAL(1, magic_square_check((int*)a, 5));
}

static void magic_square_create_test0(void)
{
	int b[5][5], a[5][5] = {
		{ 15, 8, 1, 24, 17 },
		{ 16, 14, 7, 5, 23 },
		{ 22, 20, 13, 6, 4 },
		{ 3, 21, 19, 12, 10 },
		{ 9, 2, 25, 18, 11 }
	};

	magic_square_create((int *)b, 5);

	CU_ASSERT_PTR_DATA_EQUAL((void *)a, (void *)b, 5*5*sizeof(int));

	CU_ASSERT_EQUAL(1, magic_square_check((int*)b, 5));

}

static void magic_square_create_test1(void)
{
	int a[15][15];

	magic_square_create((int *)a, 15);

	CU_ASSERT_EQUAL(1, magic_square_check((int*)a, 15));

}

static void str_pmatch_test0(void)
{
	char *str = "ababbaabaa";
	char *pat = "aab";

	CU_ASSERT_EQUAL(5, str_pmatch(str, pat));
}

static void str_pmatch_test1(void)
{
	char *str = "ababbaabaa";
	char *pat = "abab";

	CU_ASSERT_EQUAL(0, str_pmatch(str, pat));
}

static void str_pmatch_test2(void)
{
	char *str = "ababbaabaa";
	char *pat = "abaa";

	CU_ASSERT_EQUAL(6, str_pmatch(str, pat));
}

static void str_pmatch_test3(void)
{
	char *str = "ababbaabaa";
	char *pat = "abc";

	CU_ASSERT_EQUAL(-1, str_pmatch(str, pat));
}
/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter02[] = {
	{ "poly1_sum_test0", poly1_sum_test0 },
	{ "poly1_sum_test1", poly1_sum_test1 },
	{ "polynomial1_add_test0", polynomial1_add_test0 },
	{ "polynomial2_add_test0", polynomial2_add_test0 },
	{ "sparematrix_set_test", sparematrix_set_test },
	{ "sparematrix_additem_test", sparematrix_additem_test },
	{ "sparematrix_transpose_test", sparematrix_transpose_test },
	{ "sparematrix_fast_transpose_test", sparematrix_fast_transpose_test },
	{ "sparematrix_mult_test", sparematrix_mult_test },
	{ "magic_square_check_test", magic_square_check_test },
	{ "magic_square_create_test0", magic_square_create_test0 },
	{ "magic_square_create_test1", magic_square_create_test1 },
	{ "str_pmatch_test0", str_pmatch_test0 },
	{ "str_pmatch_test1", str_pmatch_test1 },
	{ "str_pmatch_test2", str_pmatch_test2 },
	{ "str_pmatch_test3", str_pmatch_test3 },
	CU_TEST_INFO_NULL,
};