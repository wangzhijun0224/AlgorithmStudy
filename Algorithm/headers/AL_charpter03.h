#ifndef _AL_CHARPTER03_H_
#define _AL_CHARPTER03_H_

int loga(int n, int a);
int get_prime(int n, int* primearray);
int get_prime2(int n, int* primearray);
void throw_coin(int m, int n, int* rlt);

int near_point(int n, double d, double *randdata);
int near_point2(int n, double d, double *randdata);

int josephus_circle(int n, int m);
int josephus_circle2(int n, int m);

/*µ¥Á´±í*/
typedef struct node *   link;
struct node{
	int item;
	link next;
};
link list_reverse(link x);
#endif