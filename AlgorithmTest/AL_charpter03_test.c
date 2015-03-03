#include "AL_charpter03_test.h"

#include "AL_charpter03.h"

#include "os_private.h"

#include <stdlib.h>
#include <assert.h>

static void loga_test(void)
{
	CU_ASSERT_EQUAL(1, loga(1, 10));
	CU_ASSERT_EQUAL(1, loga(5, 10));
	CU_ASSERT_EQUAL(2, loga(10, 10));
	CU_ASSERT_EQUAL(2, loga(30, 10));
	CU_ASSERT_EQUAL(2, loga(50, 10));
	CU_ASSERT_EQUAL(3, loga(100, 10));
	CU_ASSERT_EQUAL(4, loga(1000, 10));
	CU_ASSERT_EQUAL(4, loga(2000, 10));

	CU_ASSERT_EQUAL(1, loga(1, 2));
	CU_ASSERT_EQUAL(2, loga(2, 2));
	CU_ASSERT_EQUAL(2, loga(3, 2));
	CU_ASSERT_EQUAL(4, loga(8, 2));
	CU_ASSERT_EQUAL(10, loga(1023, 2));
	CU_ASSERT_EQUAL(11, loga(1024, 2));
	CU_ASSERT_EQUAL(11, loga(1025, 2));
}

static void prime_test(void)
{
	int rlt1, rlt2;
	int *prime, *prime2;
	prime = (int *)malloc(8192 * 1024 * sizeof(int));
	prime2 = (int *)malloc(8192 * 1024 * sizeof(int));
	assert(NULL != prime);
	assert(NULL != prime2);

	rlt1 = get_prime(100, prime);
	rlt2 = get_prime(100, prime2);

	CU_ASSERT_EQUAL(rlt1, rlt2);
	CU_ASSERT_PTR_DATA_EQUAL(prime, prime2, rlt1*sizeof(int));

	int n[10], i;
	for (i = 1, n[0] = 20000; i < 10; n[i] = n[i -1] * 2, i++)
		;

	U64 curtime;
	my_printf("\n");
	for (i = 0; i < 10; i++)
	{
		curtime = get_systime_ms();
		rlt1 = get_prime(n[i], prime);
		my_printf("\tn:%8d, prime count:%6d, get_prime()  consume time: %8ld\n", n[i], rlt1, get_systime_ms() - curtime);

		curtime = get_systime_ms();
		rlt2 = get_prime2(n[i], prime2);
		my_printf("\tn:%8d, prime count:%6d, get_prime2() consume time: %8ld\n", n[i], rlt2, get_systime_ms() - curtime);
		my_printf("\n");

		CU_ASSERT_EQUAL(rlt1, rlt2);
		CU_ASSERT_PTR_DATA_EQUAL(prime, prime2, rlt1*sizeof(int));
	}

	free(prime);
	free(prime2);

}

static void throw_coin_test(void)
{
	int n = 32;
	int rlt[33];

	throw_coin(1000, 32, rlt);

	my_printf("\n");
	for (int i = 0; i <= 32; i++)
	{
		my_printf("%2d ", i);
		for (int j = 0; j < rlt[i]; j += 3)
		{
			my_printf("*");
		}
		my_printf("\n");
	}
	my_printf("\n");
}

static void josephus_circle_test(void)
{
	CU_ASSERT_EQUAL(josephus_circle(4, 2), josephus_circle2(4, 2));
	CU_ASSERT_EQUAL(josephus_circle(9, 5), josephus_circle2(9, 5));
	CU_ASSERT_EQUAL(josephus_circle(9, 1), josephus_circle2(9, 1));
}

static void list_reverse_test(void)
{
	int n = 100, i;
	link head = (link)malloc(n*sizeof(*head));
	assert(NULL != head);

	for (i = 0; i < 100; i++)
	{
		head[i].item = i;
		head[i].next = &head[i + 1];
	}
	head[n - 1].next = NULL;

	link reverse_head = list_reverse(head);
	for (i = 99; reverse_head != NULL; reverse_head = reverse_head->next, i--)
	{
		CU_ASSERT_EQUAL(i, reverse_head->item);
	}

	free(head);

}

// ’˝»∑–‘≤‚ ‘
static void near_point_test0(void)
{
	int cnt1, cnt2;

	for (int i = 10; i <= 1000; i *= 10)
	{
		double *randnum = (double *)malloc(2 * i*sizeof(double));
		assert(randnum != NULL);

		for (int j = 0; j < 2 * i; j++)
		{
			randnum[j] = 1.0*rand() / RAND_MAX;
		}

		double d = 0.1;

		for (int j = 0; j < 3; j++, d = d*0.1)
		{
			cnt1 = near_point(i, d, randnum);
			cnt2 = near_point2(i, d, randnum);
			CU_ASSERT_EQUAL(cnt1, cnt2);
		}

		free(randnum);
	}
}

static void near_point_test1(void)
{
	U64 curtime;
	int cnt;

	my_printf("\n");

	for (int i = 10; i <= 1000000; i *= 10)
	{
		double *randnum = (double *)malloc(2 * i*sizeof(double));
		assert(randnum != NULL);

		for (int j = 0; j < 2 * i; j++)
		{
			randnum[j] = 1.0*rand() / RAND_MAX;
		}


		double d = 0.0001;

		//for (int j = 0; j < 3; j++, d = d*0.1)
		{
			my_printf("n:%d, d:%1.5f\n", i, d);
			curtime = get_systime_ms();
			cnt = near_point(i, d, randnum);
			my_printf("near_point: n: %d, d: %f, count: %d, time: %ld\n", i, d, cnt, get_systime_ms() - curtime);

#if 0
			curtime = get_systime_ms();
			cnt = near_point2(i, d, randnum);
			my_printf("near_point2: n: %d, d: %f, count: %d, time: %ld\n", i, d, cnt, get_systime_ms() - curtime);
			my_printf("\n");
#endif
		}

		free(randnum);
	}
	my_printf("\n");
}
/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_algorithm_charpter03[] = {
	{ "loga_test", loga_test },
	//{ "prime_test", prime_test },
	//{ "throw_coin_test", throw_coin_test },
	{ "near_point_test0", near_point_test0 },
	{ "near_point_test1", near_point_test1 },
	{ "josephus_circle_test", josephus_circle_test },
	{ "list_reverse_test", list_reverse_test },
	CU_TEST_INFO_NULL,
};
