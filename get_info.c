#include "get_info.h"

int get_info(FILE* fp,long *lines,int *chars,int *max,int *select)
{

	int c;
	long number;
	long tmp = 0;

	fscanf(fp, " %ld", &number);
	//printf("number %ld\n", number);
	if (number != 0){
		fprintf(stderr, "Must start from zero!\n");
		return 1;
	}
	while((c=getc(fp)) != EOF)
	{
		*chars+=1;
		if (c == '\n')
		{
			*lines+=1;
			if (*max < *chars)
			{
				*max = *chars;
				*select = *lines;
			}
			*chars = 0;
			
			fscanf(fp,"%ld",&tmp);
			if (number != tmp-1)
			{
				fprintf(stderr, "Error %ld != %ld\n", number,tmp-1);
				return 1;
			}
			number = tmp;
		}
		// if (c == ' ' || c == '\t'){
		// 	printf("space or tab detected\n");
		// 	return 1;
		// }
		putchar(c);
	}
	*lines += 1;
	printf("\n");
	if (c == EOF)
	{
		*chars+=1;
		if (*max < *chars)
		{
			*max = *chars;
			*select = *lines;
		}
		printf("Max %d chars %d lines %ld\n\n",*max,*chars,*lines);
	}
	return 0;
}