#ifndef _DS_CHARPTER02_H_
#define _DS_CHARPTER02_H_

/*********************************************************************************** 
	�����Ӧ�ã�ADT����ʽ
***********************************************************************************/

/* ����ʽ��ʾ��1�� 
	�ŵ�: ��������㶼�Ƚϼ�;
	ȱ��: ���ڷ�ϡ�����ʽ��degree��MAX_DEGREE���ϴ󣬴˷�ʽ�Ƚ��˷��ڴ�
*/
#define MAX_DEGREE	101
typedef struct
{
	int degree;					// ����
	double coef[MAX_DEGREE];		// ϵ������,����ָ����������
}polynomial1;

void polynomial1_print(polynomial1* poly);
double polynomial1_sum(polynomial1* poly, double x0);	// �����ʽ��x=x0����ֵ

#endif