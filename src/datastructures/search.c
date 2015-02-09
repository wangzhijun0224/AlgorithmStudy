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