#include "max_heap.h"

void insert_heap(max_heap **array,double result,int id)
{
	int i;
	for (i=0;i<SIZE_HEAP;i++)
	{
		if (array[i] == NULL)
		{
			array[i] = malloc(sizeof(max_heap));
			array[i]->result = result;
			array[i]->id = id;
			heapify(array);
			break;
		}
	}
}

void heapify(max_heap **array)
{
	int i;
	max_heap *temp;
	for (i=SIZE_HEAP-1;i>=0;i--)
	{
		if (array[i] != NULL)
		{
			if (array[i]->result > array[(i-1)/2]->result)
			{
				printf("%lf > %lf\n",array[i]->result,array[(i-1)/2]->result);
				temp = array[i]; 
				array[i] = array[(i-1)/2];
				array[(i-1)/2] = temp;
			}	
		}
	}
}

void print_heap(max_heap **array)
{
	int i;
	for (i=0;i<SIZE_HEAP;i++)
	{
		if (array[i] != NULL)
			printf("i:%d and result %lf and id %d\n",i,array[i]->result,array[i]->id);
	}
}

void Free_heap(max_heap **array)
{
	int i;
	for (i=0;i<SIZE_HEAP;i++)
	{
		if (array[i] != NULL)
			free(array[i]);
	}
	free(array);
}