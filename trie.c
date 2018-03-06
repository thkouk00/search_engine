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
			if (tempNode->key == *key)
			{
				;//key++;
				//tempNode = tempNode->children;
			}
			else
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
		tmp1 = key;
		tmp1++;
		if (*tmp1 == '\0')
		{	
			tempNode->endofword = 1;
			break;
		}
		key++;
	}
	//printf ("WORD %c.\n",*key);
	tempNode->endofword = 1;
	//printf("%s :\n",tmpstr);
	
	listNode *cur = tempNode->plist;
	insert(&(tempNode->plist),id);
	print(&(tempNode->plist));		//print plist
	
}

void printNode(trieNode_t **root,char *key)
{
	int found = 0 , finish = 1;
	char *str = key;
	char *str1 ;
	char *buffer = malloc(sizeof(char)*strlen(str));
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
	buffer[strlen(str)] = '\0'; 	//lathos na to ftiaxv
	if (!strcmp(buffer, str) && tempNode->endofword)
	{
		finish = 1;
		//printf("%s not found\n",str);
	}
	else{
		finish = 0;
		printf("%s not found\n",str);
	}
	if (finish)
		printf("PRINT : %s\n",buffer);
	free(buffer);
}


void FreeTrie(trieNode_t **root)
{
	trieNode_t *tempNode = NULL;
	trieNode_t *curN, *curC;
	tempNode = *root;
	while (tempNode->children != NULL)
	{
		tempNode = tempNode->children;
		while (tempNode->neighbor != NULL)
		{
			curN = tempNode;
			tempNode = tempNode->neighbor;
		}
		
	}	
}