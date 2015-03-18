#include "DS_charpter05_test.h"

#include "DS_charpter05.h"


static void create_btree_test(void)
{
/*
Ê÷:
	    A
	  /   \
	 B      C
	/ \    / \
     D   E  F   G
    / \
   H   I
*/
	char str[] = { 'A', 'B', 'D', 'H', '\0', '\0', 'I', '\0', '\0', 'E',
		'\0', '\0', 'C', 'F', '\0', '\0', 'G', '\0', '\0' };

	char end_item = '\0';

	btree bt = btree_open(sizeof(char));
	btree_make_btree(bt, str, &end_item);

	tlink root = btree_get_root(bt);

	char ch;
	btree_get_item(bt, root, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[0], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(NULL, btree_get_parent(bt, root));
	#endif
	
	tlink left, right;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[1], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[12], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	root = right;
	tlink tmp = btree_get_lchild(bt, root);
	btree_get_item(bt, tmp, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[13], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, tmp));
	#endif
	
	tmp = btree_get_rchild(bt, root);
	btree_get_item(bt, tmp, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[16], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, tmp));
	#endif
	
	root = left;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[2], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[9], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	root = left;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[3], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[6], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	btree_close(bt);
}


static void copy_btree_test(void)
{
/*
Ê÷:
	    A
	  /   \
	 B      C
	/ \    / \
     D   E  F   G
    / \
   H   I
*/
	char str[] = { 'A', 'B', 'D', 'H', '\0', '\0', 'I', '\0', '\0', 'E',
		'\0', '\0', 'C', 'F', '\0', '\0', 'G', '\0', '\0' };

	char end_item = '\0';

	btree bt1 = btree_open(sizeof(char));
	btree_make_btree(bt1, str, &end_item);

	btree bt = btree_copy(bt1);

	CU_ASSERT_EQUAL(1, btree_is_equal(bt1, bt));
	
	tlink root = btree_get_root(bt);

	char ch;
	btree_get_item(bt, root, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[0], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(NULL, btree_get_parent(bt, root));
	#endif
	
	tlink left, right;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[1], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[12], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	root = right;
	tlink tmp = btree_get_lchild(bt, root);
	btree_get_item(bt, tmp, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[13], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, tmp));
	#endif
	
	tmp = btree_get_rchild(bt, root);
	btree_get_item(bt, tmp, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[16], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, tmp));
	#endif
	
	root = left;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[2], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[9], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	root = left;
	left = btree_get_lchild(bt, root);
	btree_get_item(bt, left, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[3], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, left));
	#endif
	
	right = btree_get_rchild(bt, root);
	btree_get_item(bt, right, &ch);
	CU_ASSERT_PTR_DATA_EQUAL(&ch, &str[6], sizeof(ch));
	#if BTREE_HAVE_PARENT
	CU_ASSERT_EQUAL(root, btree_get_parent(bt, right));
	#endif
	
	btree_close(bt);
	btree_close(bt1);
}

/*
µÝ¹é°æ±éÀúº¯Êý²âÊÔ
*/
static void btree_order_test1(void)
{
/*
Ê÷:
	   +
	  / \
	 *   E
	/ \
     *   D
    / \
   /    C
  / \
A   B
*/
	char str[] = { '+', '*', '*', '/', 'A', '\0', '\0', 'B', '\0', '\0',
		'C', '\0', '\0', 'D', '\0', '\0', 'E', '\0', '\0' };
	char end_item = '\0';

	char str_rlt[sizeof(str) / sizeof(str[0])];

	btree bt = btree_open(sizeof(char));
	btree_make_btree(bt, str, &end_item);

	int index = 0;

	index = btree_preorder_recursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("+**/ABCDE", str_rlt, strlen("+**/ABCDE"));

	index = btree_inorder_recursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("A/B*C*D+E", str_rlt, strlen("A/B*C*D+E"));

	index = btree_postorder_recursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("AB/C*D*E+", str_rlt, strlen("AB/C*D*E+"));

	btree_close(bt);
}

/*
·ÇµÝ¹é°æ±éÀúº¯Êý²âÊÔ
*/
static void btree_order_test2(void)
{
	/*
	Ê÷:
	+
	/ \
	*   E
	/ \
	*   D
	/ \
	/    C
	/ \
	A   B
	*/
	char str[] = { '+', '*', '*', '/', 'A', '\0', '\0', 'B', '\0', '\0',
		'C', '\0', '\0', 'D', '\0', '\0', 'E', '\0', '\0' };
	char end_item = '\0';

	char str_rlt[sizeof(str) / sizeof(str[0])];


	btree bt = btree_open(sizeof(char));
	btree_make_btree(bt, str, &end_item);

	int index = 0;

	index = btree_preorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("+**/ABCDE", str_rlt, strlen("+**/ABCDE"));

	index = btree_preorder_norecursion2(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("+**/ABCDE", str_rlt, strlen("+**/ABCDE"));

	index = btree_inorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("A/B*C*D+E", str_rlt, strlen("A/B*C*D+E"));

	index = btree_postorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("AB/C*D*E+", str_rlt, strlen("AB/C*D*E+"));

	index = btree_postorder_norecursion2(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("AB/C*D*E+", str_rlt, strlen("AB/C*D*E+"));

	index = btree_levelorder(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("+*E*D/CAB", str_rlt, strlen("+*E*D/CAB"));

	index = btree_levelorderR(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("+E*D*C/BA", str_rlt, strlen("+E*D*C/BA"));

	btree_close(bt);
}

/*
·ÇµÝ¹é°æ±éÀúº¯Êý²âÊÔ
*/
static void btree_order_test3(void)
{
	/*
	Ê÷:
	A
	/   \
	B      C
	/ \    / \
	D   E  F   G
	/ \
	H   I
	*/
	char str[] = { 'A', 'B', 'D', 'H', '\0', '\0', 'I', '\0', '\0', 'E',
		'\0', '\0', 'C', 'F', '\0', '\0', 'G', '\0', '\0' };

	char str_rlt[sizeof(str) / sizeof(str[0])];

	char end_item = '\0';

	btree bt = btree_open(sizeof(char));
	btree_make_btree(bt, str, &end_item);

	int index = 0;

	index = btree_preorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("ABDHIECFG", str_rlt, strlen("ABDHIECFG"));

	index = btree_preorder_norecursion2(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("ABDHIECFG", str_rlt, strlen("ABDHIECFG"));

	index = btree_inorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("HDIBEAFCG", str_rlt, strlen("HDIBEAFCG"));

	index = btree_postorder_norecursion(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("HIDEBFGCA", str_rlt, strlen("HIDEBFGCA"));

	index = btree_postorder_norecursion2(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("HIDEBFGCA", str_rlt, strlen("HIDEBFGCA"));

	index = btree_levelorder(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("ABCDEFGHI", str_rlt, strlen("ABCDEFGHI"));

	index = btree_levelorderR(bt, str_rlt);
	CU_ASSERT_EQUAL(index, 9);
	CU_ASSERT_PTR_DATA_EQUAL("ACBGFEDIH", str_rlt, strlen("ACBGFEDIH"));

	btree_close(bt);
}


/***********************************************************************************
***********************************************************************************/
CU_TestInfo tests_datasture_charpter05[] = {
	{ "create_btree_test", create_btree_test },
	{ "copy_btree_test", copy_btree_test },
	{ "btree_order_test1", btree_order_test1 },
	{ "btree_order_test2", btree_order_test2 },
	{ "btree_order_test3", btree_order_test3 },
	CU_TEST_INFO_NULL,
};
