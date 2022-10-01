#include <stdio.h>
#include <stdlib.h>

#include "cases.h"

int main(void)
{
	char c; //character to read the given command
	int ***a = alloc_triplepointer(1);
	int d1 = 0;	//first dimension, the number of matrix
	int *d2 = alloc_array(1); //vector for the length of a matrix
	int *d3 = alloc_array(1); //vector for the width of a matrix
	int cond = 0; //checking that none of the memory allocation fail

	scanf("%c", &c);
	while (c != 'Q' && cond == 0) {
		if ('A' <= c && c <= 'Z') {
			//using a switch to evaluate all the cases
			switch (c) {
			case 'L':
				cond = case_l(&a, &d1, &d2, &d3);
				break;
			case 'D':
				cond = case_d(&d1, &d2, &d3);
				break;
			case 'P':
				cond = case_p(&a, &d1, &d2, &d3);
				break;
			case 'C':
				cond = case_c(&a, &d1, &d2, &d3);
				break;
			case 'M':
				cond = case_m(&a, &d1, &d2, &d3);
				break;
			case 'O':
				cond = case_o(&a, &d1, &d2, &d3);
				break;
			case 'T':
				cond = case_t(&a, &d1, &d2, &d3);
				break;
			case 'F':
				cond = case_f(&a, &d1, &d2, &d3);
				break;
			case 'S':
				cond = case_s(&a, &d1, &d2, &d3);
				break;
			default:
				//warning message
				printf("Unrecognized command\n");
			}
		}
		scanf("%c", &c);
	}
	//freeing all resourcers
	free_all(a, d1, d2, d3);
	return 0;
}
