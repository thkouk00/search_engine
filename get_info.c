#include "get_info.h"

int get_info(FILE* fp,int *lines,int *chars,int *max,int *max_words,int *select)
{

	int c;
	long number;
	long tmp = 0;
	int temp_words = 0;
	*max_words = 0;

	fscanf(fp, " %ld", &number);
	if (number != 0){
		fprintf(stderr, "Must start from zero!\n");
		return 1;
	}
	while((c=getc(fp)) != EOF)
	{
		if (c == ' ' || c == '\n')
		{
			if (temp_words > *max_words)
				*max_words = temp_words;
			temp_words = 0;
		}
		else
		{
			temp_words++;
			// printf("char is %c and %d\n",c,temp_words);
		}
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
				fprintf(stderr, "Lines not succesive.\n");
				return 1;
			}
			number = tmp;
		}

		//putchar(c);		// print input
	}
	*lines += 1;
	if (c == EOF)
	{
		*chars+=1;
		if (*max < *chars)
		{
			*max = *chars;
			*select = *lines;
		}
		printf("\nMax %d chars %d lines %d\n\n",*max,*chars,*lines);
		printf("MAX WORDS %d\n",*max_words);
	}
	return 0;
}