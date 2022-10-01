#include <stdio.h>
#include <stdlib.h>

#include "cases.h"

//case for the load function
int case_l(int ****a, int *d1, int **d2, int **d3)
{
	int length, width;
	scanf("%d%d", &length, &width);

	//defensive programming
	//using a copy to not corrupt in case of a failed memory allocation
	int ***cpy_a = load(*a, *d1, length, width);
	if (!cpy_a)
		return 1; //error

	(*a) = cpy_a;
	//reading a matrix
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++)
			scanf("%d", &(*a)[(*d1)][i][j]);
	}

	//further defensive programming
	int *cpy_d2 = realloc_array(*d2, (*d1) + 1);
	if (!cpy_d2)
		return 1;
	(*d2) = cpy_d2;
	(*d2)[(*d1)] = length; //the length of the matrix

	int *cpy_d3 = realloc_array(*d3, (*d1) + 1);
	if (!cpy_d3)
		return 1;
	(*d3) = cpy_d3;
	(*d3)[(*d1)] = width; //the width of the matrix
	(*d1)++; //increasing the number of matrixes in the vector
	return 0;
}

//case for the dimension function
int case_d(int *d1, int **d2, int **d3)
{
	int index;
	scanf("%d", &index);
	dimension(*d1, *d2, *d3, index);
	return 0;
}

//case for the print function
int case_p(int ****a, int *d1, int **d2, int **d3)
{
	int index;
	scanf("%d", &index);
	print(*a, *d1, *d2, *d3, index);
	return 0;
}

//case for the resizing function
int case_c(int ****a, int *d1, int **d2, int **d3)
{
	int index;
	scanf("%d", &index);

	int **matrix = resize(*a, *d1, d2, d3, index);
	if (matrix)
		(*a)[index] = matrix;
	return 0;
}

//case for the multiplication function
int case_m(int ****a, int *d1, int **d2, int **d3)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);

	//further defensing programming
	int ***matrix = multiply(*a, *d1, *d2, *d3, index1, index2);

	//adding the matrix in case that there is one
	if (matrix) {
		(*a) = matrix;

		//resizing the used length and width vectors
		int *cpy_d2 = realloc_array(*d2, (*d1) + 1);
		if (!cpy_d2)
			return 1;
		(*d2) = cpy_d2;
		(*d2)[(*d1)] = (*d2)[index1];

		int *cpy_d3 = realloc_array(*d3, (*d1) + 1);
		if (!cpy_d3)
			return 1;
		(*d3) = cpy_d3;
		(*d3)[(*d1)] = (*d3)[index2];

		(*d1)++;
	}
	return 0;
}

//case for the sorting function
int case_o(int ****a, int *d1, int **d2, int **d3)
{
	int ***cpy_a = sort(*a, *d1, d2, d3);
	if (cpy_a)
		(*a) = cpy_a;
	return 0;
}

//case for the transposing function
int case_t(int ****a, int *d1, int **d2, int **d3)
{
	int index;
	scanf("%d", &index);
	int **matrix = transpose(*a, *d1, *d2, *d3, index);
	//adding the matrix in case that there is one
	if (matrix) {
		(*a)[index] = matrix;

		//assuring that the sizes of the next matrix have been updated
		int aux = (*d2)[index];
		(*d2)[index] = (*d3)[index];
		(*d3)[index] = aux;
	}
	return 0;
}

//case for the freeing a single matrix function
int case_f(int ****a, int *d1, int **d2, int **d3)
{
	int index;
	scanf("%d", &index);
	int ***cpy_a = free_one(*a, *d1, d2, d3, index);
	if (cpy_a) {
		(*a) = cpy_a;
		(*d1)--; //decreasing the number of matrices in the vector
	}
	return 0;
}

//case for a Strassen multiplication
int case_s(int ****a, int *d1, int **d2, int **d3)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);

	int **matrix = strassen(*a, *d1, *d2, *d3, index1, index2);
	if (matrix) {
		//adding the new matrix if the Strassen algorithm was successful
		int ***cpy_a = load(*a, *d1, (*d2)[index1], (*d2)[index1]);
		if (!cpy_a)
			return 1;
		(*a) = cpy_a;
		for (int i = 0; i < (*d2)[index1]; i++) {
			for (int j = 0; j < (*d2)[index1]; j++)
				//assuring the conversion between the 2 matrices
				(*a)[(*d1)][i][j] = matrix[i][j];
		}
		//freeing the used resources
		free_matrix(matrix, (*d2)[index1]);

		int *cpy_d2 = realloc_array(*d2, (*d1) + 1);
		if (!cpy_d2)
			return 1;
		(*d2) = cpy_d2;
		(*d2)[(*d1)] = (*d2)[index1]; //the length of the matrix

		int *cpy_d3 = realloc_array(*d3, (*d1) + 1);
		if (!cpy_d3)
			return 1;
		(*d3) = cpy_d3;
		(*d3)[(*d1)] = (*d3)[index1]; //the width of the matrix

		(*d1)++;
	}

	return 0;
}
