#include "list.h"

listNode *CreateList(listNode **head,char *name)
{
	*head = (listNode*)malloc(sizeof(struct list));
	(*head)->id = -1;
	(*head)->number_of_times = 0;
	(*head)->next = NULL;
	(*head)->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy((*head)->name, name);
	//(*head)->name = name;
	return *head;
}

void insert(listNode **head,int id,char *name)
{
	if (*head == NULL)
	{
		*head = CreateList(head,name);
	}
	listNode *cur = *head;
	int flag = 0;
	while (cur->next !=NULL)
	{
		cur = cur->next;
		if (cur->id == id)
		{
			cur->number_of_times++;
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		//printf("MPIKA list\n");
		listNode *n = (listNode*)malloc(sizeof(struct list));
		n->id = id;
		n->number_of_times = 1;
		n->next = NULL;
		n->name = NULL;
		cur->next = n;
	}
	(*head)->number_of_times++;
}

void print(listNode **head)
{
	listNode *cur = *head;
	printf("PLIST NAME %s\n",cur->name);
	if (cur->next == NULL)
		printf("Empty list\n");
	else
	{
		//printf("Total value %d\n",cur->number_of_times);
		while (cur->next !=NULL)
		{
			cur = cur->next;
			printf("id %d and number_of_times %d\n\n",cur->id,cur->number_of_times);
			//cur = cur->next;
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

void FreeList(listNode **head)
{
	listNode *cur = *head;
	listNode *temp;
	while (cur->next != NULL)
	{
		temp = cur->next;
		cur->next = temp->next;
		// printf("LIST id %d number %d\n",temp->id,temp->number_of_times);
		free(temp);
		if (cur == NULL)
			break;
	}
}