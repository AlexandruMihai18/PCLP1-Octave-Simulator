#include <stdio.h>
#include <stdlib.h>

#include "strassen.h"

//function that adds 2 matrices
int **add(int **a, int **b, int length, int width)
{
	int **matrix = alloc_matrix(length, width);
	if (!matrix)
		return NULL;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++)
			matrix[i][j] = ((a[i][j] + b[i][j]) % MOD + MOD) % MOD;
	}
	return matrix;
}

//function to substract one matrice from another
int **substraction(int **a, int **b, int length, int width)
{
	int **matrix = alloc_matrix(length, width);
	if (!matrix)
		return NULL;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++)
			matrix[i][j] = ((a[i][j] - b[i][j]) % MOD + MOD) % MOD;
	}
	return matrix;
}

//initializing an array of 4 matrices (the 4 equal sub-blocks)
int ***matrix_init(int **a, int l)
{
	int ***matrix = alloc_triplepointer(4 * sizeof(int **));
	if (!matrix)
		return NULL;
	for (int k = 0 ; k < 4; k++) {
		matrix[k] = alloc_matrix(l, l);
		if (!matrix[k]) {
			for (int s = 0; s < k; s++)
				free_matrix(matrix[s], l);
			free(matrix);
		}
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < l; j++)
				//constructing the matrices based on their block
				//the k variable facilitates this step
				matrix[k][i][j] = a[i + l * (k / 2)][j + l * (k % 2)];
		}
	}
	return matrix;
}

//a basic multiplication of 2 2x2 matrices
//the fundamental step for the Strassen Algorithm
int **s_simple_multiplication(int **matrix, int **a, int **b)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			matrix[i][j] = 0;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++)
				//matrix multiplication with regards to MOD
				matrix[i][j] = (matrix[i][j] + (a[i][k]
								* b[k][j]) % MOD + MOD) % MOD;
		}
	}
	return matrix;
}

//function that constructs the 7 main matrices used in the algorithm
//those matrices are memorized using a triple pointer
int ***precalculation(int ***a_block, int ***b_block, int length)
{
	//an auxiliary triple pointer, buffer for memory leaks
	//this triple pointer will include additions or substractions
	//	of matrices
	int ***aux = malloc(2 * sizeof(int **));
	if (!aux)
		return NULL;

	int ***m_block = malloc(7 * sizeof(int **));
	if (!m_block) {
		free(aux);
		return NULL;
	}

	int l = length;

	//following the necessary steps of the Strassen algorithm
	aux[0] = add(a_block[0], a_block[3], l, l);
	aux[1] = add(b_block[0], b_block[3], l, l);
	m_block[0] = s_multiplication(aux[0], aux[1], l);
	//freeing the used auxiliary memory
	free_matrix(aux[0], l);
	free_matrix(aux[1], l);

	aux[0] = add(a_block[2], a_block[3], l, l);
	m_block[1] = s_multiplication(aux[0], b_block[0], l);
	free_matrix(aux[0], l);

	aux[1] = substraction(b_block[1], b_block[3], l, l);
	m_block[2] = s_multiplication(a_block[0], aux[1], l);
	free_matrix(aux[1], l);

	aux[1] = substraction(b_block[2], b_block[0], l, l);
	m_block[3] = s_multiplication(a_block[3], aux[1], l);
	free_matrix(aux[1], l);

	aux[0] = add(a_block[0], a_block[1], l, l);
	m_block[4] = s_multiplication(aux[0], b_block[3], l);
	free_matrix(aux[0], l);

	aux[0] = substraction(a_block[2], a_block[0], l, l);
	aux[1] = add(b_block[0], b_block[1], l, l);
	m_block[5] = s_multiplication(aux[0], aux[1], l);
	free_matrix(aux[0], l);
	free_matrix(aux[1], l);

	aux[0] = substraction(a_block[1], a_block[3], l, l);
	aux[1] = add(b_block[2], b_block[3], l, l);
	m_block[6] = s_multiplication(aux[0], aux[1], l);
	free_matrix(aux[0], l);
	free_matrix(aux[1], l);

	free(aux);

	return m_block;
}

//function that builds the matrix based on the previous blocks
void matrix_determination(int ***matrix, int ***m_block, int l)
{
	int ***aux = malloc(3 * sizeof(int **));

	//the following steps consists of the reconstruction
	//	of the matrix based on the Strassen Algorithm
	aux[0] = add(m_block[0], m_block[3], l, l);
	aux[1] = substraction(aux[0], m_block[4], l, l);
	aux[2] = add(aux[1], m_block[6], l, l);
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			(*matrix)[i][j] = aux[2][i][j];
	}
	//freeing the used memory
	free_matrix(aux[2], l);
	free_matrix(aux[1], l);
	free_matrix(aux[0], l);

	aux[0] = add(m_block[2], m_block[4], l, l);
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			(*matrix)[i][j + l] = aux[0][i][j];
	}
	free_matrix(aux[0], l);

	aux[0] = add(m_block[1], m_block[3], l, l);
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			(*matrix)[i + l][j] = aux[0][i][j];
	}
	free_matrix(aux[0], l);

	aux[0] = substraction(m_block[0], m_block[1], l, l);
	aux[1] = add(aux[0], m_block[2], l, l);
	aux[2] = add(aux[1], m_block[5], l, l);
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			(*matrix)[i + l][j + l] = aux[2][i][j];
	}
	free_matrix(aux[2], l);
	free_matrix(aux[1], l);
	free_matrix(aux[0], l);

	free(aux);
}

//the main function for the Strassen multiplication
int **s_multiplication(int **a, int **b, int length)
{
	int **matrix = alloc_matrix(length, length);
	if (!matrix)
		return NULL;

	if (length == 2)
		return s_simple_multiplication(matrix, a, b);

	//reducing the size of the matrices to half
	int l = length / 2;

	//deconstructing the given matrices into
	//	4 equally sized blocks
	int ***a_block = matrix_init(a, l);
	int ***b_block = matrix_init(b, l);

	//using another matrix that operates with those blocks
	int ***m_block = precalculation(a_block, b_block, l);

	matrix_determination(&matrix, m_block, l);

	//freeing the used resources (block matrices)
	for (int i = 0; i < 4; i++)
		free_matrix(a_block[i], l);
	free(a_block);

	for (int i = 0; i < 4; i++)
		free_matrix(b_block[i], l);
	free(b_block);

	for (int i = 0; i < 7; i++)
		free_matrix(m_block[i], l);
	free(m_block);

	return matrix;
}

//function that checks the main conditions and assures a smooth transition
//	towards the full Strassen algorithm
int **strassen(int ***a, int d1, int *d2, int *d3, int index1, int index2)
{
	if (check_index(index1, d1) || check_index(index2, d1)) {
		index_err();
		return NULL;
	}

	if (check_strassen(d2, d3, index1, index2)) {
		multiplication_err();
		return NULL;
	}

	int **matrix = s_multiplication(a[index1], a[index2], d2[index1]);
	if (!matrix)
		return NULL;

	return matrix;
}
