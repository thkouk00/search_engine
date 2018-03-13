//#ifndef _MINISEARCH_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "get_info.h"
#include "trie.h"
#include "funcs.h"



#define SIZE 6

void Usage(char *prog_name)			/* Usage */
{
   fprintf(stderr, "Usage: %s -i <docfile> -k <number of results>\n", prog_name);
} 


int main(int argc, char *argv[])
{
	FILE *fp;
	int K = 10; 			// default 
	int doc_flag = 0;				// flag for docfile -> exist or not
	
	if (argc < 2)
	{
		Usage(argv[0]);
		exit(1);
	}
	else		
	{
		for(int i=1;i<argc;i+=2){
			if (!strcmp(argv[i],"-i"))
			{
				fp = fopen(argv[i+1], "r");
				doc_flag = 1;
			}
			else if (!strcmp(argv[i],"-k"))
			{
				K = atoi(argv[i+1]);
			}
		}
		if (!doc_flag){
			printf("Dockfile required\n");
			Usage(argv[0]);
			exit(1);
		}
	}

	int i,c;
	int lines = 0;					//total lines
	int chars = 0;					//chars per line
	int max = 0;					//max number of chars in line
	int max_words = 0;				// max length of word
	int select = 0;					//na to svisc meta axristo
	
	if (get_info(fp,&lines,&chars,&max,&max_words,&select)){
		fprintf(stderr, "ERROR DETECTED.\n");
		exit(1);
	}
	
	char **arr;					
	arr = malloc(sizeof(char*)*lines);				//array to store sentences
	if (arr == NULL)
		fprintf(stderr, "Malloc failed.\n");

	char *str;
	str = malloc(sizeof(char)*max);					// temp string , htan max+1 
	if (str == NULL)
		fprintf(stderr, "Malloc failed.\n");
	
	fseek(fp, 0, SEEK_SET);

	for (i=0;i<lines;i++)							//store sentences in array
	{
		fscanf(fp, "%s ",str);
		fgets(str, max, fp);
		arr[i] = malloc(sizeof(char)*(strlen(str)+1));
		if (arr[i] == NULL)
			printf("array malloc failed\n");
		strncpy(arr[i], str, strlen(str)+1);
	}	

	fclose(fp);
	
	int *D = (int*)malloc(sizeof(int)*lines);
	for (i=0;i<lines;i++)
		D[i] = 0;

	//create head node for trie
	trieNode_t *root;
	CreateTrie(&root);
	char *str1;
	char delimiter[] = " \t\n"; 

	for (i =0;i<lines;i++)
	{
		strncpy(str, arr[i], strlen(arr[i])+1);
		str1 = strtok(str, delimiter);
		while (str1!=NULL)
		{
			D[i]++;						//how many words there are in every sentence
			AddNode(&root,str1,i);
			str1 = strtok(NULL, delimiter);
		}
	}
	
	// queries from user
	
	char *answer;
	char *buf;
	char tmp;
	int found;
	
	int avgdl = 0;				// average number of words in index
	for (i=0;i<lines;i++)
	{
		avgdl += D[i];
	}
	avgdl = avgdl/lines;
	int y = 0;
	int new_size = SIZE;
	double result;
	while(1)					// User queries -> /search , /df , /tf , /exit
	{
		y = 0;
		i = 0;
		puts("Give query: ");
		scanf("%ms",&buf);
		
		if (!strncmp(buf, "/search", strlen("/search")))
		{
			//space to alloc -> 10*max words 
			// max heap structure
			i = 0;
			answer = malloc(sizeof(char)*(10*max_words+11));	// 10words (max) + 10 spaces
			printf("%s\n",buf);	
			fgets(answer, 10*max_words+10, stdin);
			if (answer[0] == '\n')
				printf("Usage: /search q1 q2 . . . q10\n");
			else
			{
				str1 = strtok(answer, delimiter);
				if (str1 == NULL)
				{
					printf("Usage: /search q1 q2 . . . q10\n");
				}
				else
				{
					char **tmpArr;
					tmpArr = malloc(sizeof(char*)*10);

					while (str1!=NULL)
					{
						if (i == 10)
						{
							printf("10 words completed\n");
							break;
						}
						tmpArr[i] = malloc(sizeof(char)*(strlen(str1)+1));
						strcpy(tmpArr[i], str1);
						str1 = strtok(NULL, delimiter);
						i++;
					}
					score(tmpArr, i,D, avgdl, lines, &root,arr,K,max_words);
					for (y=0;y<i;y++)
						free(tmpArr[y]);
					free(tmpArr);
				}
			}
			free(buf);
			free(answer);
		}
		else if (!strncmp(buf, "/df", strlen("/df")))
		{
			listNode *list = NULL;
			int times;
			answer = malloc(sizeof(char)*(max_words+1));
			fgets(answer, max_words+1, stdin);
			if (answer[0] == '\n')
				df(&root);
			else
			{
				str1 = strtok(answer, delimiter);
				list = find_word(&root, str1);
				if (list == NULL)
					printf("%s not found!\n", str1);
				else
				{	
					times = 0;
					while (list->next)
					{
						list = list->next;
						times++;
					}
					printf("%s %d\n",str1,times);
				}
			}
			free(buf);
			free(answer);
		}
		else if (!strncmp(buf, "/tf", strlen("/tf")))
		{
			listNode *list = NULL;
			int str2;
			answer = malloc(sizeof(char)*(max_words+sizeof(int)+3));
			fgets(answer, max_words+sizeof(int)+2, stdin); 			// +1 is for space at first pos
			if (answer[0] == '\n')
			{
				printf("Usage: /tf id word\n");
			}
			else
			{	
				str2 = (int)atoi(strtok(answer, delimiter));
				str1 = strtok(NULL, delimiter);
				if (str1 == NULL)
					printf("Usage: /tf id word\n");
				else
				{
					list = find_word(&root, str1);
					if (list == NULL)
						printf("%s not found!\n", str1);
					else
					{	
						while (list->next)
						{
							list = list->next;
							if (list->id == str2)
							{
								printf("%s %d\n", str1,list->number_of_times);
								break;
							}	
						}
					}
				}
			}
			free(buf);
			free(answer);
		}
		else if (!strncmp(buf, "/exit", strlen("/exit")))
		{
			printf("Exit\n");
			free(buf);
			break;
		}
	}
	
	// free memory
	for (int i=0;i<lines;i++)
		free(arr[i]);
	free(arr);
	free(D);
	free(str);
	FreeTrie(&root);

	return 0;
}