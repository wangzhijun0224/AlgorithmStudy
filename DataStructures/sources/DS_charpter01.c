/***********************************************************************************
ѡ������ ��δ��������������ҳ���С������������ŵ������������б����һ��λ��
***********************************************************************************/
void select_sort(int list[], int n)
{
	int tmp, min;

	for (int i = 0; i < n - 1; ++i)
	{
		// ��δ������������ҳ���С������
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

