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
	
	while (*key != '\0')
	{
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


	// if (tempNode->children == NULL)		//no children , create first children
	// {
	// 	tempNode->children = CreateTrieNode(*key);		// roots children
	// 	tempNode = tempNode->children;			// first child node
	// 	key++;									// next letter 
	// 	//printf("first %s and %c\n",tmpstr,tempNode->key);
	// }
	// else
	// {
	// 	if (tempNode->children->key == *key)
	// 	{
	// 		tempNode = tempNode->children;
	// 		key++;
	// 		//printf("HEE word %s and %c\n",tmpstr,tempNode->key);
	// 	}
	// 	else
	// 	{	
	// 		int flag = 0;
	// 		tempNode = tempNode->children;
	// 		while (tempNode->neighbor != NULL)
	// 		{
	// 			tempNode = tempNode->neighbor;
	// 			if (tempNode->key == *key)
	// 			{
	// 				flag++;
	// 				key++;
	// 				break;
	// 			}
	// 		}
	// 		if (!flag)
	// 		{
	// 			tempNode->neighbor = CreateTrieNode(*key);
	// 			tempNode = tempNode->neighbor;
	// 			//printf("InSErT %c\n",tempNode->key);
	// 			key++;
	// 		}
	// 	}
		
	// }
	// //tempNode = tempNode->children;
	// while (*key != '\0')
	// {

	// 	// tempNode = tempNode->children;
	// 	if (tempNode->children == NULL)		
	// 	{
	// 		tempNode->children = CreateTrieNode(*key);	
	// 		tempNode = tempNode->children;			
	// 		key++;								 
	// 	}
	// 	else
	// 	{
	// 		tempNode = tempNode->children;	
	// 		if (tempNode->key == *key)
	// 		{
	// 			key++;
	// 			//tempNode = tempNode->children;
	// 		}
	// 		else
	// 		{
	// 			if (tempNode->neighbor == NULL)
	// 			{
	// 				tempNode->neighbor = CreateTrieNode(*key);
	// 				tempNode = tempNode->neighbor;
	// 				key++;
	// 			}
	// 			else
	// 			{
	// 				int flag = 0;
	// 				while (tempNode->neighbor != NULL)
	// 				{
	// 					tempNode = tempNode->neighbor;
	// 					if (tempNode->key == *key)
	// 					{
	// 						//tempNode = tempNode->neighbor;
	// 						key++;
	// 						flag++;
	// 						break;
	// 					}
	// 				}
	// 				if (!flag)
	// 				{
	// 					tempNode->neighbor = CreateTrieNode(*key);
	// 					tempNode = tempNode->neighbor;
	// 					key++;
	// 				}
	// 			}
	// 		}
	// 	}

	// }

}

void printNode(trieNode_t **root,char *key)
{
	printf("\nPRINT: ");
	int found = 0 , finish = 1;
	char *str = key;
	char *buffer = malloc(sizeof(char)*strlen(str));
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
				key++;
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
						key++;
						break;
					}
				}
				if (found)
					break;
			}
		}
		if (*key != '\0' && i+1>=strlen(str))
		{
			finish = 0;
			break;
		}
	}
	if (finish)
		printf("%s found\n",buffer);
	else
		printf("%s not found\n",str);
	free(buffer);
}


void length_trie()
{

}