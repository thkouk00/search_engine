#ifdef _MAX_HEAPH_
#define _MAX_HEAPH_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct heap{
	double result;
	int id;
}heap_t;

void insert_heap(max_heap **,double);
void delete_from_heap();
void heapify();
void free_heap();




#endif