#include "DS_charpter04_test.h"

#include "DS_charpter04.h"

static void stack_slist_test(void)
{
	stack_slist stk = stack_slist_open(sizeof(int));
	int item;

	if (NULL == stk) return;

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, stack_slist_insert(stk, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, stack_slist_del(stk, &item));
		CU_ASSERT_EQUAL(9 - i, item);
	}

	CU_ASSERT_EQUAL(0, stack_slist_del(stk, &item));
	CU_ASSERT_EQUAL(0, stack_slist_del(stk, &item));

	stack_slist_close(stk);
}

static void queue_slist_test(void)
{
	queue_slist q = queue_slist_open(sizeof(int));
	int item;

	if (NULL == q) return;

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, queue_slist_insert(q, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, queue_slist_del(q, &item));
		CU_ASSERT_EQUAL(i, item);
	}

	CU_ASSERT_EQUAL(0, queue_slist_del(q, &item));
	CU_ASSERT_EQUAL(0, queue_slist_del(q, &item));

	item = 20;
	CU_ASSERT_EQUAL(1, queue_slist_insert(q, &item));
	CU_ASSERT_EQUAL(1, queue_slist_del(q, &item));
	CU_ASSERT_EQUAL(20, item);
	item = 30;
	CU_ASSERT_EQUAL(1, queue_slist_insert(q, &item));
	CU_ASSERT_EQUAL(1, queue_slist_del(q, &item));
	CU_ASSERT_EQUAL(30, item);

	queue_slist_close(q);
}

static void dequeue_dlist_test0(void)
{
	dequeue_dlist dq = dequeue_dlist_open(sizeof(int));
	int item;

	if (NULL == dq) return;

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_insert(dq, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_pop(dq, &item));
		CU_ASSERT_EQUAL(9 - i, item);
	}

	CU_ASSERT_EQUAL(0, dequeue_dlist_pop(dq, &item));
	CU_ASSERT_EQUAL(0, dequeue_dlist_pop(dq, &item));

	dequeue_dlist_close(dq);
}
static void dequeue_dlist_test1(void)
{
	dequeue_dlist dq = dequeue_dlist_open(sizeof(int));
	int item;

	if (NULL == dq) return;

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_append(dq, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_del(dq, &item));
		CU_ASSERT_EQUAL(9 - i, item);
	}

	CU_ASSERT_EQUAL(0, dequeue_dlist_del(dq, &item));
	CU_ASSERT_EQUAL(0, dequeue_dlist_del(dq, &item));

	dequeue_dlist_close(dq);
}

static void dequeue_dlist_test2(void)
{
	dequeue_dlist dq = dequeue_dlist_open(sizeof(int));
	int item;

	if (NULL == dq) return;

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_insert(dq, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_del(dq, &item));
		CU_ASSERT_EQUAL(i, item);
	}

	CU_ASSERT_EQUAL(0, dequeue_dlist_del(dq, &item));
	CU_ASSERT_EQUAL(0, dequeue_dlist_del(dq, &item));

	dequeue_dlist_close(dq);
}

static void dequeue_dlist_test3(void)
{
	dequeue_dlist dq = dequeue_dlist_open(sizeof(int));
	int item;

	if (NULL == dq) return;
	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_append(dq, &i));
	}

	for (int i = 0; i < 10; ++i)
	{
		CU_ASSERT_EQUAL(1, dequeue_dlist_pop(dq, &item));
		CU_ASSERT_EQUAL(i, item);
	}

	CU_ASSERT_EQUAL(0, dequeue_dlist_pop(dq, &item));
	CU_ASSERT_EQUAL(0, dequeue_dlist_pop(dq, &item));

	dequeue_dlist_close(dq);
}
/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter04[] = {
	{ "stack_slist_test", stack_slist_test },
	{ "queue_slist_test", queue_slist_test },
	{ "dequeue_dlist_test0", dequeue_dlist_test0 },
	{ "dequeue_dlist_test1", dequeue_dlist_test1 },
	{ "dequeue_dlist_test2", dequeue_dlist_test2 },
	{ "dequeue_dlist_test3", dequeue_dlist_test3 },
	CU_TEST_INFO_NULL,
};