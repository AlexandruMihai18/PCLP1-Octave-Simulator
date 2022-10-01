#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

//function to check index integrity
int check_index(int index, int d1)
{
	if (index >= d1 || index < 0)
		return 1;
	return 0;
}

//checking the indexes integrity for the Strassen Algorithm
int check_strassen(int *d2, int *d3, int index1, int index2)
{
	if (d2[index1] != d2[index2])
		return 1;
	if (d2[index1] != d3[index1])
		return 1;
	if (d2[index1] != d3[index2])
		return 1;
	return 0;
}

//warning message due to an erroneous index
void index_err(void)
{
	printf("No matrix with the given index\n");
}

//warning message due to sizes of the matrices
void multiplication_err(void)
{
	printf("Cannot perform matrix multiplication\n");
}

//swap functionused in the sorting algorithm
void swap(int ****a, int **sums, int **d2, int **d3, int i, int j)
{
	//swapping the matrices
	int **aux = (*a)[i];
	(*a)[i] = (*a)[j];
	(*a)[j] = aux;

	//swapping the lengths of the matrices
	int tmp = (*d2)[i];
	(*d2)[i] = (*d2)[j];
	(*d2)[j] = tmp;

	//swapping the widths of the matrices
	tmp = (*d3)[i];
	(*d3)[i] = (*d3)[j];
	(*d3)[j] = tmp;

	//swapping the sums of the matrices
	tmp = (*sums)[i];
	(*sums)[i] = (*sums)[j];
	(*sums)[j] = tmp;
}