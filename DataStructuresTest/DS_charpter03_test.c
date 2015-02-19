#include "DS_charpter03_test.h"

#include "DS_charpter03.h"

void stack_test(void)
{
	stack *stk = stack_open(10);
	stack_elements item;

	if (NULL == stk) return;

	CU_ASSERT_EQUAL(1, stk->empty(stk));

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, stk->add(stk, i));
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

/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter03[] = {
	{ "stack_test", stack_test },
	{ "queue_test", queue_test },
	CU_TEST_INFO_NULL,
};