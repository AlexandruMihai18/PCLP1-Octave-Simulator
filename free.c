#include <stdio.h>
#include <stdlib.h>

#include "free.h"

//freeing the memory for an array
void free_array(int *v)
{
	free(v);
}

//freeing the memory for a matrix
void free_matrix(int **a, int length)
{
	for (int i = 0; i < length; i++)
		free(a[i]);
	free(a);
}

//freeing all the used resources
void free_all(int ***a, int d1, int *d2, int *d3)
{
	for (int i = 0; i < d1; i++)
		free_matrix(a[i], d2[i]);
	free_array(d2);
	free_array(d3);
	free(a);
}
