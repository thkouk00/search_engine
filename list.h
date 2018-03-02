#ifndef _LISTH_
#include <stdio.h>
#include <stdlib.h>


typedef struct list
{
	long id;
	int number_of_times;
	struct list *next;
}listNode;

void insert(listNode **,long , int);
void print(listNode **);
void length(listNode **);

#endif