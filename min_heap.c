#include "min_heap.h"

// min heap implementation , used for /search query to pick K most relevant docs

void insert_heap(min_heap **array,double result,int id,int lines)
{
	int i;
	for (i=0;i<lines;i++)
	{
		if (array[i] == NULL)
		{
			array[i] = malloc(sizeof(min_heap));
			array[i]->result = result;
			array[i]->id = id;
			heapify(array,lines);
			break;
		}
	}
}

void heapify(min_heap **array,int lines)
{
	int i;
	min_heap *temp;
	for (i=lines-1;i>=0;i--)
	{
		if (array[i] != NULL)
		{
			if (array[i]->result < array[(i-1)/2]->result)
			{
				temp = array[i]; 
				array[i] = array[(i-1)/2];
				array[(i-1)/2] = temp;
			}	
		}
	}
}

void heapsort(min_heap **array, int lines)
{
	int i;
	min_heap *temp;
	for (i=lines-1;i>0;i--)
	{

		if (array[i]!=NULL)
		{
			temp = array[0];
			array[0] = array[i];
			array[i] = temp;
			heapify(array, i-1);
		}
	}

}


void print_heap(min_heap **array,int lines)
{
	int i;
	
	for (i=0;i<lines;i++)
	{
		if (array[i] != NULL)
			printf("i:%d and result %lf and id %d\n",i,array[i]->result,array[i]->id);
	}
}

void Free_heap(min_heap **array,int lines)
{
	int i;
	for (i=0;i<lines;i++)
	{
		if (array[i] != NULL)
			free(array[i]);
	}
	free(array);
}