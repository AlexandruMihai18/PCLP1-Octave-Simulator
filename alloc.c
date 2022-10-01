#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

//allocating memory for an array that consists of one matrix
int ***alloc_triplepointer(int length)
{
	int ***a = malloc(length * sizeof(int **));
	return a;
}

//allocating memory for a matrix
int **alloc_matrix(int length, int width)
{
	int **matrix = malloc(length * sizeof(int *));
	//defensive programming
	if (!matrix)
		return NULL;
	for (int i = 0; i < length; i++) {
		matrix[i] = malloc(width * sizeof(int));
		//further defensive programming
		if (!matrix[i]) {
			for (int j = 0; j < i; j++)
				free(matrix[i]);
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

//allocating memory for a array
int *alloc_array(int length)
{
	int *v = malloc(length * sizeof(int));
	return v;
}

//resizing a given vector of matrices
int ***realloc_triplepointer(int ***a, int length)
{
	int ***matrix = realloc(a, length * sizeof(int **));
	return matrix;
}

//resizing a given array
int *realloc_array(int *v, int length)
{
	int *array = realloc(v, length * sizeof(int));
	return array;
}

