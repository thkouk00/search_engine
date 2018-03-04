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
	tempNode->endofword = 1;
	printf("%s :\n",tmpstr);
	//printf("%s from id: %d and length %ld\n", tmpstr,id,strlen(tmpstr));
	listNode *cur = tempNode->plist; 
	if (tempNode->plist == NULL)
	{
		insert(&(tempNode->plist),id);
		print(&(tempNode->plist));
	}
	else
	{
		insert(&cur,id);
		print(&cur);
		//printf("MPIKA WHILE line %d\n",id);
		// while (cur->next != NULL)
		// {
		// 	//printf("%s :\n",tmpstr);
		// 	insert(&cur,id);
		// 	print(&cur);
		// 	cur = cur->next;
		// 	//printf("NAI\n");
		// }
		//printf("BGIKA\n");
	}
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
		if (tempNode->endofword && i<strlen(str)-1)
		{
			printf("%s not found\n",str);
			finish = 0;
			break;
		}
	}
	buffer[strlen(str)] = '\0';
	if (finish)
		printf("PRINT : %s\n",buffer);
	free(buffer);
}


void length_trie()
{

}