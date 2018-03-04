#ifndef _LISTH_
#include <stdio.h>
#include <stdlib.h>


typedef struct list
{
	int id;
	int number_of_times;
	struct list *next;
}listNode;

listNode *CreateList(listNode **);
void insert(listNode **,int);
void print(listNode **);
void length(listNode **);

#endif