#include "trie.h"

void CreateTrie(trieNode_t **root)			//create root
{
	*root = CreateTrieNode('\n');
}

trieNode_t * CreateTrieNode(char key)		//initialize root
{
	trieNode_t *node = NULL;
	node = (trieNode_t *)malloc(sizeof(trieNode_t));

	if(node == NULL)
	{
		fprintf(stderr,"Malloc failed\n");
		return node;
	}

	node->key = key;
	node->children = NULL;
	node->neighbor = NULL;
	node->plist = NULL;
	node->endofword = 0;
	return node;
}


void AddNode(trieNode_t **root,char *key,int id)
{
	char *tmpstr = key;
	char *tmp1 ;
	trieNode_t *tempNode = NULL;

	if (*root == NULL)
	{
		fprintf(stderr, "Not initialized Trie!\n");
		exit(1);
	}

	
	tempNode = *root;
	
	while (*key != '\0')
	{
		if (tempNode->children == NULL)		
		{
			tempNode->children = CreateTrieNode(*key);	
			tempNode = tempNode->children;			
			//key++;								 
		}
		else
		{
			tempNode = tempNode->children;	
			// if (tempNode->key == *key)
			// {
			// 	;//key++;
			// 	//tempNode = tempNode->children;
			// }
			// else
			if (tempNode->key != *key)
			{
				if (tempNode->neighbor == NULL)
				{
					tempNode->neighbor = CreateTrieNode(*key);
					tempNode = tempNode->neighbor;
					//key++;
				}
				else
				{
					int flag = 0;
					while (tempNode->neighbor != NULL)
					{
						tempNode = tempNode->neighbor;
						if (tempNode->key == *key)
						{
							//tempNode = tempNode->neighbor;
							//key++;
							flag++;
							break;
						}
					}
					if (!flag)
					{
						tempNode->neighbor = CreateTrieNode(*key);
						tempNode = tempNode->neighbor;
						//key++;
					}
				}
			}
		}
		// tmp1 = key;
		// tmp1++;
		// if (*tmp1 == '\0')
		// {	
		// 	tempNode->endofword = 1;
		// 	break;
		// }
		key++;
	}
	
	tempNode->endofword = 1;
	// printf("%c and eow %d for %s\n",tempNode->key,tempNode->endofword,tmpstr);
	listNode *cur = tempNode->plist;
	// printf("TMPSTR %s\n",tmpstr);
	insert(&(tempNode->plist),id,tmpstr);
	// print(&(tempNode->plist));		//print plist
	
}

void printNode(trieNode_t **root,char *key)
{
	int found = 0 , finish = 1;
	char *str = key;
	char *str1 ;
	char *buffer = malloc(sizeof(char)*(strlen(str)+1));
	if (buffer == NULL)
		printf("malloc error\n");

	trieNode_t *tempNode = NULL;

	if (*root == NULL)
	{
		fprintf(stderr, "Not initialized Trie!\n");
		exit(1);
	}
	
	tempNode = *root;
	int i;
	for (i=0;i<strlen(str);i++)
	{
		while (tempNode->children!=NULL)
		{
			tempNode = tempNode->children;
			if (tempNode->key == *key)
			{
				buffer[i] = tempNode->key;
				break;
			}
			else
			{
				found = 0;
				while (tempNode->neighbor != NULL)
				{
					tempNode = tempNode->neighbor;
					if (tempNode->key == *key)
					{
						buffer[i] = tempNode->key;
						found = 1;
						break;
					}
				}
				if (found)
					break;
			}
		}
		key++;

		// if (tempNode->endofword && i==strlen(str)-1 && tempNode->key != *key)
		// {
		// 	printf("eow %d and %c.%s\n",tempNode->endofword,tempNode->key,str);
		// 	printf("%s not found\n",str);
		// 	finish = 0;
		// 	break;
		// }
	}
	buffer[i] = '\0'; 	//lathos na to ftiaxv
	if (!strncmp(buffer, str,strlen(str)) && tempNode->endofword)
	{
		finish = 1;
		listNode *l = tempNode->plist;
		if (l != NULL)
		{
			printf("NAME is %s\n",l->name);
		}
		//printf("%s not found\n",str);
	}
	else
	{
		finish = 0;
		printf("%s not found\n",str);
	}
	if (finish)
		printf("PRINT : %s\n",buffer);


	free(buffer);
}


