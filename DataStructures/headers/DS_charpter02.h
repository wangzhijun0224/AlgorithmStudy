#ifndef _DS_CHARPTER02_H_
#define _DS_CHARPTER02_H_

/*********************************************************************************** 
	�����Ӧ�ã�ADT����ʽ
***********************************************************************************/

/* 
	����ʽ��ʾ��1�� 
		�ŵ�: ��������㶼�Ƚϼ�;
		ȱ��: ���ڷ�ϡ�����ʽ��degree��MAX_DEGREE���ϴ󣬴˷�ʽ�Ƚ��˷��ڴ�
*/
#define MAX_DEGREE	101
typedef struct
{
	int degree;					// ����
	double coef[MAX_DEGREE];		// ϵ������,����ָ����������
}polynomial1;

/* 
	����ʽ��ʾ��2��ÿһ����ϵ���ͽ������
	�ŵ�: ����ϵ������ʱ���ȷ�һʡ�ڴ�
*/
typedef struct
{
	float coef;
	int expon;
}polyitem;

typedef struct
{
	int count;
	polyitem *poly;
}polynomial2;

/*
	ϡ�����:
	��һ��sparematrixitem�����ʾһ��ϡ�������������ĵ�0��Ԫ�ص�col,row,value�ֱ��ʾ���������,
	������Ԫ�ظ���
*/
typedef struct
{
	int col;	// �к�
	int row;	// �к�
	int value;	// ֵ
}sparematrixitem;

/***********************************************************************************
***********************************************************************************/
void polynomial1_print(polynomial1* poly);
double polynomial1_sum(polynomial1* poly, double x0);	// �����ʽ��x=x0����ֵ
void polynomial1_add(polynomial1* a, polynomial1* b, polynomial1* c); // ����ʽ���c = a + b
void polynomial2_add(polynomial2* a, polynomial2* b, polynomial2* c); // ����ʽ���c = a + b

void sparematrix_set(sparematrixitem a[], int col, int row);
void sparematrix_additem(sparematrixitem a[], int col, int row, int value);
void sparematrix_transpose(sparematrixitem a[], sparematrixitem b[]);	// ϡ������ת��
void sparematrix_fast_transpose(sparematrixitem a[], sparematrixitem b[]); // ϡ�����Ŀ���ת��
void sparematrix_mult(sparematrixitem a[], sparematrixitem b[], sparematrixitem d[]); //ϡ������ת��
#endif