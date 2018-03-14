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
			//insert result to max heap;
			insert_heap(heap,result,i);
		}
	}

	int len = 0;
	for (i=0;i<K;i++)
	{
		if (heap[i] != NULL){
			printf("%d.( %d) [%.4lf] ",i+1,heap[i]->id,heap[i]->result);
			//pairnw to i-osto apotelesma tou heap kai apo ekei vrisko to id gia to keimeno
			//kai epeita to vazv gia ipogrammisi.
			len = std_input_size(i+1,heap[i]->id,heap[i]->result);
			len+=13; //for spaces () etc
			underline(tmpArr, number_of_q, docs[heap[i]->id],len);
		}
	}


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
// scan doc file for given words , if we find a word we store the current length
// so we can find where to underline , after finding the lenght for the words 
void underline(char **tmpArr,int number_of_q,char *docs,int len)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	char delimiter[] = " \t\n";
	
	int i,sum = len,flag = 0;
	char *str, *str1;
	
	str = malloc(sizeof(char)*(strlen(docs)+1));
	strncpy(str, docs, strlen(docs));
	
	list_t *length = NULL;
	
	str1 = strtok(str, delimiter);
	while (str1!=NULL)
	{
		for (i=0;i<number_of_q;i++)
		{
			if (tmpArr[i]!=NULL)
			{
				if (!strcmp(str1, tmpArr[i]))
				{
					insert_search(&length, sum+1, i);
					break;
				}
			}				
		}
		sum+=strlen(str1)+1;
		str1 = strtok(NULL, delimiter);
	}
	int loop = 0;
	int z = 0,l=0;
	int y = 0;
	list_t *temp = length;
	i=0;
	if (temp)
	{
		while (i<strlen(docs))
		{
			loop++;
			
			while (i<(w.ws_col*loop)-len && i<strlen(docs))	
			{
				printf("%c",docs[i]);
				i++;
			}

			if (i==strlen(docs))
				printf("\n");
		
			z = 0;
			while (temp->next && temp->next->number_of_times < i+len)
			{
				temp = temp->next;
				
				if (temp->number_of_times < i+len)
				{
					if (z<temp->number_of_times-1)
					{
						temp->number_of_times = temp->number_of_times - w.ws_col*(loop-1);
					}
				
					while (z<temp->number_of_times-1)
					{
						printf(" ");
						z++;
					}
					while (z>temp->number_of_times-2 && z<temp->number_of_times+strlen(tmpArr[temp->word_from])-1)
					{
						printf("^");
						z++;
						flag = 1;
					}
					if (!flag)
						break;
						
				}
					
			}	
			printf("\n");
		}
	}
	free(str);
	FreeList_search(&length);
	free(length);
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
	if (tt<0)
	{
		tt = tt * (-1);
		len++;
	}
	if (tt ==0)
		len++;
	while (tt>0)
	{
		tt = tt/10;
		len++;
	}
	
	return len;
}