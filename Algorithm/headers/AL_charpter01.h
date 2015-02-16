#ifndef _AL_CHARPTER01_H_
#define _AL_CHARPTER01_H_

typedef struct{
	int p;
	int q;
}pair;

int connectivity_quickfind(pair pairs[], int m, int id[], int n, int out[]);
int connectivity_quickunion(pair pairs[], int m, int id[], int n, int out[]);
int connectivity_weighted_quickunion(pair pairs[], int m, int id[], int n, int out[]);
int connectivity_pathcompression_weighted_quickunion(pair pairs[], int m, int id[], int n, int out[]);

#endif