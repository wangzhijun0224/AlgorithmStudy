#include "DS_charpter05_test.h"

#include "DS_charpter05.h"

static btree create_btree(void)
{
	int	item;

	btree bt = btree_open(sizeof(item));

	item = 0;
	tlink root = NULL, left = NULL, right = NULL;

	item = 8;
	left = btree_make_btree(bt, NULL, &item, NULL);
	item = 9;
	right = btree_make_btree(bt, NULL, &item, NULL);
	item = 4;
	root = btree_make_btree(bt, left, &item, right);

	item = 10;
	left = btree_make_btree(bt, NULL, &item, NULL);
	item = 11;
	right = btree_make_btree(bt, NULL, &item, NULL);
	item = 5;
	right = btree_make_btree(bt, left, &item, right);

	left = root;
	item = 2;
	root = btree_make_btree(bt, left, &item, right);

	item = 3;
	right = btree_make_btree(bt, NULL, &item, NULL);
	
	


}


/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter05[] = {
	CU_TEST_INFO_NULL,
};