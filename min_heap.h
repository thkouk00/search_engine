#ifndef _MINHEAPH_
#define _MINHEAPH_
#include <stdio.h>
#include <stdlib.h>

#define SIZE_HEAP 10

typedef struct heap
{
	double result;
	int id;
}min_heap;

void insert_heap(min_heap **,double,int,int);
void heapify(min_heap **,int);
void heapsort(min_heap **,int);
void print_heap(min_heap **,int);
void Free_heap(min_heap **,int);
#endif