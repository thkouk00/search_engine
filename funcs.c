#include "funcs.h"

void score(char **tmpArr, int number_of_q,int* D, int avgdl, int lines, trieNode_t **root,char **docs,int K,int max_words)
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

	// char **A = malloc(sizeof(char*)*number_of_q);		//for underline
	int *length = malloc(sizeof(int)*number_of_q);
	
	for (i=0;i<number_of_q;i++)
		length[i] = -1;
	// underline(tmpArr, number_of_q, docs[0], length);
	//call underline
	// printf("SCORE %d %d\n",length[0],length[1]);

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
			}
			printf("Result for line %d : %lf\n",i,result);
			//insert result to max heap;
			insert_heap(heap,result,i);
		}
	}

	print_heap(heap);

	for (i=0;i<K;i++)
	{
		if (heap[i] != NULL){
			printf("%d.( %d) [%.4lf] ",i+1,heap[i]->id,heap[i]->result);
			//pairnw to i-osto apotelesma tou heap kai apo ekei vrisko to id gia to keimeno
			//kai epeita to vazv gia ipogrammisi/.
			underline(tmpArr, number_of_q, docs[heap[i]->id], length);
			// printf("%d.( %d) [%.4lf] %s",i+1,heap[i]->id,heap[i]->result,docs[heap[i]->id]);
		}
	}

	//Print info
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
//na kaw ta free kai edw kai panw
void underline(char **tmpArr,int number_of_q,char *docs,int *length)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	char delimiter[] = " \t\n";

	int i,sum = 0,flag = 0;
	char *str, *str1;

	str = malloc(sizeof(char)*(strlen(docs)+1));
	strncpy(str, docs, strlen(docs));
	str1 = strtok(str, delimiter);
	while (str1!=NULL)
	{
		for (i=0;i<number_of_q;i++)
		{
			length[i] = -1;
			if (tmpArr[i]!=NULL)
			{
				if (!strcmp(str1, tmpArr[i]))
				{
					length[i] = sum+1;
					flag = 1;
					heapify_length(length, tmpArr, number_of_q);
					break;
				}
			}				
		}
		sum+=strlen(str1)+1;
		str1 = strtok(NULL, delimiter);
	}
	printf("DOC %s\n",docs);
	for (i=0;i<number_of_q;i++)
	{
		printf("L %d and %s\n", length[i],tmpArr[i]);
	}
	// printf("DOC\n%s",docs);
	int loop = 0;
	int z = 0,l=0;
	int y = 0;
	i=0;
	while (i<strlen(docs))
	{
		loop++;
		while (i<w.ws_col*loop && i<strlen(docs))
		{
			printf("%c",docs[i]);
			i++;
		}
		// printf("\n");
		if (loop==1)
		for (l=0;l<16;l++)
			printf(" ");
		z = 0;
		for (y=0;y<number_of_q;y++)
		{
			if (tmpArr[y]==NULL)
				continue;
			if (length[y]<i)
			{
				if (tmpArr[y]!=NULL )//&& loop!=1)
				{
					if (z<length[y]-1)
					{
						length[y]= length[y] - w.ws_col*(loop-1);
					}
				}
				while (z<length[y]-1)
				{
					printf(" ");
					z++;
				}
				while (z>=length[y]-1 && z<length[y]+strlen(tmpArr[y])-1)
				{
					printf("^");
					z++;
					flag = 1;
				}
				if (flag)
					tmpArr[y] = NULL;
			}
		}
		printf("\n");
	}
	printf("\n");

}

void heapify_length(int *length, char **tmpArr,int number_of_q)
{
	int i;
	int temp;
	char *tmparr;
	
	printf("HEAPIFY BEFORE\n");
	for (i=0;i<number_of_q;i++)
	{
		printf("%s\n", tmpArr[i]);
	}

	for (i=number_of_q-1;i>=0;i--)
	{
		if (length[i] != -1)
		{
			if ((length[i] < length[(i-1)/2]) && length[i] >=0)
			{
				// printf("%d > %d\n",length[i],length[(i-1)/2]);
				temp = length[i]; 
				tmparr = tmpArr[i];
				length[i] = length[(i-1)/2];
				tmpArr[i] = tmpArr[(i-1)/2];
				length[(i-1)/2] = temp;
				tmpArr[(i-1)/2] = tmparr;
			}	
		}
	}

	printf("HEAPIFY AFTER\n");
	for (i=0;i<number_of_q;i++)
	{
		printf("%s\n", tmpArr[i]);
	}

	// for (i=0;i<number_of_q;i++)
	// {
	// 	if (length[i]!=-1)
	// 		printf("%d\n", length[i]);
	// }
}