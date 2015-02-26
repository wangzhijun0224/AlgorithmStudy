#include "DS_charpter03_test.h"

#include "DS_charpter03.h"

void stack_test(void)
{
	stack *stk = stack_open(10, sizeof(int));
	int item;

	if (NULL == stk) return;

	CU_ASSERT_EQUAL(1, stk->empty(stk));

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, stk->add(stk, &i));
	}
	
	CU_ASSERT_EQUAL(1, stk->full(stk));

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, stk->del(stk, &item));
		CU_ASSERT_EQUAL(9-i, item);
	}
	CU_ASSERT_EQUAL(1, stk->empty(stk));

	stack_close(stk);
}

void queue_test(void)
{
	queue *q = queue_open(10);
	queue_elements item;

	if (NULL == q) return;

	CU_ASSERT_EQUAL(1, q->empty(q));

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, q->add(q, i));
	}

	CU_ASSERT_EQUAL(1, q->full(q));

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, q->del(q, &item));
		CU_ASSERT_EQUAL(i, item);
	}
	CU_ASSERT_EQUAL(1, q->empty(q));

	queue_close(q);
}

static void maze_search_test1(void)
{
	unsigned char maze[9][6] = {
		{ 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 0 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 0 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0 }
	};

	unsigned int path[] = {0,0,1,0,2,0,3,0,4,0,5,1,4,2,3,2,2,2,1,2,0,3,1,4,
		2,4,3,4,4,4,5,5,4,6,3,6,2,6,1,6,0,7,1,8,2,8,3,8,4,8,5,8};
	unsigned int path2[9 * 6];

	int result = maze_search((unsigned char *)maze, 9, 6, 0, 0, 5, 8, path2);
	CU_ASSERT_EQUAL(result, sizeof(path) / sizeof(path[0]));
	CU_ASSERT_PTR_DATA_EQUAL(path, path2, sizeof(path)/sizeof(path[0]));

	result = maze_search_check((unsigned char *)maze, 9, 6, 0, 0, 5, 8, path2, result);
	CU_ASSERT_EQUAL(result, 1);
}

static void maze_search_test2(void)
{
	unsigned char maze[11][15] = {
		{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },
	};
	unsigned int path2[11 * 15];

	int result = maze_search((unsigned char *)maze, 11, 15, 0, 0, 14, 10, path2);
	CU_ASSERT_LARGER(result, 4);

	result = maze_search_check((unsigned char *)maze, 11, 15, 0, 0, 14, 10, path2, result);
	CU_ASSERT_EQUAL(result, 1);
}

static void postfix_expr_eval_test0(void)
{
	char postfix_expr[100] = { 0 };
	int value;

	strcpy_s(postfix_expr, 100, "2 3 4 * + ");
	int result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 14);

	strcpy_s(postfix_expr, 100, "1 2 + 7 * ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 21);

	strcpy_s(postfix_expr, 100, "6 2 / 3 - 4 2 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 8);

	strcpy_s(postfix_expr, 100, "12 30 40 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 1212);

	strcpy_s(postfix_expr, 100, "1 30 40 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 1201);

	strcpy_s(postfix_expr, 100, "12 3 40 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 132);

	strcpy_s(postfix_expr, 100, "12 30 4 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 132);

	strcpy_s(postfix_expr, 100, "12 3 4 * + ");
	result = postfix_expr_eval(postfix_expr, &value);
	CU_ASSERT_EQUAL(result, 1);
	CU_ASSERT_EQUAL(value, 24);

}

static void middlefix_to_postfix_test0(void)
{
	char middlefix_expr[100] = {0};
	char postfix_expr[100] = { 0 };

	strcpy_s(middlefix_expr, 100, "2 + 3 * 4 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "2 3 4 * + ", sizeof("2 3 4 * + "));

	strcpy_s(middlefix_expr, 100, "( 1 + 2 ) * 7 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "1 2 + 7 * ", sizeof("1 2 + 7 * "));

	strcpy_s(middlefix_expr, 100, "1 + ( 2  *  7 ) ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "1 2 7 * + ", sizeof("1 2 7 * + "));
	
	strcpy_s(middlefix_expr, 100, "6 / 2 - 3 + 4 * 2 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "6 2 / 3 - 4 2 * + ", sizeof("6 2 / 3 - 4 2 * + "));

	strcpy_s(middlefix_expr, 100, "12 + 30 * 40 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "12 30 40 * + ", sizeof("12 30 40 * + "));

	strcpy_s(middlefix_expr, 100, "1 + 30 * 40 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "1 30 40 * + ", sizeof("1 30 40 * + "));

	strcpy_s(middlefix_expr, 100, "12 + 3 * 40 ");
	middlefix_to_postfix(middlefix_expr, postfix_expr);
	CU_ASSERT_PTR_DATA_EQUAL(postfix_expr, "12 3 40 * + ", sizeof("12 3 40 * + "));
}
/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter03[] = {
	{ "stack_test", stack_test },
	{ "queue_test", queue_test },
	{ "maze_search_test1", maze_search_test1 },
	{ "maze_search_test2", maze_search_test2 },
	{ "postfix_expr_eval_test0", postfix_expr_eval_test0 },
	{ "middlefix_to_postfix_test0", middlefix_to_postfix_test0 },
	CU_TEST_INFO_NULL,
};
