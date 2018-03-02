#include <stdio.h>
#include "list.h"

int main()
{
	listNode *head =NULL;//= (listNode*)malloc(sizeof(listNode));
	insert(&head, 1, 2);
	insert(&head, 3, 4);
	insert(&head, 5, 6);
	insert(&head, 7, 8);
	insert(&head, 9, 10);
	insert(&head, 11, 12);
	insert(&head, 13, 14);
	insert(&head, 15, 16);
	insert(&head, 17, 18);
	insert(&head, 19, 20);
	print(&head);
	length(&head);
	char *name = "Thanos-Koukoulis";
	while (*name != '\0')
	{
		printf("%c\n",*name);
		name++;
	}
}