listNode *find_word(trieNode_t **root,char *key)
{
	int found = 0 , finish = 1;
	char *str = key;
	char *str1 ;
	char *buffer = malloc(sizeof(char)*(strlen(str)+1));
	if (buffer == NULL)
		printf("malloc error\n");

	trieNode_t *tempNode = NULL;

	if (*root == NULL)
	{
		fprintf(stderr, "Not initialized Trie!\n");
		exit(1);
	}
	
	tempNode = *root;
	int i;
	for (i=0;i<strlen(str);i++)
	{
		while (tempNode->children!=NULL)
		{
			tempNode = tempNode->children;
			if (tempNode->key == *key)
			{
				buffer[i] = tempNode->key;
				break;
			}
			else
			{
				found = 0;
				while (tempNode->neighbor != NULL)
				{
					tempNode = tempNode->neighbor;
					if (tempNode->key == *key)
					{
						buffer[i] = tempNode->key;
						found = 1;
						break;
					}
				}
				if (found)
					break;
			}
		}
		key++;
	}
	buffer[strlen(str)] = '\0'; 	//lathos na to ftiaxv
	if (!strcmp(buffer, str) && tempNode->endofword)
	{
		if (tempNode->plist == NULL)
		{
			printf("EMPTY posting list for %s\n",key);
			free(buffer);
			return NULL;
		}
		else
		{
			free(buffer);
			printf("plist %d\n",tempNode->plist->number_of_times);
			return tempNode->plist;
		}
	}
	else
	{
		finish = 0;
		printf("%s not found\n",str);
		free(buffer);
		return NULL;

	}
}

void df(trieNode_t **root)
{
	stackNode_t *head = NULL;
	trieNode_t *tempNode = NULL;
	trieNode_t *cur = NULL;
	listNode *plist = NULL;
	int times;
	tempNode = *root;

	while (tempNode->children)
	{
		tempNode = tempNode->children;
		push(&head,tempNode);
		// printf("Push %c\n",tempNode->key);
	}
	while (head != NULL)
	{
		tempNode = pop(&head);
		if (tempNode == NULL)
			break;
		if(tempNode->neighbor != NULL)
		{
			push(&head, tempNode);
			// printf("Push %c\n",tempNode->key);
			cur = tempNode;
			tempNode = tempNode->neighbor;
			cur->neighbor = NULL;
			push(&head,tempNode);
			// printf("Push %c\n",tempNode->key);
			while (tempNode->children)
			{
				tempNode = tempNode->children;
				push(&head,tempNode);
				// printf("Push %c\n",tempNode->key);
			}
		}
		else
		{	
			plist = tempNode->plist;
			if (plist)
			{
				times = 0;
				while (plist->next)
				{
					plist = plist->next;
					times++;
				}
				printf("%s %d\n",tempNode->plist->name,times);
			}	

		}
	}
	free(head);
	// free(*root);
}



void FreeTrie(trieNode_t **root)
{
	stackNode_t *head = NULL;
	trieNode_t *tempNode = NULL;
	trieNode_t *cur = NULL;
	tempNode = *root;

	while (tempNode->children)
	{
		tempNode = tempNode->children;
		push(&head,tempNode);
	}
	while (head != NULL)
	{
		tempNode = pop(&head);
		if (tempNode == NULL)
			break;
		// printf("Pop %c\n",tempNode->key);
		if(tempNode->neighbor != NULL)
		{
			push(&head, tempNode);
			cur = tempNode;
			// printf("Before push %c\n",tempNode->key);
			tempNode = tempNode->neighbor;
			cur->neighbor = NULL;
			// printf("Kanv push %c\n",tempNode->key);
			push(&head,tempNode);
			while (tempNode->children)
			{
				tempNode = tempNode->children;
				push(&head,tempNode);
			}
		}
		else
		{
			if (tempNode->plist != NULL)
			{	
				FreeList(&tempNode->plist);
				free(tempNode->plist);
			}
			// printf("DELETING %c\n",tempNode->key);
			free(tempNode);
		}
	}
	free(head);
	free(*root);
}