#ifndef _LISTH_
#define _LISTH_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct list
{
	int id;
	int number_of_times;
	char *name;
	struct list *next;
}listNode;

listNode *CreateList(listNode **,char *);
void insert(listNode **,int,char *);
void print(listNode **);
void length(listNode **);
void FreeList(listNode **);

#endif