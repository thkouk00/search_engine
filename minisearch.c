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
	int result_num = 10; 			// default 
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
				result_num = atoi(argv[i+1]);
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
	str = malloc(sizeof(char)*max);				// temp string , htan max+1 
	if (str == NULL)
		fprintf(stderr, "Malloc failed.\n");
	
	fseek(fp, 0, SEEK_SET);

	clock_t begin1 = clock();

	for (i=0;i<lines;i++)						//store sentences in array
	{
		fscanf(fp, "%s ",str);
		fgets(str, max, fp);
		arr[i] = malloc(sizeof(char)*(strlen(str)+1));
		if (arr[i] == NULL)
			printf("array malloc failed\n");
		strncpy(arr[i], str, strlen(str)+1);
		//printf("i=%d and word %s\n",i,arr[i]);
	}	

	fclose(fp);

	clock_t end1 = clock();
	double time_spent1 = (double)(end1-begin1) / CLOCKS_PER_SEC;
	printf("TIME1 %lf\n",time_spent1);
	
	int *D = (int*)malloc(sizeof(int)*lines);
	for (i=0;i<lines;i++)
		D[i] = 0;

	//create head node for trie
	trieNode_t *root;
	CreateTrie(&root);
	char *str1;
	char delimiter[] = " \t\n"; 

	clock_t begin = clock();

	for (i =0;i<lines;i++)
	{
		strncpy(str, arr[i], strlen(arr[i])+1);
		str1 = strtok(str, delimiter);
		while (str1!=NULL)
		{
			D[i]++;						//how many words in every sentence
			AddNode(&root,str1,i);
			str1 = strtok(NULL, delimiter);
		}
	}
	
	clock_t end = clock();
	double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("TIME %lf\n",time_spent);
	
	printNode(&root,"file");
	printNode(&root,"Ela");
	printNode(&root,"Th");
	// printNode(&root,"tsiritsantoyles");
	// printNode(&root,"-What-a-nice");
	// printNode(&root,"poy");
	// printNode(&root,"Christian");
	
	// // queries from user
	// char *answer = malloc(sizeof(char)*SIZE);
	
	char *answer = malloc(sizeof(char)*(max_words+1));
	// char *answer;
	char *buf;
	char tmp;
	int found;
	
	int avgdl = 0;		//for search
	for (i=0;i<lines;i++)
	{
		// printf("D[%d]=%d\n",i,D[i]);
		avgdl += D[i];
	}
	avgdl = avgdl/lines;
	// printf("avgdl %d\n",avgdl);
	int y = 0;
	int new_size = SIZE;
	double result;
	while(1)
	{
		y = 0;
		i = 0;
		puts("Give query: ");
		scanf("%ms",&buf);
		
		if (!strncmp(buf, "/search", strlen("/search")))
		{
			printf("%s\n",buf);	
			while ((tmp =getchar())!='\n')
			{	
				if (tmp == ' ')
				{
					i++;
					if (i==10)
						break;
				}

				// if (y == new_size-1)
				// {
				// 	new_size = new_size+5;
				// 	answer = realloc(answer, new_size);
				// }
				answer[y] = tmp;
				y++;
				
			}
			i++;
			answer[y] = '\0';
			result = 0;
			printf("\n i = %d and %s and y %d.\n",i,answer,y);
			str1 = strtok(answer, delimiter);
			while (str1!=NULL)
			{
				result = score(str1, D, avgdl, lines, &root);
				printf("RESULT for %s einai %lf\n", str1,result);
				str1 = strtok(NULL, delimiter);
			}
			free(buf);
			free(answer);
		}
		else if (!strncmp(buf, "/df", strlen("/df")))
		{
			listNode *list = NULL;
			int times;
			// memset(answer, '\0', max_words+1);
			fgets(answer, max+1, stdin);
			if (answer[0] == '\n')
				df(&root);
			else
			{
				str1 = strtok(answer, delimiter);
				printf("NAME .%s and length %ld and .%s.\n", answer,strlen(answer),str1);
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
		}
		else if (!strncmp(buf, "/tf", strlen("/tf")))
		{

		}
		else if (!strncmp(buf, "/exit", strlen("/exit")))
		{
			printf("Exit\n");
			free(buf);
			// free(answer);
			break;
		}
		// free(buf);
		// free(answer);
	}
	free(answer);
	for (int i=0;i<lines;i++)
		free(arr[i]);
	free(arr);
	free(D);
	free(str);

	FreeTrie(&root);
	//na kanw ta free

	return 0;
}