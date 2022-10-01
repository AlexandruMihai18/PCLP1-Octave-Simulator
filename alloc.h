#ifndef ALLOC_H__
#define ALLOC_H__

int ***alloc_triplepointer(int length);

int **alloc_matrix(int length, int width);

int *alloc_array(int length);

int ***realloc_triplepointer(int ***a, int length);

int *realloc_array(int *v, int length);

#endif // ALLOC_H__
