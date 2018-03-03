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
	return node;
}


void AddNode(trieNode_t **root,char *key)
{
	char *tmpstr = key;
	trieNode_t *tempNode = NULL;

	if (*root == NULL)
	{
		fprintf(stderr, "Not initialized Trie!\n");
		exit(1);
	}

	
	tempNode = *root;
	if (tempNode->children == NULL)		//no children , create first children
	{
		tempNode->children = CreateTrieNode(*key);		// roots children
		tempNode = tempNode->children;			// first child node
		key++;									// next letter 
		//printf("first %s and %c\n",tmpstr,tempNode->key);
	}
	else
	{
		if (tempNode->children->key == *key)
		{
			tempNode = tempNode->children;
			key++;
			//printf("HEE word %s and %c\n",tmpstr,tempNode->key);
		}
		else
		{	
			int flag = 0;
			tempNode = tempNode->children;
			while (tempNode->neighbor != NULL)
			{
				tempNode = tempNode->neighbor;
				if (tempNode->key == *key)
				{
					flag++;
					key++;
					break;
				}
			}
			if (!flag)
			{
				tempNode->neighbor = CreateTrieNode(*key);
				tempNode = tempNode->neighbor;
				//printf("InSErT %c\n",tempNode->key);
				key++;
			}
		}
		
	}
	//tempNode = tempNode->children;
	while (*key != '\0')
	{

		// tempNode = tempNode->children;
		if (tempNode->children == NULL)		
		{
			tempNode->children = CreateTrieNode(*key);	
			tempNode = tempNode->children;			
			key++;								 
		}
		else
		{
			tempNode = tempNode->children;	
			if (tempNode->key == *key)
			{
				key++;
				//tempNode = tempNode->children;
			}
			else
			{
				if (tempNode->neighbor == NULL)
				{
					tempNode->neighbor = CreateTrieNode(*key);
					tempNode = tempNode->neighbor;
					key++;
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
							key++;
							flag++;
							break;
						}
					}
					if (!flag)
					{
						tempNode->neighbor = CreateTrieNode(*key);
						tempNode = tempNode->neighbor;
						key++;
					}
				}
			}
		}

	}
}

void printNode(trieNode_t **root,char *key)
{
	printf("PRINT:");
	int found = 0;
	trieNode_t *tempNode = NULL;

	if (*root == NULL)
	{
		fprintf(stderr, "Not initialized Trie!\n");
		exit(1);
	}
	
	tempNode = *root;
	if (tempNode->children == NULL)
		printf("No entries\n");
	else
	{
		tempNode = tempNode->children;
		while (tempNode != NULL)
		{
			if (tempNode->key == *key)
			{
				printf("%c", tempNode->key);
				key++;
			}
			else
			{
				while (tempNode->neighbor != NULL)
				{
					tempNode = tempNode->neighbor;
					if (tempNode->key == *key)
					{
						printf("%c",tempNode->key);
						found = 1;
						key++;
						break;
					}
				}
				// if ((tempNode->neighbor == NULL) && !found)
				// {
				// 	printf("%s not found\n",key);
				// 	exit(1);
				// }
			}
			tempNode = tempNode->children;
		}
	}
	printf("\n");
}


void length_trie()
{

}