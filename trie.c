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


void AddNode(trieNode_t **root,char *key)
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
			//printf("ADD %c in %s and eow %d\n",tempNode->key,tmpstr,tempNode->endofword);
			tempNode->endofword = 1;
		}
		key++;
	}
	// printf("END %c for %s\n",tempNode->key,tmpstr);
	// tempNode->endofword = 1;
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
	for (int i=0;i<strlen(str);i++)
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
	buffer[strlen(str)] = '\0';
	printf("PRINT : %s\n",buffer);
	free(buffer);
}


void length_trie()
{

}