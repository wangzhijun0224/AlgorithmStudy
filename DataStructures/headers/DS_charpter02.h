#ifndef _DS_CHARPTER02_H_
#define _DS_CHARPTER02_H_

/*********************************************************************************** 
	数组的应用：ADT多项式
***********************************************************************************/

/* 多项式表示法1： 
	优点: 大多数运算都比较简单;
	缺点: 对于非稀疏多项式或degree与MAX_DEGREE相差较大，此方式比较浪费内存
*/
#define MAX_DEGREE	101
typedef struct
{
	int degree;					// 阶数
	double coef[MAX_DEGREE];		// 系数数组,按照指数降幂排序
}polynomial1;

void polynomial1_print(polynomial1* poly);
double polynomial1_sum(polynomial1* poly, double x0);	// 求多项式在x=x0处的值

#endif