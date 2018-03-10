#include "funcs.h"

void score(char **tmpArr, int number_of_q,int* D, int avgdl, int lines, trieNode_t **root,char **docs,int K)
{
	double b = 0.75;
	double k1 = 1.2;
	double result;
	double logarithm;
	double numerator = 0 , denuminator = 0;
	int *sum;
	int i,y;

	listNode *lNode;
	list_t **array, *temp;
	
	array = (list_t**)malloc(sizeof(list_t*)*lines);
	for (i=0;i<lines;i++)
		array[i] = NULL;
	
	sum = malloc(sizeof(int)*number_of_q);
	max_heap **heap ;
	heap = malloc(sizeof(max_heap*)*SIZE_HEAP);
	for (i=0;i<SIZE_HEAP;i++)
		heap[i] = NULL;

	// insert_search(&array[0], 2, 3);
	for (i=0;i<number_of_q;i++)
	{
		sum[i] = 0;
		lNode = find_word(root, tmpArr[i]);
		if (lNode)
		{
			while (lNode->next)
			{
				lNode = lNode->next;
				insert_search(&array[lNode->id], lNode->number_of_times, i);
				sum[i]++;
			}
		}
	}



	for (i=0;i<lines;i++)
	{
		if (array[i] != NULL)
		{
			result = 0;
			temp = array[i];
			while (temp->next)
			{
				
				temp = temp->next;
				logarithm = log2((lines-sum[temp->word_from]+0.5)/(sum[temp->word_from]+0.5));
				numerator = temp->number_of_times * (k1+1);
				denuminator = temp->number_of_times + k1 * (1-b+(b*D[i])/avgdl);
				result += logarithm * numerator / denuminator;
				// printf("MPIKA res %lf\n",result);
			}
			printf("Result for line %d : %lf\n",i,result);
			//insert result to max heap;
			insert_heap(heap,result,i);
		}
	}

	print_heap(heap);

	for (i=0;i<K;i++)
	{
		if (heap[i] != NULL)
			printf("%d.( %d) [%.4lf] %s",i+1,heap[i]->id,heap[i]->result,docs[heap[i]->id]);
	}


	// for (i=0;i<number_of_q;i++)
	// 	printf("SUM[%d] = %d\n",i,sum[i]);

	// for (i=0;i<lines;i++)
	// {
	// 	temp = array[i];
	// 	printf("i = %d\n",i);
	// 	if (temp == NULL)
	// 		continue;
	// 	while (temp->next)
	// 	{
	// 		temp = temp->next;
	// 		printf("number_of_times %d , word_from %d\n",temp->number_of_times,temp->word_from);
	// 	}
	// }

	for (i=0;i<lines;i++)
	{
		FreeList_search(&array[i]);
		free(array[i]);
	}
	free(array);
	free(sum);
	Free_heap(heap);

}
