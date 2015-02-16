#include "AL_charpter01_test.h"

#include "AL_charpter01.h"

static void connectivity_quickfind_test(void)
{
	pair pairs[] = {
		{ 3, 4 }, { 4, 9 }, { 8, 0 }, { 2, 3 },
		{ 5, 6 }, { 2, 9 }, { 5, 9 }, { 7, 3 },
		{ 4, 8 }, { 5, 6 }, { 0, 2 }, { 6, 1 },
		{ 5, 8 },
	};

	int m = sizeof(pairs) / sizeof(pairs[0]);
	int n = 10;
	int id[10];
	int rlt[100];
	int hope[18] = {3, 4, 4, 9, 8, 0, 2, 3, 5, 6, 5, 9, 7, 3, 4, 8, 6, 1};

	int count = connectivity_quickfind(pairs, m, id, n, rlt);

	CU_ASSERT_EQUAL(count, 18);
	CU_ASSERT_PTR_DATA_EQUAL(hope, rlt, 18*sizeof(int));
}

static void connectivity_quickunion_test(void)
{
	pair pairs[] = {
		{ 3, 4 }, { 4, 9 }, { 8, 0 }, { 2, 3 },
		{ 5, 6 }, { 2, 9 }, { 5, 9 }, { 7, 3 },
		{ 4, 8 }, { 5, 6 }, { 0, 2 }, { 6, 1 },
		{ 5, 8 },
	};

	int m = sizeof(pairs) / sizeof(pairs[0]);
	int n = 10;
	int id[10];
	int rlt[100];
	int hope[18] = {3, 4, 4, 9, 8, 0, 2, 3, 5, 6, 5, 9, 7, 3, 4, 8, 6, 1};

	int count = connectivity_quickunion(pairs, m, id, n, rlt);

	CU_ASSERT_EQUAL(count, 18);
	CU_ASSERT_PTR_DATA_EQUAL(hope, rlt, 18*sizeof(int));
}

static void connectivity_weighted_quickunion_test(void)
{
	pair pairs[] = {
		{ 3, 4 }, { 4, 9 }, { 8, 0 }, { 2, 3 },
		{ 5, 6 }, { 2, 9 }, { 5, 9 }, { 7, 3 },
		{ 4, 8 }, { 5, 6 }, { 0, 2 }, { 6, 1 },
		{ 5, 8 },
	};

	int m = sizeof(pairs) / sizeof(pairs[0]);
	int n = 10;
	int id[10];
	int rlt[100];
	int hope[18] = {3, 4, 4, 9, 8, 0, 2, 3, 5, 6, 5, 9, 7, 3, 4, 8, 6, 1};

	int count = connectivity_weighted_quickunion(pairs, m, id, n, rlt);

	CU_ASSERT_EQUAL(count, 18);
	CU_ASSERT_PTR_DATA_EQUAL(hope, rlt, 18*sizeof(int));
}

static void connectivity_pathcompression_weighted_quickunion_test(void)
{
	pair pairs[] = {
		{ 3, 4 }, { 4, 9 }, { 8, 0 }, { 2, 3 },
		{ 5, 6 }, { 2, 9 }, { 5, 9 }, { 7, 3 },
		{ 4, 8 }, { 5, 6 }, { 0, 2 }, { 6, 1 },
		{ 5, 8 },
	};

	int m = sizeof(pairs) / sizeof(pairs[0]);
	int n = 10;
	int id[10];
	int rlt[100];
	int hope[18] = {3, 4, 4, 9, 8, 0, 2, 3, 5, 6, 5, 9, 7, 3, 4, 8, 6, 1};

	int count = connectivity_pathcompression_weighted_quickunion(pairs, m, id, n, rlt);

	CU_ASSERT_EQUAL(count, 18);
	CU_ASSERT_PTR_DATA_EQUAL(hope, rlt, 18*sizeof(int));
}

/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_algorithm_charpter01[] = {
	{ "connectivity_quickfind_test", connectivity_quickfind_test },
	{ "connectivity_quickunion_test", connectivity_quickunion_test },
	{ "connectivity_weighted_quickunion_test", connectivity_weighted_quickunion_test },
	{ "connectivity_pathcompression_weighted_quickunion_test", connectivity_pathcompression_weighted_quickunion_test },
	CU_TEST_INFO_NULL,
};