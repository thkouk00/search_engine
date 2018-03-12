#include "list.h"

listNode *CreateList(listNode **head,char *name)
{
	*head = (listNode*)malloc(sizeof(struct list));
	(*head)->id = -1;
	(*head)->number_of_times = 0;
	(*head)->next = NULL;
	(*head)->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy((*head)->name, name);
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
	if (cur->next == NULL)
		printf("Empty list\n");
	else
	{
		while (cur->next !=NULL)
		{
			cur = cur->next;
			printf("id %d and number_of_times %d\n\n",cur->id,cur->number_of_times);
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
	if (*head != NULL)
	{
		free((*head)->name);
		while (cur->next != NULL)
		{
			temp = cur->next;
			cur->next = temp->next;
			free(temp);
			if (cur == NULL)
				break;
		}
	}
}


//for search 

void insert_search(list_t **head,int number_of_times,int word_from)
{
	if (*head == NULL)
	{
		*head = (list_t*)malloc(sizeof(struct list_search));
		(*head)->number_of_times = -1;
		(*head)->word_from = -1;
		(*head)->next = NULL;
	}
	list_t *cur = *head;

	list_t *n = (list_t*)malloc(sizeof(struct list_search));
	n->number_of_times = number_of_times;
	n->word_from = word_from;
	n->next = cur->next;
	cur->next = n;
}

void print_search(list_t **head)
{
	list_t *cur = *head;
	if (cur->next == NULL)
		printf("Empty list\n");
	else
	{
		while (cur->next !=NULL)
		{
			cur = cur->next;
			printf("number_of_times %d\n\n",cur->number_of_times);
		}
	}
}

void FreeList_search(list_t **head)
{
	list_t *cur = *head;
	list_t *temp;
	if (*head != NULL)
	{
		while (cur->next != NULL)
		{
			temp = cur->next;
			cur->next = temp->next;
			free(temp);
			if (cur == NULL)	//mallon axristo
			{
				free(cur);
				break;
			}
		}
	}
}