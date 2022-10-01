#ifndef UTILITY_H__
#define UTILITY_H__

int check_index(int index, int d1);

int check_strassen(int *d2, int *d3, int index1, int index2);

void index_err(void);

void multiplication_err(void);

void swap(int ****a, int **sums, int **d2, int **d3, int i, int j);

#endif // UTILITY_H__
