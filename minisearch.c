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
	arr = malloc(sizeof(char*)*lines);
	// for (int i=0;i<lines;i++)
	// 	arr[i] = malloc(sizeof(char)*(max+1));

	fseek(fp, 0, SEEK_SET);
	char *str1;
	str1 = malloc(sizeof(char)*(max+1));
	
	//proxora apo thn arxh ths grammhs mexri na breis keno , diladi na exei perasei to id
	//kai meta pare oli ti grammh kai balti sto map
	for (int i=0;i<lines;i++)
	{
		while(1)
		{
			fscanf(fp, "%s", str1);							//takes first word
			c = getc(fp);									//takes space after first word
			if (fgets(str1, max, fp) == NULL)				// sentence i want
				break;
			printf("length %ld\n", strlen(str1));
			arr[i] = malloc(sizeof(char)*strlen(str1));
			strcpy(arr[i], str1);
			printf("%s", str1);
			
		}
	}



	fclose(fp);
	printf("\nEND %s\n",arr[1]);
	printf("\nLines %ld and max %d and select %d\n",lines,max,select);

	
	return 0;
}