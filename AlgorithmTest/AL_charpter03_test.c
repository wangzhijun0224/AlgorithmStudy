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

static void near_point_test(void)
{
	my_printf("\n");
	double d;
	for (int i = 10; i <= 10000; i *= 10)
	{
		d = 0.3;
		my_printf("n: %8d, d: %f, count: %d\n", i, d, near_point(i, d));
		d = 0.6;
		my_printf("n: %8d, d: %f, count: %d\n", i, d, near_point(i, d));
		d = 0.9;
		my_printf("n: %8d, d: %f, count: %d\n", i, d, near_point(i, d));
	}
	my_printf("\n");
}

/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_algorithm_charpter03[] = {
	{ "loga_test", loga_test },
	//{ "prime_test", prime_test },
	{ "throw_coin_test", throw_coin_test },
	{ "near_point_test", near_point_test },
	CU_TEST_INFO_NULL,
};
