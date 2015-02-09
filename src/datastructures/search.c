/***********************************************************************************
	���ֲ��ң�
	list[]Ϊ���Ӵ�С����õ�����
	left��rightΪ���ҵ����ұ߽�
	���ҵ�������searchnum���ڵ��±꣬���򷵻�-1
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