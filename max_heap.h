#ifndef _MAXHEAPH_
#define _MAXHEAPH_
#include <stdio.h>
#include <stdlib.h>

#define SIZE_HEAP 10

typedef struct heap
{
	double result;
	int id;
}max_heap;

void insert_heap(max_heap **,double,int);
void heapify(max_heap **);
void print_heap(max_heap **);
void Free_heap(max_heap **);
#endif