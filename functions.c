#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int ***load(int ***a, int d1, int length, int width)
{
	int ***cpy_a = realloc_triplepointer(a, d1 + 1);
	//defensive programming
	if (!cpy_a)
		return NULL;
	cpy_a[d1] = alloc_matrix(length, width);
	return cpy_a;
}

//function to show the size of a given matrix
void dimension(int d1, int *d2, int *d3, int index)
{
	if (check_index(index, d1))
		index_err();
	else
		printf("%d %d\n", d2[index], d3[index]);
}

//function to print a given matrix
void print(int ***a, int d1, int *d2, int *d3, int index)
{
	if (check_index(index, d1)) {
		index_err();
	} else {
		for (int i = 0; i < d2[index]; i++) {
			for (int j = 0; j < d3[index]; j++)
				printf("%d ", a[index][i][j]);
			printf("\n");
		}
	}
}

//function to resize a given matrix
int **resize(int ***a, int d1, int **d2, int **d3, int index)
{
	if (check_index(index, d1)) {
		index_err();
		return NULL;
	}
	int length, width;

	scanf("%d", &length);
	//using an array to memorize the rows that will be kept
	int *row = alloc_array(length);
	if (!row)
		return NULL;
	for (int i = 0; i < length; i++)
		scanf("%d", &row[i]);

	scanf("%d", &width);
	//using an array to memorize the columns that will be kept
	int *column = alloc_array(width);
	if (!column)
		return NULL;
	for (int i = 0; i < width; i++)
		scanf("%d", &column[i]);

	//building the new matrix
	int **matrix = alloc_matrix(length, width);
	if (!matrix)
		return NULL;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++)
			matrix[i][j] = a[index][row[i]][column[j]];
	}

	//freeing the memory for the old matrix
	free_matrix(a[index], (*d2)[index]);
	//freeing the used arrays
	free(row);
	free(column);
	//reestablishing new sizes for the matrix
	(*d2)[index] = length;
	(*d3)[index] = width;

	//returning the next matrix
	return matrix;
}

int ***multiply(int ***a, int d1, int *d2, int *d3, int index1, int index2)
{
	if (check_index(index1, d1) || check_index(index2, d1)) {
		index_err();
		return NULL;
	}

	if (d3[index1] != d2[index2]) {
		multiplication_err();
		return NULL;
	}

	//adding another matrix in the vector of matrices
	//it includes the result of multiplying 2 given matrices
	int ***matrix = load(a, d1, d2[index1], d3[index2]);
	if (!matrix)
		return NULL;
	for (int i = 0; i < d2[index1]; i++) {
		for (int j = 0; j < d3[index2]; j++)
			matrix[d1][i][j] = 0;
	}
	for (int i = 0; i < d2[index1]; i++) {
		for (int j = 0; j < d3[index2]; j++) {
			for (int k = 0; k < d2[index2]; k++)
				//the multiplication process modulo MOD
				//assuring the positivite nature of the result
				matrix[d1][i][j] = (matrix[d1][i][j] + (matrix[index1][i][k]
									* matrix[index2][k][j]) % MOD + MOD) % MOD;
		}
	}
	//returning the newly added matrix
	return matrix;
}

int ***sort(int ***a, int d1, int **d2, int **d3)
{
	//using a sums array as a criteria for the sorting algorithm
	int *sums = alloc_array(d1);
	if (!sums)
		return NULL;
	for (int i = 0; i < d1; i++)
		sums[i] = 0;

	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < (*d2)[i]; j++) {
			for (int k = 0; k < (*d3)[i]; k++)
				sums[i] = (sums[i] + MOD + a[i][j][k]) % MOD;
		}
	}
	//the selection sorting algorithm
	for (int i = 0; i < d1; i++) {
		for (int j = i + 1; j < d1; j++) {
			if (sums[i] > sums[j])
				swap(&a, &sums, d2, d3, i, j);
		}
	}
	//freeing the used vector
	free_array(sums);
	return a;
}

int **transpose(int ***a, int d1, int *d2, int *d3, int index)
{
	if (check_index(index, d1)) {
		index_err();
		return NULL;
	}
	//new matrix that includes the transposed given matrix
	int **matrix = alloc_matrix(d3[index], d2[index]);
	if (!matrix)
		return NULL;
	for (int i = 0; i < d3[index]; i++) {
		for (int j = 0; j < d2[index]; j++)
			//the transposing process
			matrix[i][j] = a[index][j][i];
	}
	//freeing the non-transposed matrix
	free_matrix(a[index], d2[index]);
	//returning the next matrix in the array of matrices
	return matrix;
}

//function that frees the memory used of a single matrix
int ***free_one(int ***a, int d1, int **d2, int **d3, int index)
{
	if (check_index(index, d1)) {
		index_err();
		return NULL;
	}
	//freeing the memory of a matrix
	free_matrix(a[index], (*d2)[index]);

	//assuring the continuity of the 3 arrays
	for (int i = index + 1; i < d1; i++) {
		a[i - 1] = a[i];
		(*d2)[i - 1] = (*d2)[i];
		(*d3)[i - 1] = (*d3)[i];
	}
	//returning the new array of matrices
	return a;
}

