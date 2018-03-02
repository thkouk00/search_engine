#include "list.h"

void insert(listNode **head,long id,int number_of_times)
{
	listNode *n = (listNode*)malloc(sizeof(struct list));
	n->id = id;
	n->number_of_times = number_of_times;
	n->next = NULL;
	listNode *cur = *head;
	if (*head == NULL){
		*head = n;
	}
	else
	{
		while (cur->next !=NULL)
			cur = cur->next;
		cur->next = n;
	}
}

void print(listNode **head)
{
	listNode *cur = *head;
	if (cur == NULL)
		printf("Empty list\n");
	else
	{
		while (cur !=NULL)
		{
			printf("id %ld and number_of_times %d\n",cur->id,cur->number_of_times);
			cur = cur->next;
		}
	}
}

void length(listNode **head)
{
	int len = 0;
	listNode *cur = *head;
	while (cur !=NULL)
	{
		len++;
		cur = cur->next;
	}
	printf("Length %d\n",len);
}