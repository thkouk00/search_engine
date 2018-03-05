#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_info.h"
#include "trie.h"

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

	int c;
	int lines = 0;					//total lines
	int chars = 0;					//chars per line
	int max = 0;					//max number of chars in line
	int select = 0;					//na to svisc meta axristo
	
	if (get_info(fp,&lines,&chars,&max,&select)){
		fprintf(stderr, "ERROR DETECTED.\n");
		exit(1);
	}
	
	char **arr;					
	arr = malloc(sizeof(char*)*lines);				//array to store sentences

	char *str;
	str = malloc(sizeof(char)*max);				// temp string , htan max+1 
	
	fseek(fp, 0, SEEK_SET);
	for (int i=0;i<lines;i++)						//store sentences in array
	{
		fscanf(fp, "%s ", str);
		fgets(str, max, fp);
		arr[i] = malloc(sizeof(char)*strlen(str));
		strcpy(arr[i], str);
	}	

	// for (int i=0;i<lines;i++)		//print input
	// 	printf("i=%d %s\n", i,arr[i]);
	
	//create head node for trie
	trieNode_t *root;
	CreateTrie(&root);
	char *str1;
	char delimiter[] = " \t\n"; 

	for (int i =0;i<lines;i++)
	{
		str = arr[i];
		str1 = strtok(str, delimiter);
		
		while (str1!=NULL)
		{
			AddNode(&root,str1,i);
			str1 = strtok(NULL, delimiter);
		}
	}

	printNode(&root,"-What-a-nice");
	printNode(&root,"poy");
	printNode(&root,"grammes");
	printNode(&root,"Everybody");		//na rotiso an prpei na emfanizei apotelesma
	printNode(&root,"xvreaei");			//an psaxw gia "Every"
	printNode(&root,"re");
	printNode(&root,"YOLO");
	printNode(&root,"magken");
	printNode(&root,"gamhtheite");		//na ftiaxv print gia lexeis poy den iparxoun

	// queries from user
	char answer[20];
	//puts("Give query:");
	//fgets(answer,20,stdin);
	// while (1)
	// {
	// 	puts("Give query:");
	// 	fgets(answer,20,stdin);
	// 	printf ("answer is %s",answer);
	// 	if (!strncmp(answer, "/search",strlen("/search")))
	// 		printf("You asked for search\n");
	// 	else if (!strncmp(answer, "/df",strlen("/df")))
	// 		printf("You asked for document frequency\n");
	// 	else if (!strncmp(answer, "/tf",strlen("/tf")))
	// 		printf("You asked for term frequency\n");
	// 	else if (!strncmp(answer, "/exit",strlen("/exit")))
	// 	{
	// 		printf("Exit program\n");
	// 		break;
	// 	}

	// }
	// printf("answer-> %s",answer);


	fclose(fp);
	//na kanw ta free

	return 0;
}