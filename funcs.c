#include "funcs.h"

// calculate score in order to print relevant docs for given words

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

	// print_heap(heap);

	int len = 0;
	for (i=0;i<K;i++)
	{
		if (heap[i] != NULL){
			printf("%d.( %d) [%.4lf] ",i+1,heap[i]->id,heap[i]->result);
			//pairnw to i-osto apotelesma tou heap kai apo ekei vrisko to id gia to keimeno
			//kai epeita to vazv gia ipogrammisi/.
			len = std_input_size(i+1,heap[i]->id,heap[i]->result);
			len+=13; //for spaces () etc
			underline(tmpArr, number_of_q, docs[heap[i]->id], length,len);
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

// function to underline words given from /search query 
void underline(char **tmpArr,int number_of_q,char *docs,int *length,int len)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	char delimiter[] = " \t\n";
	// printf("STR %ld and %d\n",strlen(docs)+len,len);
	int i,sum = len,flag = 0;
	char *str, *str1;
	int *flags = malloc(sizeof(int)*number_of_q);
	str = malloc(sizeof(char)*(strlen(docs)+1));
	strncpy(str, docs, strlen(docs));
	for (i=0;i<number_of_q;i++)
	{
		length[i] = 99999999;
		flags[i] = 0;
	}

	str1 = strtok(str, delimiter);
	while (str1!=NULL)
	{
		for (i=0;i<number_of_q;i++)
		{
			if (tmpArr[i]!=NULL)
			{
				if (!strcmp(str1, tmpArr[i]))
				{
					length[i] = sum+1;
					// flag = 1;
				}
			}				
		}
		sum+=strlen(str1)+1;
		str1 = strtok(NULL, delimiter);
	}
	sort_array(length, tmpArr, number_of_q);
	// for (int l =0;l<number_of_q;l++)
	// 	printf("lenght[%d] %d\n",l,length[l]);
	int loop = 0;
	int z = 0,l=0;
	int y = 0;
	i=0;
	while (i<strlen(docs))
	{
		loop++;
		while (i<(w.ws_col*loop)-len && i<strlen(docs))//+len-1)	//htan -1 to len edw,den ftanei to i sto telos
		{
			printf("%c",docs[i]);
			i++;
		}
		// exit(1);
		// printf("I %d\n", i);
		
		z = 0;
		for (y=0;y<number_of_q;y++)
		{
			if (flags[y])	
				continue;
			
			// if (!strcmp(tmpArr[y],"syspro"))
			// 	printf("HRE i %d and %d\n",i,length[y]);
			// exit(1);
			if (length[y]<i+len-1)
			{
				// printf("loop %d and length %d adn %d\n",loop,length[y],y);
				if (z<length[y]-1)
				{
					length[y]= length[y] - w.ws_col*(loop-1);
				}
				// if (!strcmp(tmpArr[y],"syspro"))
				// 	printf("HRE\n");
				// exit(1);
				while (z<length[y]-1)
				{
					printf(" ");
					z++;
				}
				while (z>=length[y]-1 && z<length[y]+strlen(tmpArr[y])-1)
				{
					printf("^");
					z++;
					flags[y] = 1;
				}
			}
		}
		printf("\n");
	}
	printf("I %d\n",i);
	// printf("\n");

	free(flags);
	free(str);
}

// helper functions

void sort_array(int *length, char **tmpArr,int number_of_q)
{
	int i,j;
	int temp;
	char *tmparr;
	
	for (i=0;i<number_of_q;i++)
	{
		for (j=i;j<number_of_q;j++)
		{
			if (length[i]>length[j])
			{
				temp = length[i];
				tmparr = tmpArr[i];
				length[i] = length[j];
				tmpArr[i] = tmpArr[j];
				length[j] = temp;
				tmpArr[j] = tmparr;
			}
		}
	}
}

int std_input_size(int i,int id, int result)
{
	int tt = 0;
	int len = 0;
	tt = i;
	if (tt ==0)
		len++;
	while (tt>0)
	{
		tt = tt/10;
		len++;
	}
	tt = id;
	if (tt ==0)
		len++;
	while (tt>0)
	{
		tt = tt/10;
		len++;
	}
	tt = result;
	if (tt ==0)
		len++;
	while (tt>0)
	{
		tt = tt/10;
		len++;
	}
	// printf("lenght %d\n",len);
	return len;
}