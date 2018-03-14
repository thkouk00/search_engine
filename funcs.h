#ifndef _FUNCSH_
#define _FUNCSH_
#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "trie.h"
#include "list.h"
#include "max_heap.h"
#include "stack.h"

void score(char**, int,int*, int, int , trieNode_t **,char **,int,int);
void underline(char **,int ,char *,int);
int std_input_size(int ,int , int);

#endif
