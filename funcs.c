#include "funcs.h"

double score(char* key, int* D, int avgdl, int lines, trieNode_t **root)
{
	double b = 0.75;
	double k1 = 1.2;
	double result = 0;
	int i=0;

	listNode *lNode, *temp;
	lNode = find_word(root,key);
	printf("Yo\n");
	if (lNode == NULL)
		return 0;
	temp = lNode;

	while(temp->next !=NULL)
	{
		temp = temp->next;
		i++;
	}

	//double logarithm = log(lines-i+0.5) - log(i+0.5);
	double logarithm = log2((lines-i+0.5)/(i+0.5));
	printf("Log %lf and avgdl %d\n",logarithm,avgdl);
	while (lNode->next != NULL)
	{
		lNode = lNode->next;
		result += logarithm*(lNode->number_of_times*(k1+1))/(lNode->number_of_times+(k1*(1-b+(b*D[lNode->id]/avgdl))));
		printf("Result is %lf\n",result);
	}

	return result;
}
