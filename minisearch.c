#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_info.h"

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
		if (!doc_flag)
			Usage(argv[0]);
	}

	int c;
	long lines = 0;					//total lines
	int chars = 0;					//chars per line
	int max = 0;					//max number of chars in line
	int select = 0;					//na to svisc meta axristo
	
	if (get_info(fp,&lines,&chars,&max,&select)){
		fprintf(stderr, "ERROR DETECTED.\n");
		return 1;
	}
	
	char **arr;					
	arr = malloc(sizeof(char*)*lines);				//array to store sentences

	char *str;
	str = malloc(sizeof(char)*(max+1));				// temp string
	
	fseek(fp, 0, SEEK_SET);
	for (int i=0;i<lines;i++)						//store sentences in array
	{
		fscanf(fp, "%s", str);
		c = getc(fp);
		fgets(str, max+1, fp);
		arr[i] = malloc(sizeof(char)*strlen(str));
		strcpy(arr[i], str);
	}	

	for (int i=0;i<lines;i++)
		printf("%s\n", arr[i]);
	



	fclose(fp);
	printf("\nLines %ld and max %d and select %d\n",lines,max,select);

	
	return 0;
}