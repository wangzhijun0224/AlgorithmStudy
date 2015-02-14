#include <stdio.h>

#include "Basic.h"
#include "DS_test.h"

int main()
{
	CU_BasicRunMode mode = CU_BRM_VERBOSE;
	CU_ErrorAction error_action = CUEA_IGNORE;

	setvbuf(stdout, NULL, _IONBF, 0);

	if (CU_initialize_registry()) {
		printf("\nInitialization of Test Registry failed.");
	}
	else {
		AddDataStructuresTests();
		CU_basic_set_mode(mode);
		CU_set_error_action(error_action);
		printf("\nTests completed with return value %d.\n", CU_basic_run_tests());
		CU_cleanup_registry();
	}

	return 0;


}