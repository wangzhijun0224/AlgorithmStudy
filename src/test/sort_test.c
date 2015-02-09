#include "sort.h"
#include "search.h"

#include <stdlib.h>
#include <stdio.h>

void select_sort_test()
{
#define  MAX_SIZE  20

	int list[MAX_SIZE] = { 0 };

	printf("Original List:\n");

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		list[i] = rand();
		printf("%d\t", list[i]);
	}

	select_sort(list, MAX_SIZE);

	printf("\nOrigina List Sorted:\n");
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		printf("%d\t", list[i]);
	}

	// search test
	int right = MAX_SIZE - 1;
	if (0 != binary_search(list, list[0], 0, right))
	{
		printf("search function has error.\n");
	}

	if (right != binary_search(list, list[right], 0, right))
	{
		printf("search function has error.\n");
	}

	if (-1 != binary_search(list, list[right+1], 0, right))
	{
		printf("search function has error.\n");
	}
}