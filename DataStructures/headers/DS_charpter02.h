#ifndef _DS_CHARPTER02_H_
#define _DS_CHARPTER02_H_

/*********************************************************************************** 
	数组的应用：ADT多项式
***********************************************************************************/

/* 
	多项式表示法1： 
		优点: 大多数运算都比较简单;
		缺点: 对于非稀疏多项式或degree与MAX_DEGREE相差较大，此方式比较浪费内存
*/
#define MAX_DEGREE	101
typedef struct
{
	int degree;					// 阶数
	double coef[MAX_DEGREE];		// 系数数组,按照指数降幂排序
}polynomial1;

/* 
	多项式表示法2：每一项由系数和阶数组成
	优点: 非零系数较少时，比法一省内存
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
	稀疏矩阵:
	用一个sparematrixitem数组表示一个稀疏矩阵，其中数组的第0个元素的col,row,value分别表示矩阵的行数,
	列数和元素个数
*/
typedef struct
{
	int col;	// 行号
	int row;	// 列号
	int value;	// 值
}sparematrixitem;

/***********************************************************************************
***********************************************************************************/
void polynomial1_print(polynomial1* poly);
double polynomial1_sum(polynomial1* poly, double x0);	// 求多项式在x=x0处的值
void polynomial1_add(polynomial1* a, polynomial1* b, polynomial1* c); // 多项式相加c = a + b
void polynomial2_add(polynomial2* a, polynomial2* b, polynomial2* c); // 多项式相加c = a + b

void sparematrix_set(sparematrixitem a[], int col, int row);
void sparematrix_additem(sparematrixitem a[], int col, int row, int value);
void sparematrix_transpose(sparematrixitem a[], sparematrixitem b[]);	// 稀疏矩阵的转置
void sparematrix_fast_transpose(sparematrixitem a[], sparematrixitem b[]); // 稀疏矩阵的快速转置
void sparematrix_mult(sparematrixitem a[], sparematrixitem b[], sparematrixitem d[]); //稀疏矩阵的转置
#endif