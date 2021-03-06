#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "CUnit.h"

#include "AL_charpter01_test.h"
#include "AL_charpter03_test.h"

static CU_SuiteInfo suites[] = {
	{ "suit_datasture01", NULL, NULL, tests_algorithm_charpter01 },
	{ "suit_datasture02", NULL, NULL, tests_algorithm_charpter03 },
	CU_SUITE_INFO_NULL,
};
void AddAlgorithmTests(void)
{
	assert(NULL != CU_get_registry());
	assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}