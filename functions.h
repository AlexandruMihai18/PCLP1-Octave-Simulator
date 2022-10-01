#ifndef FUNCTIONS_H__
#define FUNCTIONS_H__

#include "alloc.h"
#include "utility.h"
#include "free.h"

#define MOD 10007

int ***load(int ***a, int d1, int length, int width);

void dimension(int d1, int *d2, int *d3, int index);

void print(int ***a, int d1, int *d2, int *d3, int index);

int **resize(int ***a, int d1, int **d2, int **d3, int index);

int ***multiply(int ***a, int d1, int *d2, int *d3, int index1, int index2);

int ***sort(int ***a, int d1, int **d2, int **d3);

int **transpose(int ***a, int d1, int *d2, int *d3, int index);

int ***free_one(int ***a, int d1, int **d2, int **d3, int index);

#endif // FUNCTIONS_H__
