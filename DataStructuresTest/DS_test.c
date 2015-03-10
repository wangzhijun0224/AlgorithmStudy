#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "CUnit.h"

#include "DS_charpter01_test.h"
#include "DS_charpter02_test.h"
#include "DS_charpter03_test.h"
#include "DS_charpter04_test.h"
#include "DS_charpter05_test.h"

static CU_SuiteInfo suites[] = {
	{ "suit_datasture01", NULL, NULL, tests_datasture_charpter01 },
	{ "suit_datasture02", NULL, NULL, tests_datasture_charpter02 },
	{ "suit_datasture03", NULL, NULL, tests_datasture_charpter03 },
	{ "suit_datasture04", NULL, NULL, tests_datasture_charpter04 },
	{ "suit_datasture05", NULL, NULL, tests_datasture_charpter05 },
	CU_SUITE_INFO_NULL,
};
void AddDataStructuresTests(void)
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