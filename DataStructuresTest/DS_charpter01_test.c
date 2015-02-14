#include "DS_charpter01_test.h"

#include "DS_charpter01.h"

/***********************************************************************************
	select_sort() ≤‚ ‘
***********************************************************************************/
void select_sort_test0(void)
{
#define LIST_LEN	10

	int list[LIST_LEN] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int sorted_list[LIST_LEN] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	select_sort(list, LIST_LEN);

	CU_ASSERT_PTR_DATA_EQUAL(list, sorted_list, LIST_LEN*sizeof(int));
}

void select_sort_test1(void)
{
#define LIST_LEN	10

	int list[LIST_LEN] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int sorted_list[LIST_LEN] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	select_sort(list, LIST_LEN);

	CU_ASSERT_PTR_DATA_EQUAL(list, sorted_list, LIST_LEN*sizeof(int));
}

void select_sort_test2(void)
{
#define LIST_LEN	10

	int list[LIST_LEN] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 3};
	int sorted_list[LIST_LEN] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3};

	select_sort(list, LIST_LEN);

	CU_ASSERT_PTR_DATA_EQUAL(list, sorted_list, LIST_LEN*sizeof(int));
}

/***********************************************************************************
binary_search() ≤‚ ‘
***********************************************************************************/
void binary_search_test(void)
{
	int list[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	CU_ASSERT_EQUAL(binary_search(list, list[0], 0, 9), 0);

	CU_ASSERT_EQUAL(binary_search(list, list[9], 0, 9), 9);

	CU_ASSERT_EQUAL(binary_search(list, list[4], 0, 9), 4);

	CU_ASSERT_EQUAL(binary_search(list, 10, 0, 9), -1);
}

/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter01[] = {
	{ "select_sort_test0", select_sort_test0 },
	{ "select_sort_test1", select_sort_test1 },
	{ "select_sort_test2", select_sort_test2 },
	{ "binary_search_test", binary_search_test },
	CU_TEST_INFO_NULL,
};