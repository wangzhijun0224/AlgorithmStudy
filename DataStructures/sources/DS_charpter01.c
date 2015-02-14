/***********************************************************************************
选择排序： 从未被排序的整数中找出最小的整数，将其放到已排序整数列表的下一个位置
***********************************************************************************/
void select_sort(int list[], int n)
{
	int tmp, min;

	for (int i = 0; i < n - 1; ++i)
	{
		// 从未排序的整数中找出最小的整数
		min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (list[j] < list[min])
			{
				min = j;
			}
		}

		// swap
		tmp = list[i], list[i] = list[min], list[min] = tmp;
	}
}

/***********************************************************************************
	二分查找：
	list[]为按从大到小排序好的数组
	left，right为查找的左右边界
	若找到，返回searchnum所在的下标，否则返回-1
***********************************************************************************/
int binary_search(int list[], int searchnum, int left, int right)
{
	int middle;

	while (left <= right)
	{
		middle = (left + right) / 2;
		if (list[middle] < searchnum)
		{
			left = middle + 1;
		}
		else if (list[middle] > searchnum)
		{
			right = middle - 1;
		}
		else
		{
			return middle;
		}
	}

	return -1;
}

