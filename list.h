#ifndef _LISTH_
#define _LISTH_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct list 		//for posting list
{
	int id;
	int number_of_times;
	char *name;
	struct list *next;
}listNode;

typedef struct list_search 		// for search 
{
	int number_of_times;
	int word_from;
	struct list_search *next;
}list_t;

listNode *CreateList(listNode **,char *);
void insert(listNode **,int,char *);
void print(listNode **);
void length(listNode **);
void FreeList(listNode **);

void insert_search(list_t **, int, int);
void print_search(list_t **);
void FreeList_search(list_t **);

#endif