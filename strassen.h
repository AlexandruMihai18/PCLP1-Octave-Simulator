#ifndef STRASSEN_H__
#define STRASSEN_H__

#include "alloc.h"
#include "free.h"
#include "utility.h"

#define MOD 10007

int **add(int **a, int **b, int length, int width);

int **substraction(int **a, int **b, int length, int width);

int ***matrix_init(int **a, int l);

int **s_simple_multiplication(int **matrix, int **a, int **b);

int ***precalculation(int ***a_block, int ***b_block, int length);

void matrix_determination(int ***matrix, int ***m_block, int l);

int **s_multiplication(int **a, int **b, int length);

int **strassen(int ***a, int d1, int *d2, int *d3, int index1, int index2);

#endif // STRASSEN_H__
