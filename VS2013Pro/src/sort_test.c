#include "sort.h"

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
}